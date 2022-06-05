#include "executer/cpu.hpp"
#include "loader/loader.hpp"
#include <fstream>

int main() {
    std::ifstream in_file("bin.abc");

    load_text(in_file);

    while (!cpu::execution_finished) {
        cpu::cycle();
    }
}