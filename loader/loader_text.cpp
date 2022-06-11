#include "executer/cpu.hpp"
#include "lib/function.hpp"
#include "loader/loader.hpp"
#include "loader/text_scanner.hpp"
#include <FlexLexer.h>
#include <cassert>
#include <functional>
#include <string>

// Author: Voldemort
// Note: Dark magic, do not touch

double yylval;
static text_type next_type = INVALID;
static unsigned long max_global = 0;

static text_type peek(yyFlexLexer &lexer, double &next_val) {
    static double peeked_val;
    if (next_type == INVALID) {
        text_type next = static_cast<text_type>(lexer.yylex());
        peeked_val = next_val = yylval;

        return next;
    } else {
        next_val = peeked_val;
        return next_type;
    }
}

static bool match(text_type tok, yyFlexLexer &lexer, double &next_val) {
    if (tok == peek(lexer, next_val)) {
        next_type = INVALID;
        return true;
    } else {
        return false;
    }
}

/* Eats up to n characters from lexer until a character in delim is found or
 * something different than a character is met. */
static void eatup(yyFlexLexer &lexer, std::string delim = "", unsigned n = -1) {
    double val;
    text_type next;

    while (n) {
        next = peek(lexer, val);
        if (next == CHAR) {
            --n;
            if (delim.find_first_of(static_cast<char>(val)) != delim.npos) {
                break;
            }
        } else {
            next_type = next;
            break;
        }
    }
}

static bool string(yyFlexLexer &lexer, std::string &res) {
    double val;
    bool matched = match(LONG, lexer, val);

    unsigned long number = val;
    if (!matched) {
        return false;
    }

    eatup(lexer, "", 1);

    res = "";

    for (unsigned long i = 0; i < number; ++i) {
        match(CHAR, lexer, val);
        char chr = val;
        if (static_cast<double>(chr) != val) {
            return false;
        }

        res += chr;
    }

    return true;
}

static bool strings(yyFlexLexer &lexer, std::function<void(unsigned long, std::string &)> insert) {
    double val;
    bool matched = match(LONG, lexer, val);

    unsigned long number = val;

    // If it didn't match, this won't run
    for (unsigned long i = 0; i < number && matched; ++i) {
        eatup(lexer, "", 1);
        std::string res;
        matched = string(lexer, res);
        if (matched) {
            insert(i, res);
        }
    }

    return matched;
}

static bool numbers(yyFlexLexer &lexer, std::function<void(unsigned long, double)> insert) {
    double val;
    bool matched = match(LONG, lexer, val);

    unsigned long number = val;

    // If it didn't match, this won't run
    for (unsigned long i = 0; i < number && matched; ++i) {
        eatup(lexer, "", 1);
        matched = match(DOUBLE, lexer, val);
        if (matched)
            insert(i, val);
    }

    return matched;
}

static bool userfunc(yyFlexLexer &lexer, std::function<void(unsigned long, Function *)> insert) {
    double val;

    bool matched = match(LONG, lexer, val);

    unsigned long address = val;
    if (!matched) {
        return false;
    }
    eatup(lexer, "", 1);

    matched = match(LONG, lexer, val);

    unsigned long localsize = val;
    if (!matched) {
        return false;
    }
    eatup(lexer, "", 1);

    std::string id = "";

    if (!string(lexer, id))
        return false;

    insert(address, new Function(id, address, localsize));
    return true;
}

static bool userfuncs(yyFlexLexer &lexer, std::function<void(unsigned long, Function *)> insert) {
    double val;
    bool matched = match(LONG, lexer, val);

    unsigned long number = val;

    // If it didn't match, this won't run
    for (; number && matched; --number) {
        eatup(lexer, "", 1);
        matched = userfunc(lexer, insert);
    }

    return matched;
}

static bool libfuncs(yyFlexLexer &lexer, std::function<void(unsigned long, std::string &)> insert) {
    return strings(lexer, insert);
}

static bool magicnumber(yyFlexLexer &lexer) noexcept {
    double val;

    return match(LONG, lexer, val) && val == 340200501;
}

static void insert_string_array(unsigned long index, std::string &str) {
    cpu::pools.insert_string(index, str);
}

static void insert_number_array(unsigned long index, double num) {
    cpu::pools.insert_number(index, num);
}

static void insert_userfunc_array(unsigned long index, Function *func) {
    cpu::pools.insert_userfunc(index, func);
}

