#include "lib/instruction.hpp"
#include <deque>

class code_segment {
private:
    std::deque<instruction> instructions;

public:
    code_segment();
    ~code_segment();

    void insert(instruction &);
    instruction &operator[](unsigned long);

    unsigned long size();
};
