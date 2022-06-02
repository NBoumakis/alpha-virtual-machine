#include "memory/memcell/memcell.hpp"

static memcell *assign(memcell *&lv, memcell *rv);

numberMemcell::numberMemcell(const double number) {
    setNumber(number);
}

void numberMemcell::setNumber(const double number) {
    this->value = number;
}

double numberMemcell::getNumber(void) const override {
    return this->value;
}

memcell_type numberMemcell::getType(void) const override {
    return memcell_type::number_m;
}

std::string numberMemcell::getTypeName() const override {
    return "number";
}

stringMemcell::stringMemcell(const std::string &string) {
    setString(string);
}

void stringMemcell::setString(const std::string &string) {
    this->value = string;
}

std::string stringMemcell::getString(void) const override {
    return this->value;
}

memcell_type stringMemcell::getType(void) const override {
    return memcell_type::string_m;
}

std::string stringMemcell::getTypeName() const override {
    return "string";
}

boolMemcell::boolMemcell(const bool boolean) {
    setBool(boolean);
}

void boolMemcell::setBool(const bool boolean) {
    this->value = boolean;
}

bool boolMemcell::getBool(void) const override {
    return this->value;
}

memcell_type boolMemcell::getType(void) const override {
    return memcell_type::bool_m;
}

std::string boolMemcell::getTypeName() const override {
    return "bool";
}

dynamicTableMemcell::dynamicTableMemcell(const dynamic_table table) {
    setDynamicTable(table);
}

void dynamicTableMemcell::setDynamicTable(const dynamic_table table) {
    this->value = table;
}

dynamic_table dynamicTableMemcell::getDynamicTable(void) const override {
    return this->value;
}

memcell_type dynamicTableMemcell::getType(void) const override {
    return memcell_type::table_m;
}

std::string dynamicTableMemcell::getTypeName() const override {
    return "table";
}

userfuncMemcell::userfuncMemcell(const unsigned long userfunc) {
    setUserFunc(userfunc);
}

void userfuncMemcell::setUserFunc(const unsigned long userfunc) {
    this->value = userfunc;
}

unsigned long userfuncMemcell::getUserFunc(void) const override {
    return this->value;
}

memcell_type userfuncMemcell::getType(void) const override {
    return memcell_type::userfunc_m;
}

std::string userfuncMemcell::getTypeName() const override {
    return "userfunc";
}

libfuncMemcell::libfuncMemcell(const std::string &libfunc) {
    setLibFunc(libfunc);
}

void libfuncMemcell::setLibFunc(const std::string &userfunc) {
    this->value = userfunc;
}

std::string libfuncMemcell::getLibFunc(void) const override {
    return this->value;
}