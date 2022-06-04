#include "code_segment.hpp"

unsigned long code_segment::size() {
    return instructions.size();
}

instruction &code_segment::operator[](unsigned long i) {
    return instructions.at(i);
}

void code_segment::insert(instruction &instr) {
    instructions.push_back(instr);
}
