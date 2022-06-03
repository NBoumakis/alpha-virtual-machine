#include "table/dynamic_table.hpp"

dynamic_table::dynamic_table() {
    refCounter = 0;
}

dynamic_table::~dynamic_table() {
    for (auto &memObj : strIndexed) {
        memObj.second->~memcell();
    }

    strIndexed.clear();

    for (auto &memObj : numIndexed) {
        memObj.second->~memcell();
    }

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

void dynamic_table::set_elem(const memcell *key, const memcell *value) {

    switch (key->getType()) {

    case memcell_type::number_m:
        numIndexed.insert(key, value);
        break;

    case memcell_type::string_m:
        strIndexed.insert(key, value);
        break;

    default:
        assert(false);
    }
}

void dynamic_table::inc_ref_counter() {
    ++refCounter;
}

void dynamic_table::dec_ref_counter() {
    dynamic_table obj;
    assert(refCounter > 0);

    if (!(--refCounter)) {
        obj.~dynamic_table();
    }
}