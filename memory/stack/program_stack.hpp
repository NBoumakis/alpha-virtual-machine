#ifndef __PROGRAM_STACK_H
#define __PROGRAM_STACK_H

#include "memory/memcell/memcell.hpp"
#include <deque>

class program_stack {
private:
    std::deque<memcell *> stack;
    unsigned long stack_size = 0;

public:
    program_stack() {
        stack.resize(4096);
        for (size_t i = 0; i < 4096; ++i) {
            stack.at(i) = new undefMemcell();
        }
    };
    ~program_stack() = default;

    void push(memcell *);
    void pop(unsigned long i);

    memcell *&operator[](unsigned long);

    // unsigned long size();
};

#endif /* __PROGRAM_STACK_H */
