#include "executer/execute/execute_funcs_table.hpp"
#include "executer/cpu.hpp"
#include "executer/decode/decode.hpp"
#include "memory/memcell/memcell.hpp"
#include "table/dynamic_table.hpp"
#include <assert.h>

void execute_newtable(instruction *instr) {
    memcell *lv = translate_operand(instr->result);
    assert(lv);

    lv = new dynamicTableMemcell();
    lv->getDynamicTable()->inc_ref_counter();
}

void execute_tablegetelem(instruction *instr) {
    memcell *lv = translate_operand(instr->result);
    memcell *t = translate_operand(instr->arg1);
    memcell *i = translate_operand(instr->arg2, cpu::ax);

    assert(lv || lv == cpu::retval);
    assert(t && t > cpu::stack[cpu::top]);

    assert(i);

    if (t->getType() != memcell_type::table_m) {
        // FIXME
        std::cerr << "ERROR: illegal use of type " << t->getTypeName() << "as table !";
        assign(lv, new nilMemcell());
    } else {
        memcell *content = t->getDynamicTable()->get_elem(i);

        if (content) {
            assign(lv, content);
        } else {
            assign(lv, new nilMemcell());
            std::string ts = static_cast<std::string>(*t);
            std::string is = static_cast<std::string>(*i);
            // FIXME
            std::cerr << "WARNING: " << ts << "[" << is << "] not found!";
        }
    }
}

void execute_tablesetelem(instruction *instr) {
    memcell *t = translate_operand(instr->result);
    memcell *i = translate_operand(instr->arg1, cpu::ax);
    memcell *c = translate_operand(instr->arg2, cpu::bx);

    assert(t && c && i);

    if (t->getType() != memcell_type::table_m) {
        // FIXME
        std::cerr << "ERROR: illegal use of type " << t->getTypeName() << " as table!";
    } else {
        t->getDynamicTable()->set_elem(i, c);
    }
}
