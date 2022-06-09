#include "memory/memcell/memcell.hpp"
#include "library/reporting/reporting.hpp"
#include "table/dynamic_table.hpp"

#include "executer/cpu.hpp"

// sub-class numberMemcell
numberMemcell::numberMemcell(double number) {
    this->value = number;
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

memcell *numberMemcell::copy(memcell const *b) {
    assert(b->getType() == memcell_type::number_m);

    return new numberMemcell(*dynamic_cast<numberMemcell const *>(b));
}

numberMemcell::operator std::string() const {
    return std::to_string(this->value);
}

numberMemcell::operator bool() const {
    return this->value != 0;
}

bool numberMemcell::operator==(const memcell *op) const {
    assert(op && op->getType() == memcell_type::number_m);

    return this->value == op->getNumber();
}

// sub-class stringMemcell
stringMemcell::stringMemcell(const std::string &str) {
    this->value = str;
}

void stringMemcell::setString(const std::string &str) {
    this->value = str;
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

memcell *stringMemcell::copy(memcell const *b) {
    assert(b->getType() == memcell_type::string_m);

    return new stringMemcell(*dynamic_cast<stringMemcell const *>(b));
}

stringMemcell::operator std::string() const {
    return this->value;
}

stringMemcell::operator bool() const {
    return this->value != "";
}

bool stringMemcell::operator==(const memcell *op) const {
    assert(op && op->getType() == memcell_type::string_m);

    return this->value == op->getString();
}

// sub-class boolMemcell
boolMemcell::boolMemcell(const bool boolean) {
    this->value = boolean;
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

memcell *boolMemcell::copy(memcell const *b) {
    return new boolMemcell(*dynamic_cast<boolMemcell const *>(b));
}

boolMemcell::operator std::string() const {
    return (this->value) ? "true" : "false";
}
boolMemcell::operator bool() const {
    return this->value;
}

bool boolMemcell::operator==(const memcell *op) const {
    assert(op && op->getType() == memcell_type::bool_m);

    return this->value == op->getBool();
}

// sub-class dynamicTableMemcell
dynamicTableMemcell::dynamicTableMemcell(dynamic_table *table) {
    this->value = table;
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

memcell *dynamicTableMemcell::copy(memcell const *b) {
    assert(b->getType() == memcell_type::table_m);

    return new dynamicTableMemcell(*dynamic_cast<dynamicTableMemcell const *>(b));
}

dynamicTableMemcell::operator std::string() const {
    return this->value->to_string();
}

dynamicTableMemcell::operator bool() const {
    return true;
}

bool dynamicTableMemcell::operator==(const memcell *op) const {
    // Redundant to check equality with nil
    assert(op && op->getType() == memcell_type::table_m);

    return true;
}

// sub-class userfuncMemcell
userfuncMemcell::userfuncMemcell(const unsigned long userfunc) {
    this->value = userfunc;
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

memcell *userfuncMemcell::copy(memcell const *b) {
    return new userfuncMemcell(*dynamic_cast<userfuncMemcell const *>(b));
}

userfuncMemcell::operator std::string() const {
    return "user function " + std::to_string(this->value);
}
userfuncMemcell::operator bool() const {
    return true;
}

bool userfuncMemcell::operator==(const memcell *op) const {
    assert(op && op->getType() == memcell_type::userfunc_m);

    return (this->value == op->getUserFunc());
}

// sub-class libfuncMemcell
libfuncMemcell::libfuncMemcell(const std::string &libfunc) {
    this->value = libfunc;
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

memcell *libfuncMemcell::copy(memcell const *b) {
    assert(b->getType() == memcell_type::libfunc_m);

    return new libfuncMemcell(*dynamic_cast<libfuncMemcell const *>(b));
}

libfuncMemcell::operator std::string() const {
    return "library function " + this->value;
}

libfuncMemcell::operator bool() const {
    return true;
}

bool libfuncMemcell::operator==(const memcell *op) const {
    assert(op && op->getType() != memcell_type::libfunc_m);

    return (this->value == op->getLibFunc());
}

// sub-class nilMemcell
memcell_type nilMemcell::getType(void) const {
    return memcell_type::nil_m;
}

std::string nilMemcell::getTypeName() const {
    return "nil";
}

memcell *nilMemcell::copy(memcell const *b) {
    assert(b && b->getType() == memcell_type::nil_m);

    return new nilMemcell(*dynamic_cast<nilMemcell const *>(b));
}

nilMemcell::operator std::string() const {
    return "nil";
}

nilMemcell::operator bool() const {
    return false;
}

bool nilMemcell::operator==(const memcell *op) const {
    assert(op && op->getType() == memcell_type::nil_m);

    return false;
}

// sub-class undefMemcell
memcell_type undefMemcell::getType(void) const {
    return memcell_type::undefined_m;
}

std::string undefMemcell::getTypeName() const {
    return "undefined";
}

memcell *undefMemcell::copy(memcell const *b) {
    return new undefMemcell(*dynamic_cast<undefMemcell const *>(b));
}

undefMemcell::operator std::string() const {
    return "undefined";
}

undefMemcell::operator bool() const {
    assert(false);
}

bool undefMemcell::operator==(const memcell *op) const {
    assert(false);
}

memcell *assign(memcell *&lv, memcell *rv) {
    if (lv == rv)
        return lv;

    if (lv->getType() == memcell_type::table_m &&
        rv->getType() == memcell_type::table_m &&
        lv->getDynamicTable() == rv->getDynamicTable())
        return lv;

    if (rv != cpu::retval && rv->getType() == memcell_type::undefined_m)
        std::cerr << "Warning: Assigning from 'undefined'!" << std::endl;

    delete lv;

    lv = rv->copy(rv);

    if (lv->getType() == memcell_type::table_m)
        lv->getDynamicTable()->inc_ref_counter();

    return lv;
}