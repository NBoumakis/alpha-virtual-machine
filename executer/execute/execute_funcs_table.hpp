#ifndef __EXECUTE_FUNCS_TABLE_H
#define __EXECUTE_FUNCS_TABLE_H

#include "lib/instruction.hpp"

extern void execute_newtable(instruction *);

extern void execute_tablegetelem(instruction *);

extern void execute_tablesetelem(instruction *);

#endif /* __EXECUTE_FUNCS_TABLE_H */
