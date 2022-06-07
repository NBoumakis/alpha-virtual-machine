#include "executer/cpu.hpp"
#include "memory/memcell/memcell.hpp"

#include <algorithm>

static bool is_number(const std::string &s) {
    bool found_dot = false;

    if (!s.empty()) {
        auto c_itr = s.begin();
        if (!(*c_itr == '+' || *c_itr == '-' || isdigit(*c_itr))) {
            return false;
        }

        for (; c_itr != s.end(); ++c_itr) {
            if (!(isdigit(*c_itr) || (*c_itr == '.' && found_dot)))
                return false;

            found_dot = (*c_itr == '.');
        }

        return true;
    } else {
        return false;
    }
}

void libfunc_typeof() {
    unsigned long num_of_actuals = cpu::env.get_totalactuals();

    if (num_of_actuals != 1) {
        // FIXME
        std::cerr << "ERROR: one argument (not " << num_of_actuals << ") expected in 'typeof'";
        cpu::execution_finished = true;
    } else {
        delete cpu::retval;
        cpu::retval = new stringMemcell(cpu::env.get_actual(0UL)->getTypeName());
    }
}

void libfunc_print() {
    unsigned long num_of_actuals = cpu::env.get_totalactuals();

    for (unsigned long i = 0; i < num_of_actuals; i++) {
        std::string s = static_cast<std::string>(*cpu::env.get_actual(i));
        std::cout << s;
    }
}
void libfunc_totalarguments() {
    unsigned long p_topsp = cpu::env.get_envvalue(cpu::topsp + 1); // AVM_SAVEDTOPSP_OFFSET
    delete cpu::retval;

    if (!p_topsp) {
        // FIXME
        std::cerr << "ERROR: 'totalarguments' called outside a function !";
        cpu::execution_finished = true;
        cpu::retval = new nilMemcell();
    } else {
        cpu::retval = new numberMemcell(cpu::env.get_envvalue(p_topsp + 4)); // AVM_NUMACTUALS_OFFSET
    }
}

static memcell *parse_input(const std::string &input) {
    if (is_number(input))
        return new numberMemcell(std::stod(input));
    else if (input == "true")
        return new boolMemcell(true);
    else if (input == "false")
        return new boolMemcell(false);
    else if (input == "nil")
        return new nilMemcell();
    else {
        if (input.empty())
            return new stringMemcell("");
        else if (input[0] == '"' && input[input.size() - 1] == '"')
            return new stringMemcell(input.substr(1, input.size() - 2));
        else
            return new stringMemcell(input);
    }
}

void libfunc_input() {
    std::string line;

    std::getline(std::cin, line);

    cpu::retval = parse_input(line);
}