#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include "lib/symbol.h"
#include "memory/memcell/memcell.hpp"
#include <functional>
#include <string>
#include <unordered_map>

class environment {
private:
    std::unordered_map<std::string, std::function<void()>> dispatch;

public:
    environment();
    ~environment();

    void call_save_environment();
    void call_libfunc(const std::string &);

    Function *get_funcinfo(unsigned long);
    unsigned long get_envvalue(unsigned long);
    std::function<void()> get_libfunc(const std::string &);

    unsigned long total_actuals();
    memcell *get_actual(unsigned long);

    void register_libfunc(const std::string &, std::function<void()>);
};

#endif /* __ENVIRONMENT_H */
