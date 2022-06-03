#ifndef __EXECUTE_FUNCS_RELATIONAL_H
#define __EXECUTE_FUNCS_RELATIONAL_H

#include "lib/instruction.hpp"

extern void execute_jeq(instruction *);

extern void execute_jne(instruction *);

extern void execute_ordered(instruction *);

#endif /* __EXECUTE_FUNCS_RELATIONAL_H */
