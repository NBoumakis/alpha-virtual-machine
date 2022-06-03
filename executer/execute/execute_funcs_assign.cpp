#include "execute_funcs_assign.hpp"
#include "cpu.hpp"
#include "decode.hpp"
#include "memcell.hpp"
#include <assert.h>

void execute_assign(instruction *instr) {
    memcell *lv = translate_operand(instr->result, (memcell *)nullptr);
    memcell *rv = translate_operand(instr->arg1, cpu::ax);

    assert(lv && rv);

    assign(lv, rv);
}
