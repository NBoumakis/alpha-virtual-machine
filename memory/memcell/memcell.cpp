#include "memory/memcell/memcell.hpp"
#include "library/reporting/reporting.hpp"

numberMemcell::numberMemcell(const double number) {
    setNumber(number);
}

void numberMemcell::setNumber(const double number) {
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

dynamicTableMemcell::dynamicTableMemcell(const dynamic_table table) {
    setDynamicTable(table);
}

void dynamicTableMemcell::setDynamicTable(const dynamic_table table) {
    this->value = table;
}

dynamic_table dynamicTableMemcell::getDynamicTable(void) const {
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

libfuncMemcell::libfuncMemcell(const std::string &libfunc) {
    setLibFunc(libfunc);
}

void libfuncMemcell::setLibFunc(const std::string &userfunc) {
    this->value = userfunc;
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

const std::unordered_map<memcell_type, std::function<memcell *(memcell const &)>> dispatch = {
    {memcell_type::number_m, [](memcell const &) -> memcell * { return new numberMemcell; }},
    {memcell_type::string_m, [](memcell const &) -> memcell * { return new stringMemcell; }},
    {memcell_type::bool_m, [](memcell const &) -> memcell * { return new boolMemcell; }},
    {memcell_type::table_m, [](memcell const &) -> memcell * { return new dynamicTableMemcell; }},
    {memcell_type::userfunc_m, [](memcell const &) -> memcell * { return new userfuncMemcell; }},
    {memcell_type::libfunc_m, [](memcell const &) -> memcell * { return new libfuncMemcell; }},
    {memcell_type::nil_m, [](memcell const &) -> memcell * { return new nilMemcell; }},
};

memcell *assign(memcell *&lv, memcell *rv) {
    delete lv;

    lv = dispatch.at(rv->getType())(*rv);

    return lv;
}