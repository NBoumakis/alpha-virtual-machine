#ifndef __DECODE_H
#define __DECODE_H

#include "lib/vmarg.h"
#include "memory/memcell/memcell.hpp"

memcell *translate_operand(vmarg *arg, memcell *reg);

#endif /* __DECODE_H */