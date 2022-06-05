#include "table/dynamic_table.hpp"
#include "memory/memcell/memcell.hpp"

dynamic_table::dynamic_table() {
    refCounter = 0;
}

dynamic_table::~dynamic_table() {
    strIndexed.clear();

    numIndexed.clear();
}

memcell *dynamic_table::get_elem(const memcell *key) const {
    switch (key->getType()) {

    case memcell_type::number_m:
        return numIndexed.at(key->getNumber());

    case memcell_type::string_m:
        return strIndexed.at(key->getString());

    default:
        assert(false);
    }
}

void dynamic_table::set_elem(const memcell *key, memcell *value) {

    switch (key->getType()) {

    case memcell_type::number_m:
        numIndexed.insert({key->getNumber(), value});
        break;

    case memcell_type::string_m:
        strIndexed.insert({key->getString(), value});
        break;

    default:
        assert(false);
    }
}

void dynamic_table::inc_ref_counter() {
    ++refCounter;
}

void dynamic_table::dec_ref_counter() {
    assert(refCounter > 0);

    if (!(--refCounter)) {
        delete this;
    }
}