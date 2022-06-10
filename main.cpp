#include "executer/cpu.hpp"
#include "library/functions/libfunc.hpp"
#include "loader/loader.hpp"
#include <algorithm>
#include <fstream>

void init_libfuncs() {
    cpu::env.register_libfunc("print", libfunc_print);
    cpu::env.register_libfunc("totalarguments", libfunc_totalarguments);
    cpu::env.register_libfunc("typeof", libfunc_typeof);
    cpu::env.register_libfunc("input", libfunc_input);
    cpu::env.register_libfunc("objectmemberkeys", libfunc_objectmemberkeys);
    cpu::env.register_libfunc("objecttotalmembers", libfunc_objecttotalmembers);
    cpu::env.register_libfunc("objectcopy", libfunc_objectcopy);
    cpu::env.register_libfunc("sqrt", libfunc_sqrt);
    cpu::env.register_libfunc("cos", libfunc_cos);
    cpu::env.register_libfunc("sin", libfunc_sin);
    cpu::env.register_libfunc("strtonum", libfunc_strtonum);
    cpu::env.register_libfunc("argument", libfunc_argument);
}

char *getCmdOption(char **begin, char **end, const std::string &option) {
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return nullptr;
}

bool cmdOptionExists(char **begin, char **end, const std::string &option) {
    return std::find(begin, end, option) != end;
}

int main(int argc, char *argv[]) {
    char *in_fname = getCmdOption(argv, argv + argc, "--in");
    bool is_text = cmdOptionExists(argv, argv + argc, "--text");

    if (in_fname) {
        if (is_text) {
            std::ifstream in_file(in_fname);

            if (!in_file.is_open()) {
                std::cerr << "Cannot open file " << in_fname << " for reading." << std::endl;
                return -1;
            }

            if (!load_text(in_file)) {
                std::cerr << "Error loading text-formatted executable " << in_fname << "." << std::endl;
                return -1;
            }
        } else {
            std::ifstream in_file(in_fname, std::ios::in | std::ios::binary);

            if (!in_file.is_open()) {
                std::cerr << "Cannot open file " << in_fname << " for reading." << std::endl;
                return -1;
            }

            if (!load_text(in_file)) {
                std::cerr << "Error loading binary executable " << in_fname << "." << std::endl;
                return -1;
            }
        }
    } else {
        std::cerr << "No argument found for mandatory option --in." << std::endl;

        return -1;
    }

    init_libfuncs();

    while (!cpu::execution_finished) {
        cpu::cycle();
    }
}