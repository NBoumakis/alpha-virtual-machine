#include "executer/cpu.hpp"
#include "lib/function.hpp"
#include "loader/loader.hpp"
#include "loader/text_scanner.hpp"
#include <cassert>
#include <functional>
#include <string>

bool load_binary(std::ifstream &in_file) {
    assert(in_file.is_open());

    bool loaded = avmbinaryfile(in_file);
    if (loaded)
        cpu::code_size = cpu::code.size();
    return loaded;
}