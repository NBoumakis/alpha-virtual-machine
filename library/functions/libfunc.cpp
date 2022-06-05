#include "executer/cpu.hpp"
#include "memory/memcell/memcell.hpp"

void libfunc_typeof() {
    unsigned long num_of_actuals = cpu::env.get_totalactuals();

    if (num_of_actuals != 1) {
        // FIXME
        std::cerr << "ERROR: one argument (not " << num_of_actuals << ") expected in 'typeof'";
        cpu::execution_finished = true;
    } else {
        delete cpu::retval;
        cpu::retval = new stringMemcell(cpu::env.get_actual(0UL)->getTypeName());
    }
}

void libfunc_print() {
    unsigned long num_of_actuals = cpu::env.get_totalactuals();

    for (unsigned long i = 0; i < num_of_actuals; i++) {
        std::string s = static_cast<std::string>(*cpu::env.get_actual(i));
    }
}
void libfunc_totalarguments() {
    unsigned long p_topsp = cpu::env.get_envvalue(cpu::topsp + 1); // AVM_SAVEDTOPSP_OFFSET
    delete cpu::retval;

    if (!p_topsp) {
        // FIXME
        std::cerr << "ERROR: 'totalarguments' called outside a function !";
        cpu::execution_finished = true;
        cpu::retval = new nilMemcell();
    } else {
        cpu::retval = new numberMemcell(cpu::env.get_envvalue(p_topsp + 4)); // AVM_NUMACTUALS_OFFSET
    }
}
