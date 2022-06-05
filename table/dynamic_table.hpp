#ifndef __DYNAMIC_TABLE_H
#define __DYNAMIC_TABLE_H

#include <cassert>
#include <string>
#include <unordered_map>

class memcell;

class dynamic_table {
private:
    unsigned long refCounter;
    std::unordered_map<std::string, memcell *> strIndexed;
    std::unordered_map<double, memcell *> numIndexed;

    void numIndexed_toString(std::string &res) const;
    void strIndexed_toString(std::string &res) const;

public:
    dynamic_table();
    ~dynamic_table();

    memcell *get_elem(const memcell *) const;
    void set_elem(const memcell *, memcell *);

    std::string to_string() const;

    void inc_ref_counter();
    void dec_ref_counter();
};

#endif /* __DYNAMIC_TABLE_H */