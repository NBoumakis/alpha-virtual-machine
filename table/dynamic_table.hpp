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

public:
    dynamic_table();
    ~dynamic_table();

    memcell *get_elem(const memcell *) const;
    void set_elem(const memcell *, memcell *);

    void inc_ref_counter();
    void dec_ref_counter();
};

#endif /* __DYNAMIC_TABLE_H */