#ifndef __DECODE_H
#define __DECODE_H

#include "lib/vmarg.hpp"
#include "memory/memcell/memcell.hpp"

memcell *&translate_operand(vmarg *arg, memcell *&reg);

memcell *&translate_operand(vmarg *arg);

#endif /* __DECODE_H */