#include "memory/const_values/const_values.hpp"

void const_values::insert_number(unsigned long key, double val) {
    this->number_pool.insert({key, val});
}

void const_values::insert_string(unsigned long key, std::string val) {
    this->string_pool.insert({key, val});
}

void const_values::insert_libfunc(unsigned long key, std::string val) {
    this->libfunc_pool.insert({key, val});
}

void const_values::insert_userfunc(unsigned long key, Function *val) {
    this->userfunc_pool.insert({key, val});
}

double &const_values::get_number(unsigned long key) {
    return this->number_pool.at(key);
}

std::string &const_values::get_string(unsigned long key) {
    return this->string_pool.at(key);
}

std::string &const_values::get_libfunc(unsigned long key) {
    return this->libfunc_pool.at(key);
}

Function *&const_values::get_userfunc(unsigned long key) {
    return this->userfunc_pool.at(key);
}