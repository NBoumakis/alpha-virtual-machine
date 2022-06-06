#include "executer/decode/decode.hpp"
#include "executer/cpu.hpp"

memcell *&translate_operand(const vmarg *arg, memcell *&reg) {
    switch (arg->type) {
    case global_var:
        return cpu::stack[cpu::stack.size() - 1 - arg->val];

    case local_var:
        return cpu::stack[cpu::topsp - arg->val];

    case formal_arg:
        return cpu::stack[cpu::topsp + 4 + 1 + arg->val];

    case retval:
        return cpu::retval;
    case const_num:
        delete reg;
        reg = new numberMemcell(cpu::pools.get_number(arg->val));
        return reg;

    case const_str:
        delete reg;
        reg = new stringMemcell(cpu::pools.get_string(arg->val));
        return reg;

    case const_bool:
        delete reg;
        reg = new boolMemcell(arg->val);
        return reg;

    case const_nil:
        delete reg;

        reg = new nilMemcell();
        return reg;

    case user_func:
        delete reg;
        reg = new userfuncMemcell(arg->val);
        return reg;

    case lib_func:
        delete reg;
        reg = new libfuncMemcell(cpu::pools.get_libfunc(arg->val));
        return reg;

    default:
        assert(false);
    }
}

memcell *&translate_operand(const vmarg *arg) {
    switch (arg->type) {
    case global_var:
        return cpu::stack[cpu::stack.size() - 1 - arg->val];

    case local_var:
        return cpu::stack[cpu::topsp - arg->val];

    case formal_arg:
        return cpu::stack[cpu::topsp + 4 + 1 + arg->val];

    case retval:
        return cpu::retval;

    default:
        assert(false);
    }
}
