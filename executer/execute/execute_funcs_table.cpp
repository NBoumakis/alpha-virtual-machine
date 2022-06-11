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
        std::cerr << BRED "ERROR: Cannot index " << t->getTypeName() << "!" RST << std::endl;
        cpu::execution_finished = true;
        assign(lv, new nilMemcell());
    } else {
        memcell_type key_type = i->getType();
        if (key_type != memcell_type::string_m &&
            key_type != memcell_type::number_m &&
            key_type != memcell_type::bool_m &&
            key_type != memcell_type::userfunc_m &&
            key_type != memcell_type::libfunc_m) {
            assign(lv, new nilMemcell());
            std::cerr << BRED "ERROR: Key type " << i->getTypeName() << " is not supported!" RST << std::endl;
            cpu::execution_finished = true;
            return;
        }

        memcell *content = t->getDynamicTable()->get_elem(i);

        if (content) {
            assign(lv, content);
        } else {
            assign(lv, new nilMemcell());
            std::string ts = static_cast<std::string>(*t);
            std::string is = static_cast<std::string>(*i);
            std::cerr << BYEL "WARNING: Key " << is << " not in table " << ts << "!" RST << std::endl;
        }
    }
}

void execute_tablesetelem(instruction *instr) {
    memcell *&c = translate_operand(instr->arg1, cpu::bx);
    memcell *&t = translate_operand(instr->arg2);
    memcell *&i = translate_operand(instr->result, cpu::ax);

    assert(t && c && i);

    if (t->getType() != memcell_type::table_m) {
        std::cerr << BRED "ERROR: Cannot index " << t->getTypeName() << ". Not a table!" RST << std::endl;
        cpu::execution_finished = true;
    } else {
        memcell_type key_type = i->getType();
        if (key_type != memcell_type::string_m &&
            key_type != memcell_type::number_m &&
            key_type != memcell_type::bool_m &&
            key_type != memcell_type::userfunc_m &&
            key_type != memcell_type::libfunc_m) {
            std::cerr << BRED "ERROR: Key type " << i->getTypeName() << " is not supported!" RST << std::endl;
            cpu::execution_finished = true;
            return;
        }

        t->getDynamicTable()->set_elem(i, c);
    }
}
