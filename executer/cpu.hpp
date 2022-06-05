#include "library/environment/environment.hpp"
#include "memory/code_segment/code_segment.hpp"
#include "memory/const_values/const_values.hpp"
#include "memory/memcell/memcell.hpp"
#include "memory/stack/program_stack.hpp"

class cpu {
public:
    static unsigned long pc, topsp, top, code_size;
    static memcell *ax, *bx, *cx, *retval;
    static program_stack stack;
    static environment env;
    static code_segment code;
    static const_values pools;
    static bool execution_finished;

    cpu();
    ~cpu();

    static void cycle();
};
