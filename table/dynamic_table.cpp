#include "table/dynamic_table.hpp"
#include "executer/cpu.hpp"
#include "memory/memcell/memcell.hpp"

dynamic_table::dynamic_table() {
    refCounter = 0;
}

memcell *dynamic_table::get_elem(const memcell *key) const {
    switch (key->getType()) {

    case memcell_type::number_m: {
        auto res = numIndexed.find(key->getNumber());
        if (res != numIndexed.end()) {
            return res->second;
        } else {
            return nullptr;
        }
    }
    case memcell_type::string_m: {
        auto res = strIndexed.find(key->getString());
        if (res != strIndexed.end()) {
            return res->second;
        } else {
            return nullptr;
        }
    }

    case memcell_type::bool_m: {
        auto res = boolIndexed.find(key->getBool());
        if (res != boolIndexed.end()) {
            return res->second;
        } else {
            return nullptr;
        }
    }

    case memcell_type::userfunc_m: {
        auto res = userfuncIndexed.find(key->getUserFunc());
        if (res != userfuncIndexed.end()) {
            return res->second;
        } else {
            return nullptr;
        }
    }

    case memcell_type::libfunc_m: {
        auto res = libfuncIndexed.find(key->getLibFunc());
        if (res != libfuncIndexed.end()) {
            return res->second;
        } else {
            return nullptr;
        }
    }

    default:
        assert(false);
    }
}

