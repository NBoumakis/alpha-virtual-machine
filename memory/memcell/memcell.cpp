#include "memory/memcell/memcell.hpp"

static memcell *assign(memcell *&lv, memcell *rv);

void numberMemcell::setNumber(const double number) {
    this->value = number;
}
double numberMemcell::getNumber(void) const override {
    return this->value;
}