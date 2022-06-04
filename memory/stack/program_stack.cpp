#include "memory/stack/program_stack.hpp"

void program_stack::push(memcell *cell) {
    this->stack.push_front(cell);
}

memcell *program_stack::pop() {
    auto top = this->stack.front();

    this->stack.pop_front();

    return top;
}

memcell *&program_stack::operator[](unsigned long index) {
    return this->stack.at(index);
}

unsigned long program_stack::size() {
    return this->stack.size();
}
