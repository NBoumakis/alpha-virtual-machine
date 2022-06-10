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