#include "memory/stack/program_stack.hpp"
#include "executer/cpu.hpp"

void program_stack::push(memcell *cell) {
    if (!cpu::top) {
        std::cerr << "ERROR: Stack overflow" << std::endl;
        cpu::execution_finished = true;
    } else {
        this->stack.at(cpu::top--) = cell;
    }
}

void program_stack::pop(unsigned long i) {
    this->stack.at(i) = new undefMemcell();
}

memcell *&program_stack::operator[](unsigned long index) {
    return this->stack.at(index);
}

// unsigned long program_stack::size() {
//     return this->stack_size;
// }
