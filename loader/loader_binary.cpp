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

    in_file.read(reinterpret_cast<char *>(length), sizeof(length));
    if (!in_file.good()) {
        return false;
    }

    char temp[length + 1];
    in_file.read(temp, length);
    temp[length] = '\0';
    res = temp;

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