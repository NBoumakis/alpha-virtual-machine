#include "executer/cpu.hpp"
#include "library/functions/libfunc.hpp"
#include "loader/loader.hpp"
#include <fstream>

int main() {
    std::ifstream in_file("bin.abc");

    load_text(in_file);

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

    while (!cpu::execution_finished) {
        cpu::cycle();
    }
}