#include "table/dynamic_table.hpp"

dynamic_table::dynamic_table(){
    refCounter=0;
}

dynamic_table::~dynamic_table(){
    for (auto &memObj: strIndexed){
        memObj.second->~memcell();
    }

    strIndexed.clear();


    for (auto &memObj: numIndexed){
        memObj.second->~memcell();
    }

    numIndexed.clear();
}

memcell *dynamic_table::get_elem(const memcell *) const{
    
}

void dynamic_table::set_elem(const memcell *key, const memcell *value){
    
}

void dynamic_table::inc_ref_counter(){
    ++refCounter;
}

void dynamic_table::dec_ref_counter(){
    assert(refCounter > 0);

    if (!(--refCounter)){
        ~dynamic_table();
    }
}