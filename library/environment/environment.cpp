#include "library/environment/environment.hpp"
#include "executer/cpu.hpp"
#include "lib/colors.hpp"

static void push_envvalue(unsigned long val) {
    numberMemcell tmp(val);
    cpu::stack.push(&tmp);
}

void environment::call_save_environment() {
    push_envvalue(total_actuals);
    push_envvalue(cpu::pc + 1);
    push_envvalue(cpu::top + total_actuals + 2);
    push_envvalue(cpu::topsp);
}

void environment::call_libfunc(const std::string &id) {
    std::function<void()> func;

    try {
        func = dispatch.at(id);
    } catch (const std::out_of_range &e) {
        std::cerr << BRED "ERROR: Unsupported lib function " << id << " called!" RST << std::endl;
        cpu::execution_finished = true;
    }

    if (!cpu::execution_finished) {
        cpu::topsp = cpu::top;
        total_actuals = 0;

        func();

        // cpu::execution_finished might change in func, recheck
        if (!cpu::execution_finished)
            cpu::executer[funcexit_vmiop](nullptr);
    }
}

Function *environment::get_funcinfo(unsigned long address) {
    return cpu::pools.get_userfunc(address);
}

unsigned long environment::get_envvalue(unsigned long index) {
    assert(cpu::stack[index]->getType() == memcell_type::number_m);

    unsigned long val = static_cast<unsigned long>(cpu::stack[index]->getNumber());
    assert(static_cast<double>(val) == cpu::stack[index]->getNumber());

    return val;
}

memcell *&environment::get_actual(unsigned long i) {
    assert(i < get_totalactuals());

    return cpu::stack[cpu::topsp + 4 + 1 + i];
}

unsigned long environment::get_totalactuals() {
    return get_envvalue(cpu::topsp + 4);
}

void environment::register_libfunc(const std::string &id, std::function<void()> libfunc) {
    this->dispatch.insert({id, libfunc});
}