#include "library/environment/environment.hpp"
#include "executer/cpu.hpp"

void environment::call_save_environment() {
    cpu::stack.push(new numberMemcell(total_actuals));
    cpu::stack.push(new numberMemcell(cpu::pc + 1));
    cpu::stack.push(new numberMemcell(cpu::top + total_actuals + 2));
    cpu::stack.push(new numberMemcell(cpu::topsp));
}
