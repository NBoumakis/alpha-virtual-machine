#include "library/environment/environment.hpp"
#include "executer/cpu.hpp"

void environment::call_save_environment() {
    cpu::stack.push(new numberMemcell(total_actuals));
    cpu::stack.push(new numberMemcell(cpu::pc + 1));
    cpu::stack.push(new numberMemcell(cpu::top + total_actuals + 2));
    cpu::stack.push(new numberMemcell(cpu::topsp));
}

void environment::call_libfunc(const std::string &id) {
    std::function<void()> func;

    try {
        func = dispatch.at(id);

        cpu::topsp = cpu::top;
        total_actuals = 0;

        func();

        if (!cpu::execution_finished)
            cpu::executer[funcexit_vmiop](nullptr);
    } catch (const std::out_of_range &e) {
        std::cerr << "ERROR: unsupported lib function " << id << " called!" << std::endl;
        cpu::execution_finished = true;
    }
}
