#include "executer/cpu.hpp"

unsigned long cpu::pc, cpu::topsp, cpu::top, cpu::code_size;
memcell *cpu::ax, *cpu::bx, *cpu::cx, *cpu::retval;
program_stack cpu::stack;
environment cpu::env;
code_segment cpu::code;
const_values cpu::pools;
bool cpu::execution_finished;