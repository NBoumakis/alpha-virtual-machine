#include "executer/execute/execute_funcs_arithmetic.hpp"
#include "executer/cpu.hpp"
#include "executer/decode/decode.hpp"
#include "lib/colors.hpp"
#include "memory/memcell/memcell.hpp"
#include <assert.h>
#include <functional>
#include <unordered_map>

double add_impl(double x, double y) { return x + y; }
double sub_impl(double x, double y) { return x - y; }
double mul_impl(double x, double y) { return x * y; }
double div_impl(double x, double y) {
    if (y == 0) {
        // FIXME
        std::cerr << BRED "ERROR: Division by zero" RST << std::endl;
        cpu::execution_finished = true;
    }
    return x / y;
}
double mod_impl(double x, double y) {
    if (((long)y) == 0) {
        // FIXME
        std::cerr << BRED "ERROR: Division by zero" RST << std::endl;
        cpu::execution_finished = true;
    }
    return ((long)x) % ((long)y);
}

static std::unordered_map<vmopcode, std::function<double(double, double)>> arithm_funcs = {
    {add_vmiop, add_impl},
    {sub_vmiop, sub_impl},
    {mul_vmiop, mul_impl},
    {div_vmiop, div_impl},
    {mod_vmiop, mod_impl}};

void execute_arithmetic(instruction *instr) {
    memcell *&lv = translate_operand(instr->arg1);
    memcell *&rv1 = translate_operand(instr->arg2, cpu::ax);
    memcell *&rv2 = translate_operand(instr->result, cpu::bx);

    assert(rv1 && rv2 && lv);

    if (rv1->getType() != memcell_type::number_m || rv2->getType() != memcell_type::number_m) {
        // FIXME
        std::cerr << BRED "ERROR: arithmetic operation does not have operands of type number!" RST << std::endl;
        cpu::execution_finished = true;
    } else {
        lv = new numberMemcell();
        lv->setNumber((arithm_funcs.at(instr->opcode))(rv1->getNumber(), rv2->getNumber()));
    }
}
