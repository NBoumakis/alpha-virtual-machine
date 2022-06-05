#include "executer/cpu.hpp"

unsigned long cpu::pc, cpu::topsp, cpu::top, cpu::code_size;
memcell *cpu::ax = new undefMemcell(), *cpu::bx = new undefMemcell(), *cpu::cx, *cpu::retval = new undefMemcell();
program_stack cpu::stack;
environment cpu::env;
code_segment cpu::code;
const_values cpu::pools;
bool cpu::execution_finished;
execute cpu::executer;

void cpu::cycle() {
    if (cpu::execution_finished)
        return;

    if (cpu::pc == cpu::code_size) {
        execution_finished = true;
        return;
    } else {
        assert(cpu::pc < cpu::code_size);

        instruction *instr = cpu::code[pc];
        assert(instr &&
               instr->opcode >= 0 &&
               instr->opcode <= vmopcode::nop_vmiop);

        unsigned long oldPC = pc;
        cpu::executer[instr->opcode](instr);
        if (oldPC == pc)
            ++pc;
    }
}