#include "execute_funcs_relational.hpp"
#include "executer/cpu.hpp"
#include "memory/memcell/memcell.hpp"
#include <assert.h>
#include <functional>
#include <unordered_map>

bool jle_impl(double x, double y) { return x <= y; }
bool jge_impl(double x, double y) { return x >= y; }
bool jlt_impl(double x, double y) { return x < y; }
bool jgt_impl(double x, double y) { return x > y; }

static std::unordered_map<vmopcode, std::function<bool(double, double)>> ordered_funcs = {
    {jle_vmiop, jle_impl},
    {jge_vmiop, jge_impl},
    {jlt_vmiop, jlt_impl},
    {jgt_vmiop, jgt_impl}};

void execute_ordered(instruction *instr) {
    memcell *rv1 = translate_operand(instr->arg1, cpu::ax);
    memcell *rv2 = translate_operand(instr->arg1, cpu::bx);
    bool result;

    assert(rv1 && rv2);

    if (rv1->getType() == memcell_type::number_m && rv2->getType() == memcell_type::number_m) {
        result = ordered_funcs.at(instr->opcode)(rv1->getNumber(), rv2->getNumber());
    } else {
        // error : only numbers
    }

    if (!cpu::execution_finished && result)
        cpu::pc = instr->result->val;
}