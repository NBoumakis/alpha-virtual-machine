#include "executer/execute/execute_funcs_table.hpp"
#include "executer/cpu.hpp"
#include "executer/decode/decode.hpp"
#include "lib/colors.hpp"
#include "memory/memcell/memcell.hpp"
#include "table/dynamic_table.hpp"
#include <assert.h>

void execute_newtable(instruction *instr) {
    memcell *&lv = translate_operand(instr->arg1);
    assert(lv);

    delete lv;

    lv = new dynamicTableMemcell(new dynamic_table());
    lv->getDynamicTable()->inc_ref_counter();
}

void execute_tablegetelem(instruction *instr) {
    memcell *&lv = translate_operand(instr->arg1);
    memcell *&t = translate_operand(instr->arg2);
    memcell *&i = translate_operand(instr->result, cpu::ax);

    assert(lv);
    assert(t);
    assert(i);

    if (t->getType() != memcell_type::table_m) {
        // FIXME
        std::cerr << BRED "ERROR: cannot get the element of a non-table operand with name " << t->getTypeName() << "!" RST << std::endl;
        cpu::execution_finished = true;
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
            std::cerr << BYEL "WARNING: the value of table " << ts << " with key " << is << " is undefined!" RST << std::endl;
        }
    }
}

void execute_tablesetelem(instruction *instr) {
    memcell *&c = translate_operand(instr->arg1, cpu::bx);
    memcell *&t = translate_operand(instr->arg2);
    memcell *&i = translate_operand(instr->result, cpu::ax);

    assert(t && c && i);

    if (t->getType() != memcell_type::table_m) {
        // FIXME
        std::cerr << BRED "ERROR: " << t->getTypeName() << " cannot be a value to the table with key " << i->getTypeName() << "!" RST << std::endl;
        cpu::execution_finished = true;
    } else {
        t->getDynamicTable()->set_elem(i, c);
    }
}
