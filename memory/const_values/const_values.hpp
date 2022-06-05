#ifndef __CONST_VALUES_H
#define __CONST_VALUES_H

#include "lib/function.hpp"
#include <string>
#include <unordered_map>

class const_values {
private:
    std::unordered_map<unsigned long, double> number_pool;
    std::unordered_map<unsigned long, std::string> string_pool;
    std::unordered_map<unsigned long, std::string> libfunc_pool;
    std::unordered_map<unsigned long, Function *> userfunc_pool;

public:
    const_values() = default;
    ~const_values() = default;

    void insert_number(unsigned long, double);
    void insert_string(unsigned long, std::string);
    void insert_libfunc(unsigned long, std::string);
    void insert_userfunc(unsigned long, Function *);

    double &get_number(unsigned long);
    std::string &get_string(unsigned long);
    std::string &get_libfunc(unsigned long);
    Function *&get_userfunc(unsigned long);
};

#endif /* __CONST_VALUES_H */