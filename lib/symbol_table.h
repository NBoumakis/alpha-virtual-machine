#ifndef __SYMBOL_TABLE_H
#define __SYMBOL_TABLE_H

#include "lib/scope.h"
#include "lib/symbol.h"
#include <unordered_set>

extern Scope symbolTableObj;
extern unsigned int scopeLevel;
extern std::unordered_set<std::string> libFunctions;

bool isLibFunction(std::string name);

extern unsigned int funcDepth;

void initSymbolTable();
#endif