#include "lib/vmarg.hpp"
#include <cassert>

vmarg::vmarg(vmarg_t type) {
    this->type = type;
}

vmarg::vmarg(vmarg_t type, unsigned long val) {
    this->type = type;
    this->val = val;
}