void dynamic_table::set_elem(const memcell *key, memcell *value) {
    switch (key->getType()) {
    case memcell_type::number_m: {
        auto loc = numIndexed.find(key->getNumber());

        if (value->getType() != memcell_type::nil_m) {
            if (loc != numIndexed.end()) {
                delete loc->second;
                loc->second = value->copy(value);
            } else
                numIndexed.insert({key->getNumber(), value->copy(value)});
        } else if (loc != numIndexed.end()) {
            delete loc->second;
            numIndexed.erase(key->getNumber());
        }

        break;
    }

    case memcell_type::string_m: {
        auto loc = strIndexed.find(key->getString());
        if (value->getType() != memcell_type::nil_m) {
            if (loc != strIndexed.end()) {
                delete loc->second;
                loc->second = value->copy(value);
            } else
                strIndexed.insert({key->getString(), value->copy(value)});
        } else if (loc != strIndexed.end()) {
            delete loc->second;
            strIndexed.erase(key->getString());
        }
        break;
    }

    case memcell_type::bool_m: {
        auto loc = boolIndexed.find(key->getBool());
        if (value->getType() != memcell_type::nil_m) {
            if (loc != boolIndexed.end()) {
                delete loc->second;
                loc->second = value->copy(value);
            } else
                boolIndexed.insert({key->getBool(), value->copy(value)});
        } else if (loc != boolIndexed.end()) {
            delete loc->second;
            boolIndexed.erase(key->getBool());
        }
        break;
    }

    case memcell_type::userfunc_m: {
        auto loc = userfuncIndexed.find(key->getUserFunc());
        if (value->getType() != memcell_type::nil_m) {
            if (loc != userfuncIndexed.end()) {
                delete loc->second;
                loc->second = value->copy(value);
            } else
                userfuncIndexed.insert({key->getUserFunc(), value->copy(value)});
        } else if (loc != userfuncIndexed.end()) {
            delete loc->second;
            userfuncIndexed.erase(key->getUserFunc());
        }
        break;
    }

    case memcell_type::libfunc_m: {
        auto loc = libfuncIndexed.find(key->getLibFunc());
        if (value->getType() != memcell_type::nil_m) {
            if (loc != libfuncIndexed.end()) {
                delete loc->second;
                loc->second = value->copy(value);
            } else
                libfuncIndexed.insert({key->getLibFunc(), value->copy(value)});
        } else if (loc != libfuncIndexed.end()) {
            delete loc->second;
            libfuncIndexed.erase(key->getLibFunc());
        }
        break;
    }

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

memcell *dynamic_table::get_keys() const {
    memcell *res = new dynamicTableMemcell(new dynamic_table());

    unsigned long i = 0;
    for (auto &&elem : this->numIndexed) {
        res->getDynamicTable()->set_elem(new numberMemcell(i), new numberMemcell(elem.first));
        ++i;
    }

    for (auto &&elem : this->strIndexed) {
        res->getDynamicTable()->set_elem(new numberMemcell(i), new stringMemcell(elem.first));
        ++i;
    }

    for (auto &&elem : this->boolIndexed) {
        res->getDynamicTable()->set_elem(new numberMemcell(i), new boolMemcell(elem.first));
        ++i;
    }

    for (auto &&elem : this->userfuncIndexed) {
        res->getDynamicTable()->set_elem(new numberMemcell(i), new userfuncMemcell(elem.first));
        ++i;
    }

    for (auto &&elem : this->libfuncIndexed) {
        res->getDynamicTable()->set_elem(new numberMemcell(i), new libfuncMemcell(elem.first));
        ++i;
    }

    return res;
}

static void string_num_element(std::map<double, memcell *>::const_iterator elem, std::string &res) {
    res += "\t" + std::to_string(static_cast<unsigned long>(elem->first)) + ":\t" +
           static_cast<std::string>(*elem->second);
}

static void string_str_element(std::map<std::string, memcell *>::const_iterator elem, std::string &res) {
    res += "\n\t{ \"" + elem->first + "\":\t";
    res += static_cast<std::string>(*elem->second) + " }";
}

static void string_bool_element(std::map<bool, memcell *>::const_iterator elem, std::string &res) {
    res += "\n\t{ ";
    res += ((elem->first) ? "true" : "false");
    res += ":\t" + static_cast<std::string>(*elem->second) + " }";
}

static void string_userfunc_element(std::map<unsigned long, memcell *>::const_iterator elem, std::string &res) {
    res += "\n\t{ ";
    res += cpu::env.get_funcinfo(elem->first)->id;
    res += ":\t" + static_cast<std::string>(*elem->second) + " }";
}

void dynamic_table::numIndexed_toString(std::string &res) const {
    auto elem = this->numIndexed.begin();

    if (elem != this->numIndexed.end()) {
        res += "\n";
        string_num_element(elem, res);

        ++elem;
    }
    for (; elem != this->numIndexed.end(); ++elem) {
        res += ",\n";
        string_num_element(elem, res);
    }
}

void dynamic_table::strIndexed_toString(std::string &res) const {
    auto elem = this->strIndexed.begin();

    if (elem != this->strIndexed.end()) {
        string_str_element(elem, res);

        ++elem;
    }
    for (; elem != this->strIndexed.end(); ++elem) {
        res += ",";
        string_str_element(elem, res);
    }
}

void dynamic_table::boolIndexed_toString(std::string &res) const {
    auto elem = this->boolIndexed.begin();

    if (elem != this->boolIndexed.end()) {
        string_bool_element(elem, res);

        ++elem;
    }
    for (; elem != this->boolIndexed.end(); ++elem) {
        res += ",";
        string_bool_element(elem, res);
    }
}

void dynamic_table::userfuncIndexed_toString(std::string &res) const {
    auto elem = this->userfuncIndexed.begin();

    if (elem != this->userfuncIndexed.end()) {
        string_userfunc_element(elem, res);

        ++elem;
    }
    for (; elem != this->userfuncIndexed.end(); ++elem) {
        res += ",";
        string_userfunc_element(elem, res);
    }
}

void dynamic_table::libfuncIndexed_toString(std::string &res) const {
    auto elem = this->libfuncIndexed.begin();

    if (elem != this->libfuncIndexed.end()) {
        string_str_element(elem, res);

        ++elem;
    }
    for (; elem != this->libfuncIndexed.end(); ++elem) {
        res += ",";
        string_str_element(elem, res);
    }
}

std::string dynamic_table::to_string() const {
    std::string res = "[";

    numIndexed_toString(res);
    strIndexed_toString(res);
    boolIndexed_toString(res);
    userfuncIndexed_toString(res);
    libfuncIndexed_toString(res);

    res += "]";

    return res;
}

unsigned long dynamic_table::size() const {
    return this->numIndexed.size() + this->strIndexed.size();
}
