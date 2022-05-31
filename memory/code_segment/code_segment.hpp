#include "instruction/instruction.hpp"
#include <vector>

class code_segment {
private:
    std::vector<instruction> instructions;

public:
    code_segment(/* args */);
    ~code_segment();
};

code_segment::code_segment(/* args */) {
}

code_segment::~code_segment() {
}
