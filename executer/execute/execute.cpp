#include "executer/execute/execute.hpp"
#include "executer/execute/execute_funcs_arithmetic.hpp"
#include "executer/execute/execute_funcs_assign.hpp"
#include "executer/execute/execute_funcs_function.hpp"
#include "executer/execute/execute_funcs_nop.hpp"
#include "executer/execute/execute_funcs_relational.hpp"
#include "executer/execute/execute_funcs_table.hpp"

execute::execute() {
    dispatch.insert({assign_vmiop, execute_assign});

    dispatch.insert({add_vmiop, execute_arithmetic});
    dispatch.insert({sub_vmiop, execute_arithmetic});
    dispatch.insert({mul_vmiop, execute_arithmetic});
    dispatch.insert({div_vmiop, execute_arithmetic});
    dispatch.insert({mod_vmiop, execute_arithmetic});

    dispatch.insert({jump_vmiop, execute_jump});
    dispatch.insert({jeq_vmiop, execute_jeq});
    dispatch.insert({jne_vmiop, execute_jne});
    dispatch.insert({jle_vmiop, execute_ordered});
    dispatch.insert({jge_vmiop, execute_ordered});
    dispatch.insert({jlt_vmiop, execute_ordered});
    dispatch.insert({jgt_vmiop, execute_ordered});

    dispatch.insert({call_vmiop, execute_call});
    dispatch.insert({pusharg_vmiop, execute_pusharg});
    dispatch.insert({funcenter_vmiop, execute_funcenter});
    dispatch.insert({funcexit_vmiop, execute_funcexit});

    dispatch.insert({newtable_vmiop, execute_newtable});
    dispatch.insert({table_getelem_vmiop, execute_tablegetelem});
    dispatch.insert({table_setelem_vmiop, execute_tablesetelem});

    dispatch.insert({nop_vmiop, execute_nop});
}

std::function<void(instruction *)> execute::operator[](vmopcode op) {
    return dispatch.at(op);
}