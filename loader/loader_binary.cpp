#include "executer/cpu.hpp"
#include "lib/function.hpp"
#include "loader/loader.hpp"
#include "loader/text_scanner.hpp"
#include <cassert>
#include <functional>
#include <string>

static bool magicnumber(std::ifstream &in_file) {
    unsigned long ulong;

    in_file.read(reinterpret_cast<char *>(&ulong), sizeof(ulong));

    return ulong == 340200501 && in_file.good();
}

static bool globals(std::ifstream &in_file) {
    unsigned long ulong;

    in_file.read(reinterpret_cast<char *>(&ulong), sizeof(ulong));

    cpu::topsp = 0;
    cpu::top = 4095 - ulong;

    return in_file.good();
}

static bool string(std::ifstream &in_file, std::string &res) {
    unsigned long length;

    in_file.read(reinterpret_cast<char *>(&length), sizeof(length));
    if (!in_file.good()) {
        return false;
    }

    char *temp = new char[length + 1];
    in_file.read(temp, length);
    temp[length] = '\0';
    res = temp;
    delete[] temp;

    return in_file.good();
}

static bool strings(std::ifstream &in_file, std::function<void(unsigned long, std::string &)> insert) {
    unsigned long number;

    in_file.read(reinterpret_cast<char *>(&number), sizeof(number));

    bool load_success = in_file.good();

    for (unsigned long i = 0; i < number && load_success; ++i) {
        std::string res;
        load_success = string(in_file, res);
        if (load_success) {
            insert(i, res);
        }
    }

    return in_file.good();
}

static bool numbers(std::ifstream &in_file, std::function<void(unsigned long, double)> insert) {
    unsigned long number_count;
    in_file.read(reinterpret_cast<char *>(&number_count), sizeof(number_count));

    bool load_success = in_file.good();
    for (unsigned long i = 0; i < number_count && load_success; ++i) {
        double number;
        in_file.read(reinterpret_cast<char *>(&number), sizeof(number));

        load_success = in_file.good();
        if (load_success)
            insert(i, number);
    }

    return in_file.good();
}

static bool userfunc(std::ifstream &in_file, std::function<void(unsigned long, Function *)> insert) {
    unsigned long address;

    in_file.read(reinterpret_cast<char *>(&address), sizeof(address));

    if (!in_file.good()) {
        return false;
    }

    unsigned long localsize;

    in_file.read(reinterpret_cast<char *>(&localsize), sizeof(localsize));

    if (!in_file.good()) {
        return false;
    }

    std::string id;

    if (!string(in_file, id))
        return false;

    insert(address, new Function(id, address, localsize));
    return true;
}

static bool userfuncs(std::ifstream &in_file, std::function<void(unsigned long, Function *)> insert) {
    unsigned long number;

    in_file.read(reinterpret_cast<char *>(&number), sizeof(number));

    bool load_success = in_file.good();

    // If it didn't match, this won't run
    for (; number && load_success; --number) {
        load_success = userfunc(in_file, insert);
    }

    return load_success;
}

static bool libfuncs(std::ifstream &in_file, std::function<void(unsigned long, std::string &)> insert) {
    return strings(in_file, insert);
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

static bool arrays(std::ifstream &in_file) {
    return strings(in_file, insert_string_array) && numbers(in_file, insert_number_array) && userfuncs(in_file, insert_userfunc_array) && libfuncs(in_file, insert_libfunc_array);
}

static void insert_instruction(instruction *instr) {
    cpu::code.insert(instr);
}

static bool operand_type(std::ifstream &in_file, int &type) {
    in_file.read(reinterpret_cast<char *>(&type), sizeof(type));

    return in_file.good();
}

static bool operand_value(std::ifstream &in_file, unsigned long &value) {
    in_file.read(reinterpret_cast<char *>(&value), sizeof(value));
    return in_file.good();
}

static bool code_instruction(std::ifstream &in_file, std::function<void(instruction *)> insert) {
    int opcode_int;
    vmarg *arg1 = nullptr, *arg2 = nullptr, *result = nullptr;

    in_file.read(reinterpret_cast<char *>(&opcode_int), sizeof(opcode_int));
    vmopcode opcode = static_cast<vmopcode>(opcode_int);

    if (!in_file.good() || opcode_int < 0 || static_cast<int>(opcode) != opcode_int) {
        return false;
    }

    int arg1_type, arg2_type, result_type;

    operand_type(in_file, arg1_type);
    operand_type(in_file, arg2_type);
    operand_type(in_file, result_type);

    unsigned long value;

    if (arg1_type != -1) {
        if (operand_value(in_file, value))
            arg1 = new vmarg(static_cast<vmarg_t>(arg1_type), value);
        else
            return false;
    }

    if (arg2_type != -1) {
        if (operand_value(in_file, value))
            arg2 = new vmarg(static_cast<vmarg_t>(arg2_type), value);
        else
            return false;
    }

    if (result_type != -1) {
        if (operand_value(in_file, value))
            result = new vmarg(static_cast<vmarg_t>(result_type), value);
        else
            return false;
    }

    instruction *instr = new instruction(opcode, arg1, arg2, result);
    insert(instr);

    return true;
}

static bool code(std::ifstream &in_file) {
    unsigned long instruction_n;

    in_file.read(reinterpret_cast<char *>(&instruction_n), sizeof(instruction_n));

    // If it didn't match, this won't run
    for (unsigned long i = 0; i < instruction_n && in_file.good(); ++i) {
        code_instruction(in_file, insert_instruction);
    }

    return in_file.good();
}

static bool avmbinaryfile(std::ifstream &in_file) {
    if (!magicnumber(in_file))
        return false;

    if (!globals(in_file))
        return false;

    if (!arrays(in_file))
        return false;

    if (!code(in_file))
        return false;

    return true;
}

bool load_binary(std::ifstream &in_file) {
    assert(in_file.is_open());

    bool loaded = avmbinaryfile(in_file);
    if (loaded)
        cpu::code_size = cpu::code.size();
    return loaded;
}