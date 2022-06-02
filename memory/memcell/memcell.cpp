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