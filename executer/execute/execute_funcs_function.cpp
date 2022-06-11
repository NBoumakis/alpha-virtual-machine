#include "executer/execute/execute_funcs_function.hpp"
#include "executer/cpu.hpp"
#include "executer/decode/decode.hpp"
#include "lib/colors.hpp"
#include "library/environment/environment.hpp"
#include "memory/memcell/memcell.hpp"
#include <assert.h>
#include <iostream>

void execute_call(instruction *instr) {
    memcell *&func = translate_operand(instr->arg1, cpu::ax);
    assert(func);

    cpu::env.call_save_environment();

    switch (func->getType()) {
    case memcell_type::userfunc_m: {
        cpu::pc = func->getUserFunc();
        assert(cpu::pc < cpu::code_size);
        assert(cpu::code[cpu::pc]->opcode == funcenter_vmiop);
        break;
    }

    case memcell_type::string_m: {
        cpu::env.call_libfunc(func->getString());
        break;
    }

    case memcell_type::libfunc_m: {
        cpu::env.call_libfunc(func->getLibFunc());
        break;
    }

    default: {
        std::cerr << BRED "ERROR: Variable at offset " << instr->arg1->val << " is not a function!" RST << std::endl;
        cpu::execution_finished = true;
    }
    }
}

void execute_pusharg(instruction *instr) {
    memcell *arg = translate_operand(instr->arg1, cpu::ax);
    assert(arg);

    cpu::stack.push(arg);
    ++cpu::env.total_actuals;
}

void execute_funcenter(instruction *instr) {
    memcell *&func = translate_operand(instr->arg1, cpu::ax);
    assert(func);
    assert(cpu::pc == func->getUserFunc());

    cpu::env.total_actuals = 0;
    Function *func_info = cpu::env.get_funcinfo(cpu::pc);
    cpu::topsp = cpu::top;
    cpu::top = cpu::top - func_info->totalLocals;
}
void execute_funcexit(instruction *unused) {
    unsigned long oldTop = cpu::top;

    cpu::top = cpu::env.get_envvalue(cpu::topsp + 2);   // AVM_SAVEDTOP_OFFSET
    cpu::pc = cpu::env.get_envvalue(cpu::topsp + 3);    // AVM_SAVEDPC_OFFSET
    cpu::topsp = cpu::env.get_envvalue(cpu::topsp + 1); // AVM_SAVEDTOPSP_OFFSET

    while (++oldTop <= cpu::top) {
        cpu::stack.pop(oldTop);
    }
}