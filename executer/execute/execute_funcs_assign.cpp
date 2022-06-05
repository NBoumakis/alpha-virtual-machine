#include "executer/execute/execute_funcs_assign.hpp"
#include "executer/cpu.hpp"
#include "executer/decode/decode.hpp"
#include "memory/memcell/memcell.hpp"
#include <assert.h>

void execute_assign(instruction *instr) {
    memcell *lv = translate_operand(instr->result);
    memcell *rv = translate_operand(instr->arg1, cpu::ax);

    assert(lv && rv);

    assign(lv, rv);
}
