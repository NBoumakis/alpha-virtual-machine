#ifndef __EXECUTE_H
#define __EXECUTE_H

#include "lib/instruction.hpp"
#include <functional>
#include <unordered_map>

class execute {
private:
    std::unordered_map<vmopcode, std::function<void(instruction *)>> dispatch;

public:
    execute();
    ~execute() = default;

    std::function<void(instruction *)> operator[](vmopcode);
};

#endif /* __EXECUTE_H */