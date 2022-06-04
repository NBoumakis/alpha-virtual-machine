#include "memory/memcell/memcell.hpp"
#include "library/reporting/reporting.hpp"

// sub-class numberMemcell
numberMemcell::numberMemcell(double number) {
    setNumber(number);
}

void numberMemcell::setNumber(double number) {
    this->value = number;
}

double numberMemcell::getNumber(void) const {
    return this->value;
}

memcell_type numberMemcell::getType(void) const {
    return memcell_type::number_m;
}

std::string numberMemcell::getTypeName() const {
    return "number";
}

numberMemcell::operator std::string() const {}
numberMemcell::operator bool() const {}

bool numberMemcell::operator==(const memcell *op) const {
    // TODO
    assert(op);

    return (*this == *op);
}

// sub-class stringMemcell
stringMemcell::stringMemcell(const std::string &string) {
    setString(string);
}

void stringMemcell::setString(const std::string &string) {
    this->value = string;
}

std::string stringMemcell::getString(void) const {
    return this->value;
}

memcell_type stringMemcell::getType(void) const {
    return memcell_type::string_m;
}

std::string stringMemcell::getTypeName() const {
    return "string";
}

stringMemcell::operator std::string() const {}
stringMemcell::operator bool() const {}

bool stringMemcell::operator==(const memcell *op) const {
    // TODO
}

// sub-class boolMemcell
boolMemcell::boolMemcell(const bool boolean) {
    setBool(boolean);
}

void boolMemcell::setBool(const bool boolean) {
    this->value = boolean;
}

bool boolMemcell::getBool(void) const {
    return this->value;
}

memcell_type boolMemcell::getType(void) const {
    return memcell_type::bool_m;
}

std::string boolMemcell::getTypeName() const {
    return "bool";
}

boolMemcell::operator std::string() const {}
boolMemcell::operator bool() const {}

bool boolMemcell::operator==(const memcell *op) const {
    // TODO
}

// sub-class dynamicTableMemcell
dynamicTableMemcell::dynamicTableMemcell(dynamic_table *table) {
    setDynamicTable(table);
}

void dynamicTableMemcell::setDynamicTable(dynamic_table *table) {
    this->value = table;
}

dynamic_table *dynamicTableMemcell::getDynamicTable(void) const {
    return this->value;
}

memcell_type dynamicTableMemcell::getType(void) const {
    return memcell_type::table_m;
}

std::string dynamicTableMemcell::getTypeName() const {
    return "table";
}

dynamicTableMemcell::operator std::string() const {}
dynamicTableMemcell::operator bool() const {}

bool dynamicTableMemcell::operator==(const memcell *op) const {
    // TODO
}

// sub-class userfuncMemcell
userfuncMemcell::userfuncMemcell(const unsigned long userfunc) {
    setUserFunc(userfunc);
}

void userfuncMemcell::setUserFunc(const unsigned long userfunc) {
    this->value = userfunc;
}

unsigned long userfuncMemcell::getUserFunc(void) const {
    return this->value;
}

memcell_type userfuncMemcell::getType(void) const {
    return memcell_type::userfunc_m;
}

std::string userfuncMemcell::getTypeName() const {
    return "userfunc";
}

userfuncMemcell::operator std::string() const {}
userfuncMemcell::operator bool() const {}

bool userfuncMemcell::operator==(const memcell *op) const {
    // TODO
}

// sub-class libfuncMemcell
libfuncMemcell::libfuncMemcell(const std::string &libfunc) {
    setLibFunc(libfunc);
}

void libfuncMemcell::setLibFunc(const std::string &libfunc) {
    this->value = libfunc;
}

std::string libfuncMemcell::getLibFunc(void) const {
    return this->value;
}

memcell_type libfuncMemcell::getType(void) const {
    return memcell_type::libfunc_m;
}

std::string libfuncMemcell::getTypeName() const {
    return "libfunc";
}

libfuncMemcell::operator std::string() const {}
libfuncMemcell::operator bool() const {}

bool libfuncMemcell::operator==(const memcell *op) const {
    // TODO
}

// sub-class nilMemcell
memcell_type nilMemcell::getType(void) const {
    return memcell_type::nil_m;
}

std::string nilMemcell::getTypeName() const {
    return "nil";
}

nilMemcell::operator std::string() const {}
nilMemcell::operator bool() const {}

bool nilMemcell::operator==(const memcell *op) const {
    // TODO
}

// sub-class undefMemcell
memcell_type undefMemcell::getType(void) const {
    return memcell_type::undefined_m;
}

std::string nilMemcell::getTypeName() const {
    return "undefined";
}

bool undefMemcell::operator==(const memcell *op) const {
    // TODO
    assert(op);

    warning("Cannot assign from a undefined r-value");
}

// avm_assign
const std::unordered_map<memcell_type, std::function<memcell *(memcell const &)>> dispatch = {
    {memcell_type::number_m, [](memcell const &) -> memcell * { return new numberMemcell; }},
    {memcell_type::string_m, [](memcell const &) -> memcell * { return new stringMemcell; }},
    {memcell_type::bool_m, [](memcell const &) -> memcell * { return new boolMemcell; }},
    {memcell_type::table_m, [](memcell const &) -> memcell * { return new dynamicTableMemcell; }},
    {memcell_type::userfunc_m, [](memcell const &) -> memcell * { return new userfuncMemcell; }},
    {memcell_type::libfunc_m, [](memcell const &) -> memcell * { return new libfuncMemcell; }},
    {memcell_type::nil_m, [](memcell const &) -> memcell * { return new nilMemcell; }},
    {memcell_type::undefined_m, [](memcell const &) -> memcell * { return new undefMemcell; }},
};

memcell *assign(memcell *&lv, memcell *rv) {
    delete lv;

    lv = dispatch.at(rv->getType())(*rv);

    return lv;
}