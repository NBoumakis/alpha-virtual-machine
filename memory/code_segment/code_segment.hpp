#ifndef __CODE_SEGMENT_HPP
#define __CODE_SEGMENT_HPP

#include "lib/instruction.hpp"
#include <deque>

class code_segment {
private:
    std::deque<instruction *> instructions;

public:
    code_segment() = default;
    ~code_segment() = default;

    void insert(instruction *&);
    instruction *&operator[](unsigned long);

    unsigned long size();
};

#endif /* __CODE_SEGMENT_HPP */