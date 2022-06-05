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

static void string_num_element(std::unordered_map<double, memcell *>::const_iterator elem, std::string &res) {
    res += "\n\t" + std::to_string(elem->first) + ":\t";

    if (elem->second->getType() == memcell_type::string_m)
        res += "\"" + static_cast<std::string>(*elem->second) + "\"";
    else
        res += static_cast<std::string>(*elem->second);
}

static void string_str_element(std::unordered_map<std::string, memcell *>::const_iterator elem, std::string &res) {
    res += "\n\t{ \"" + elem->first + "\":\t";

    if (elem->second->getType() == memcell_type::string_m)
        res += "\"" + static_cast<std::string>(*elem->second) + "\" }";
    else
        res += static_cast<std::string>(*elem->second);
}

void dynamic_table::numIndexed_toString(std::string &res) const {
    auto elem = this->numIndexed.begin();

    if (elem != this->numIndexed.end()) {
        string_num_element(elem, res);

        ++elem;
    }
    for (; elem != this->numIndexed.end(); ++elem) {
        res += ",";
        string_num_element(elem, res);
    }
}

void dynamic_table::strIndexed_toString(std::string &res) const {
    auto elem = this->strIndexed.begin();

    if (elem != this->strIndexed.end()) {
        res += ",";
        string_str_element(elem, res);

        ++elem;
    }
    for (; elem != this->strIndexed.end(); ++elem) {
        res += ",";
        string_str_element(elem, res);
    }
}

std::string dynamic_table::to_string() const {
    std::string res = "[";

    numIndexed_toString(res);
    strIndexed_toString(res);

    res += "]";

    return res;
}