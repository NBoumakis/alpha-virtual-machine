#include "memory/memcell/memcell.hpp"

static memcell *assign(memcell *&lv, memcell *rv);

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