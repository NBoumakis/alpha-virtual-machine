#ifndef __PROGRAM_STACK_H
#define __PROGRAM_STACK_H

#include "memory/memcell/memcell.hpp"
#include <deque>

class program_stack {
private:
    std::deque<memcell *> stack;

public:
    program_stack();
    ~program_stack();

    void push(memcell *);
    memcell *pop();

    memcell *operator[](unsigned long);

    unsigned long size();
};

#endif /* __PROGRAM_STACK_H */
