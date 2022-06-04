#include "lib/function.hpp"
#include <cassert>
#include <string>

std::string Function::to_string() {
    std::string result;

    result += "\"" + id + "\"\t";

    result += "[userfunction]\t\t";

    result += "(address " + std::to_string(taddress) + ")\t";
    result += "(local size " + std::to_string(totalLocals) + ")";

    return result;
}
