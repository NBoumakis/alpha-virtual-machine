#ifndef __SYMBOL_H
#define __SYMBOL_H

#include <string>

class Function {
public:
    std::string id;
    unsigned long taddress;
    unsigned long totalLocals;

public:
    Function(std::string &id, unsigned long taddress, unsigned long localSize)
        : id(id), taddress(taddress), totalLocals(localSize) {}

    std::string to_string();
    std::string type_string();
};

#endif /* __SYMBOL_H */