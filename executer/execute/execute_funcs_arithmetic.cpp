#include "executer/execute/execute_funcs_arithmetic.hpp"
#include "executer/cpu.hpp"
#include "executer/decode/decode.hpp"
#include "memory/memcell/memcell.hpp"
#include <assert.h>
#include <functional>
#include <unordered_map>

double add_impl(double x, double y) { return x + y; }
double sub_impl(double x, double y) { return x - y; }
double mul_impl(double x, double y) { return x * y; }
// TODO error checking
double div_impl(double x, double y) { return x / y; }
double mod_impl(double x, double y) { return ((unsigned)x) % ((unsigned)y); }

static std::unordered_map<vmopcode, std::function<double(double, double)>> arithm_funcs = {
    {add_vmiop, add_impl},
    {sub_vmiop, sub_impl},
    {mul_vmiop, mul_impl},
    {div_vmiop, div_impl},
    {mod_vmiop, mod_impl}};

void execute_arithmetic(instruction *instr) {
    memcell *lv = translate_operand(instr->result);
    memcell *rv1 = translate_operand(instr->arg1, cpu::ax);
    memcell *rv2 = translate_operand(instr->arg1, cpu::bx);

    assert(rv1 && rv2 && lv);

    if (rv1->getType() != memcell_type::number_m || rv2->getType() != memcell_type::number_m) {
        // FIXME
        std::cerr << "ERROR: not a number in arithmetic !";
        cpu::execution_finished = 1;
    } else {
        lv = new numberMemcell();
        lv->setNumber((arithm_funcs.at(instr->opcode))(rv1->getNumber(), rv2->getNumber()));
    }
}
