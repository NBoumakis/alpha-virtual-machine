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