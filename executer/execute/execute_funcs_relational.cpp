#include "executer/execute/execute_funcs_relational.hpp"
#include "executer/cpu.hpp"
#include "executer/decode/decode.hpp"
#include "lib/colors.hpp"
#include "lib/vmarg.hpp"
#include "memory/memcell/memcell.hpp"
#include <cassert>
#include <functional>
#include <unordered_map>

void execute_jump(instruction *instr) {
    cpu::pc = instr->result->val;
}

void execute_jeq(instruction *instr) {

    assert(instr->result->type == vmarg_t::instruction_label);

    memcell *&rv1 = translate_operand(instr->arg1, cpu::ax);
    memcell *&rv2 = translate_operand(instr->arg2, cpu::bx);
    bool result;

    if (rv1->getType() == memcell_type::undefined_m || rv2->getType() == memcell_type::undefined_m) {
        // FIXME
        std::cerr << BRED "ERROR: Cannot perform equality comparison on an undefined operand!" RST << std::endl;
        cpu::execution_finished = true;
    } else if (rv1->getType() == memcell_type::nil_m || rv2->getType() == memcell_type::nil_m) {
        result = (rv1->getType() == memcell_type::nil_m) && (rv2->getType() == memcell_type::nil_m);
    } else if (rv1->getType() == memcell_type::bool_m || rv2->getType() == memcell_type::bool_m) {
        result = (static_cast<bool>(*rv1) == static_cast<bool>(*rv2));
    } else if (rv1->getType() != rv2->getType()) {
        // FIXME
        std::cerr << BRED "ERROR: Cannot perform equality comparison between " << rv1->getTypeName() << " and " << rv2->getTypeName() << "!" RST << std::endl;
        cpu::execution_finished = true;
    } else {
        result = (*rv1 == *rv2);
    }

    if (!cpu::execution_finished && result)
        cpu::pc = instr->result->val;
}

void execute_jne(instruction *instr) {

    assert(instr->result->type == vmarg_t::instruction_label);

    memcell *&rv1 = translate_operand(instr->arg1, cpu::ax);
    memcell *&rv2 = translate_operand(instr->arg2, cpu::bx);
    bool result;

    if (rv1->getType() == memcell_type::undefined_m || rv2->getType() == memcell_type::undefined_m) {
        // FIXME
        std::cerr << BRED "ERROR: Cannot perform inequality comparison on an undefined operand!" RST << std::endl;
        cpu::execution_finished = true;
    } else if (rv1->getType() == memcell_type::nil_m || rv2->getType() == memcell_type::nil_m) {
        result = (rv1->getType() == memcell_type::nil_m) && (rv2->getType() == memcell_type::nil_m);
    } else if (rv1->getType() == memcell_type::bool_m || rv2->getType() == memcell_type::bool_m) {
        result = (static_cast<bool>(*rv1) != static_cast<bool>(*rv2));
    } else if (rv1->getType() != rv2->getType()) {
        // FIXME
        std::cerr << BRED "ERROR: Cannot perform inequality comparison between " << rv1->getTypeName() << " and " << rv2->getTypeName() << "!" RST << std::endl;
        cpu::execution_finished = true;
    } else {
        result = (*rv1 != *rv2);
    }

    if (!cpu::execution_finished && result)
        cpu::pc = instr->result->val;
}

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
    memcell *&rv1 = translate_operand(instr->arg1, cpu::ax);
    memcell *&rv2 = translate_operand(instr->arg2, cpu::bx);
    bool result;

    assert(rv1 && rv2);

    if (rv1->getType() == memcell_type::number_m && rv2->getType() == memcell_type::number_m) {
        result = ordered_funcs.at(instr->opcode)(rv1->getNumber(), rv2->getNumber());
    } else {
        // FIXME
        std::cerr << BRED "ERROR: Cannot compare operands that are not numbers" RST << std::endl;
        cpu::execution_finished = true;
    }

    if (!cpu::execution_finished && result)
        cpu::pc = instr->result->val;
}
