#ifndef __VMARGS_H
#define __VMARGS_H

#include <string>

enum vmarg_t { instruction_label,
               global_var,
               formal_arg,
               local_var,
               const_num,
               const_str,
               const_bool,
               const_nil,
               user_func,
               lib_func,
               retval };

class vmarg {
public:
    vmarg_t type;
    unsigned long val;

    vmarg(vmarg_t type);
    vmarg(vmarg_t type, unsigned long val);
};

#endif /* __VMARGS_H */