static void insert_libfunc_array(unsigned long index, std::string &id) {
    cpu::pools.insert_libfunc(index, id);
}

static bool arrays(yyFlexLexer &lexer) {
    if (!strings(lexer, insert_string_array))
        return false;
    eatup(lexer);

    if (!numbers(lexer, insert_number_array))
        return false;
    eatup(lexer);

    if (!userfuncs(lexer, insert_userfunc_array))
        return false;
    eatup(lexer);

    if (!libfuncs(lexer, insert_libfunc_array))
        return false;

    return true;
}

static void insert_instruction(instruction *instr) {
    cpu::code.insert(instr);
}

static bool operand_type(yyFlexLexer &lexer, char &type) {
    double val;
    bool matched = match(LONG, lexer, val);

    type = val;
    if (!matched) {
        return false;
    }

    return true;
}

static bool operand_value(yyFlexLexer &lexer, unsigned long &value) {
    double val;
    bool matched = match(LONG, lexer, val);

    if (!matched) {
        return false;
    }

    value = val;
    return true;
}

static bool code_instruction(yyFlexLexer &lexer, std::function<void(instruction *)> insert) {
    double val;
    bool matched = match(LONG, lexer, val);
    vmarg *arg1 = nullptr, *arg2 = nullptr, *result = nullptr;

    vmopcode opcode = static_cast<vmopcode>(val);
    if (!matched || val < 0 || static_cast<double>(opcode) != val) {
        return false;
    }

    char arg1_type, arg2_type, result_type;

    eatup(lexer, "", 1);
    operand_type(lexer, arg1_type);

    eatup(lexer, "", 1);
    operand_type(lexer, arg2_type);

    eatup(lexer, "", 1);
    operand_type(lexer, result_type);

    unsigned long value;

    eatup(lexer, "", 2);
    if (arg1_type != -1) {
        operand_value(lexer, value);
        arg1 = new vmarg(static_cast<vmarg_t>(arg1_type), value);

        if (arg1_type == vmarg_t::global_var && value + 1 > max_global)
            max_global = value + 1;
    } else {
        // If no argument present, eat up the -1
        operand_type(lexer, arg1_type);
    }

    eatup(lexer, "", 1);
    if (arg2_type != -1) {
        operand_value(lexer, value);
        arg2 = new vmarg(static_cast<vmarg_t>(arg2_type), value);

        if (arg2_type == vmarg_t::global_var && value + 1 > max_global)
            max_global = value + 1;
    } else {
        // If no argument present, eat up the -1
        operand_type(lexer, arg2_type);
    }

    eatup(lexer, "", 1);
    if (result_type != -1) {
        operand_value(lexer, value);
        result = new vmarg(static_cast<vmarg_t>(result_type), value);

        if (result_type == vmarg_t::global_var && value + 1 > max_global)
            max_global = value + 1;
    } else {
        // If no argument present, eat up the -1
        operand_type(lexer, arg1_type);
    }

    instruction *instr = new instruction(opcode, arg1, arg2, result);
    insert(instr);

    return true;
}

static bool code(yyFlexLexer &lexer) {
    double val;
    bool matched = match(LONG, lexer, val);

    unsigned long number = val;

    // If it didn't match, this won't run
    for (unsigned long i = 0; i < number && matched; ++i) {
        eatup(lexer, "", 1);
        code_instruction(lexer, insert_instruction);
    }

    cpu::topsp = 0;
    cpu::top = 4095 - max_global;

    return matched;
}

static bool globals(yyFlexLexer &lexer) {
    double val;
    bool matched = match(LONG, lexer, val);

    unsigned long number = val;
    if (!matched || static_cast<double>(number) != val) {
        return false;
    }

    cpu::topsp = 0;
    cpu::top = 4095 - number;

    return true;
}

static bool avmtextfile(std::ifstream &in_file) {
    yyFlexLexer lexer(in_file, std::cout);

    if (!magicnumber(lexer))
        return false;

    eatup(lexer);

    if (!globals(lexer))
        return false;

    eatup(lexer);

    if (!arrays(lexer))
        return false;

    eatup(lexer);

    if (!code(lexer))
        return false;

    return true;
}

bool load_text(std::ifstream &in_file) {
    assert(in_file.is_open());

    bool loaded = avmtextfile(in_file);
    if (loaded)
        cpu::code_size = cpu::code.size();
    return loaded;
}