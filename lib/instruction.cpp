#include "lib/instruction.hpp"

#include <string>

instruction::instruction(vmopcode op, vmarg *arg1 = nullptr, vmarg *arg2 = nullptr, vmarg *result = nullptr)
    : opcode(op), arg1(arg1), arg2(arg2), result(result) {}

std::string vmopcode_name[] = {"assign",
                               "add",
                               "sub",
                               "mul",
                               "div",
                               "mod",
                               "uminus",
                               "and",
                               "or",
                               "not",
                               "jump",
                               "jeq",
                               "jne",
                               "jle",
                               "jge",
                               "jlt",
                               "jgt",
                               "call",
                               "pusharg",
                               "funcenter",
                               "funcexit",
                               "newtable",
                               "table_getelem",
                               "table_setelem",
                               "nop"};
