#ifndef __TEMP_VARS_H
#define __TEMP_VARS_H

#include "lib/symbol.h"
#include <string>

std::string newtempname();

void resettemp();

Symbol *newTempvar();

#endif /* __TEMP_VARS_H */