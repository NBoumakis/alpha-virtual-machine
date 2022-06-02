#include <cpu.hpp>
#include <memory/memcell/memcell.hpp>

void libfunc_typeof(){
    unsigned long num_of_actuals = cpu::env.total_actuals();

    if (num_of_actuals != 1){
        //error one argument not expected in 'typeof'

    }else{
       delete cpu::retval;
       cpu::retval = new string(cpu::env->get_actual(0UL).get_type_name());
    }
}

void libfunc_print(){
    unsigned long num_of_actuals = cpu::env.total_actuals();

    for(unsigned long i = 0 ; i < num_of_actuals ; i++){
        std::string s = static_cast<std::string> (*cpu::env.get_actual(i));
    }

}

