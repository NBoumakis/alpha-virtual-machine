#include "memory/stack/program_stack.hpp"
#include "executer/cpu.hpp"
#include "lib/colors.hpp"

void program_stack::push(memcell *cell) {
    if (!cpu::top) {
        std::cerr << BRED "ERROR: Stack overflow" RST << std::endl;
        cpu::execution_finished = true;
    } else {
        assign(this->stack.at(cpu::top--), cell);
    }
}

void program_stack::pop(unsigned long i) {
    this->stack.at(i) = new undefMemcell();
}

memcell *&program_stack::operator[](unsigned long index) {
    return this->stack.at(index);
}
