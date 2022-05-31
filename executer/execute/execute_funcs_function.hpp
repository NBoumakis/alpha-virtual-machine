#ifndef __EXECUTE_FUNCS_FUNCTION_H
#define __EXECUTE_FUNCS_FUNCTION_H

#include "lib/instruction.hpp"

extern void execute_call(instruction *);

extern void execute_pusharg(instruction *);

extern void execute_funcenter(instruction *);

extern void execute_funcexit(instruction *);

#endif /* __EXECUTE_FUNCS_FUNCTION_H */
