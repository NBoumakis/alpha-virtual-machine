#include "loader/loader.hpp"
#include "executer/cpu.hpp"
#include "lib/function.hpp"
#include <algorithm>
#include <cassert>
#include <unordered_map>

bool is_number(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

static bool magicnumber(std::ifstream &in_file) noexcept {
    unsigned number;

    if (in_file >> number) {
        return number == 340200501;
    }

    return false;
}

static bool globals(std::ifstream &in_file) {
    unsigned long number;

    in_file >> number;
    cpu::topsp = cpu::top = 4095 - number;

    return true;
}

static std::string string(std::ifstream &in_file) {
    std::string token;

    in_file >> token;

    if (!is_number(token)) {
        throw std::out_of_range("Invalid size, not an integer");
    }

    unsigned long total = std::stoul(token);

    /*
    char str[total + 1];
    in_file.get(str, total + 1);

    return std::string(str);
    */
    in_file >> token;

    return token;
}

static bool strings(std::ifstream &in_file, std::unordered_map<unsigned long, std::string> &buf) {
    unsigned long total;
    std::string token;

    in_file >> token;

    if (!is_number(token)) {
        throw std::out_of_range("Invalid number of string, not an integer");
    }

    total = std::stoul(token);

    for (unsigned long i = total; i; --i) {
        try {
            buf.insert({total - i, string(in_file)});
        } catch (const std::out_of_range &e) {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    return true;
}

static bool numbers(std::ifstream &in_file) noexcept {
    unsigned long total;
    std::string token;

    in_file >> token;

    if (!is_number(token)) {
        throw std::out_of_range("Invalid number of string, not an integer");
    }

    total = std::stoul(token);

    for (unsigned long i = total; i; --i) {
        double number;

        try {
            in_file >> token;
            number = std::stod(token);
        } catch (const std::invalid_argument &e) {
            return false;
        }

        cpu::pools.insert_number(total - i, number);
    }

    return true;
}

static bool userFunctions(std::ifstream &in_file) {
    unsigned long total;
    std::string token;

    in_file >> token;

    if (!is_number(token)) {
        throw std::out_of_range("Invalid number of string, not an integer");
    }

    total = std::stoul(token);

    for (unsigned long i = total; i; --i) {
        unsigned long address, localsize;

        try {
            in_file >> token;
            address = std::stoul(token);
        } catch (const std::invalid_argument &e) {
            return false;
        }

        try {
            in_file >> token;
            localsize = std::stoul(token);
        } catch (const std::invalid_argument &e) {
            return false;
        }

        in_file >> token;

        cpu::pools.insert_userfunc(address, new Function(token, address, localsize));
    }

    return true;
}

static bool libfunctions(std::ifstream &in_file) {
    std::unordered_map<unsigned long, std::string> string_map;

    try {
        if (strings(in_file, string_map)) {
            for (auto &str : string_map) {
                cpu::pools.insert_libfunc(str.first, str.second);
            }
        } else {
            return false;
        }
    } catch (const std::out_of_range &e) {
        std::cerr << e.what() << '\n';
        return false;
    }

    return true;
}

static bool arrays(std::ifstream &in_file) noexcept {
    std::unordered_map<unsigned long, std::string> string_map;

    try {
        if (strings(in_file, string_map)) {
            for (auto &str : string_map) {
                cpu::pools.insert_string(str.first, str.second);
            }
        } else {
            return false;
        }
    } catch (const std::out_of_range &e) {
        std::cerr << e.what() << '\n';
        return false;
    }

    string_map.clear();

    try {
        if (!numbers(in_file)) {
            return false;
        }
    } catch (const std::out_of_range &e) {
        std::cerr << e.what() << '\n';
        return false;
    }

    return userFunctions(in_file) && libfunctions(in_file);
}

static bool code(std::ifstream &in_file) noexcept {
    unsigned long total;
    std::string token;

    in_file >> token;

    if (!is_number(token)) {
        return false;
    }

    total = std::stoul(token);

    for (unsigned long i = total; i; --i) {
        vmopcode op;
        std::string arg1TypeStr, arg2TypeStr, resultTypeStr;
        vmarg *arg1 = nullptr, *arg2 = nullptr, *result = nullptr;

        // Read opcode
        in_file >> token;
        op = static_cast<vmopcode>(std::stoi(token));

        // Read argument types
        in_file >> arg1TypeStr >> arg2TypeStr >> resultTypeStr;

        // Parse arguments
        try {
            in_file >> token;
            if (arg1TypeStr != "-1") {
                if (arg1TypeStr != std::to_string(vmarg_t::user_func))
                    arg1 = new vmarg(static_cast<vmarg_t>(std::stoi(arg1TypeStr)), std::stoul(token));
                else
                    arg1 = new vmarg(static_cast<vmarg_t>(std::stoi(arg1TypeStr)), cpu::pools.get_userfunc(std::stoul(token))->taddress);
            }

            in_file >> token;
            if (arg2TypeStr != "-1") {
                arg2 = new vmarg(static_cast<vmarg_t>(std::stoi(arg2TypeStr)), std::stoul(token));
            }

            in_file >> token;
            if (resultTypeStr != "-1") {
                result = new vmarg(static_cast<vmarg_t>(std::stoi(resultTypeStr)), std::stoul(token));
            }
        } catch (const std::invalid_argument &e) {
            std::cerr << e.what() << '\n';

            return false;
        }

        instruction *instr = new instruction(op, arg1, arg2, result);
        cpu::code.insert(instr);
    }

    return true;
}

static bool parse_text(std::ifstream &in_file) {
    assert(in_file.is_open());

    return magicnumber(in_file) && globals(in_file) && arrays(in_file) && code(in_file);
}

bool load_text(std::ifstream &in_file) {
    assert(in_file.is_open());

    bool loaded = parse_text(in_file);
    if (loaded)
        cpu::code_size = cpu::code.size();
    return loaded;
}