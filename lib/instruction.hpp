#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include "lib/vmarg.hpp"

enum vmopcode {
    assign_vmiop,
    add_vmiop,
    sub_vmiop,
    mul_vmiop,
    div_vmiop,
    mod_vmiop,
    uminus_vmiop,
    and_vmiop,
    or_vmiop,
    not_vmiop,
    jump_vmiop,
    jeq_vmiop,
    jne_vmiop,
    jle_vmiop,
    jge_vmiop,
    jlt_vmiop,
    jgt_vmiop,
    call_vmiop,
    pusharg_vmiop,
    funcenter_vmiop,
    funcexit_vmiop,
    newtable_vmiop,
    table_getelem_vmiop,
    table_setelem_vmiop,
    nop_vmiop
};

class instruction {
public:
    vmopcode opcode;
    vmarg *arg1;
    vmarg *arg2;
    vmarg *result;
    unsigned long srcLine;

    instruction(vmopcode, vmarg *, vmarg *, vmarg *);
};

#endif /* __INSTRUCTION_H */