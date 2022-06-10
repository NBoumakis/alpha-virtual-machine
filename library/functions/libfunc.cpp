#include "executer/cpu.hpp"
#include "lib/colors.hpp"
#include "memory/memcell/memcell.hpp"
#include "table/dynamic_table.hpp"

#include <cmath>

static bool is_number(const std::string &s) {
    bool found_dot = false;

    if (!s.empty()) {
        auto c_itr = s.begin();
        if (!(*c_itr == '+' || *c_itr == '-' || isdigit(*c_itr))) {
            return false;
        }

        ++c_itr;

        for (; c_itr != s.end(); ++c_itr) {
            if (!isdigit(*c_itr) && (*c_itr != '.' || found_dot))
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
        std::cerr << BRED "ERROR: Too many arguments in 'typeof' call. Expected 1, got " << num_of_actuals << "!" RST << std::endl;
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
        std::cerr << BRED "WARNING: Function 'totalarguments' called outside of function!" RST << std::endl;
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

void libfunc_objectmemberkeys() {
    unsigned long num_of_actuals = cpu::env.get_totalactuals();

    if (num_of_actuals != 1) {
        // FIXME
        std::cerr << BRED "ERROR: Too many arguments in 'objectmemberkeys' call. Expected 1, got " << num_of_actuals << "!" RST << std::endl;
        cpu::execution_finished = true;
        cpu::retval = new nilMemcell();
    } else {
        memcell *arg = cpu::env.get_actual(0);

        if (arg->getType() != memcell_type::table_m) {
            std::cerr << BRED "ERROR: Function 'objectmemberkeys' called with argument of type " << arg->getTypeName() << "!" RST << std::endl;
            cpu::execution_finished = true;
            cpu::retval = new nilMemcell();
        } else {
            cpu::retval = arg->getDynamicTable()->get_keys(); // AVM_NUMACTUALS_OFFSET
        }
    }
}

void libfunc_objecttotalmembers() {
    unsigned long num_of_actuals = cpu::env.get_totalactuals();

    if (num_of_actuals != 1) {
        // FIXME
        std::cerr << BRED "ERROR: Too many arguments in 'objecttotalmembers' call. Expected 1, got " << num_of_actuals << "!" RST << std::endl;
        cpu::execution_finished = true;
        cpu::retval = new nilMemcell();
    } else {
        memcell *arg = cpu::env.get_actual(0);

        if (arg->getType() != memcell_type::table_m) {
            std::cerr << BRED "ERROR: Function 'objecttotalmembers' called with argument of type " << arg->getTypeName() << "!" RST << std::endl;
            cpu::execution_finished = true;
            cpu::retval = new nilMemcell();
        } else {
            cpu::retval = new numberMemcell(arg->getDynamicTable()->size());
        }
    }
}

void libfunc_objectcopy() {
    unsigned long num_of_actuals = cpu::env.get_totalactuals();

    if (num_of_actuals != 1) {
        // FIXME
        std::cerr << BRED "ERROR: Too many arguments in 'objectcopy' call. Expected 1, got " << num_of_actuals << "!" RST << std::endl;
        cpu::execution_finished = true;
        cpu::retval = new nilMemcell();
    } else {
        memcell *arg = cpu::env.get_actual(0);

        if (arg->getType() != memcell_type::table_m) {
            std::cerr << BRED "ERROR: Function 'objectcopy' called with argument of type " << arg->getTypeName() << "!" RST << std::endl;
            cpu::execution_finished = true;
            cpu::retval = new nilMemcell();
        } else {
            // We know that both arguments are in the location
            libfunc_objectmemberkeys();
            memcell *keys = cpu::retval;

            libfunc_objecttotalmembers();

            assert(cpu::retval->getType() == memcell_type::number_m);
            unsigned long keys_n = static_cast<unsigned long>(cpu::retval->getNumber());
            assert(static_cast<double>(keys_n) == cpu::retval->getNumber());

            delete cpu::retval;
            cpu::retval = new dynamicTableMemcell(new dynamic_table());

            for (; keys_n; --keys_n) {
                numberMemcell key_n(keys_n - 1);
                memcell *key = keys->getDynamicTable()->get_elem(&key_n);
                memcell *value = arg->getDynamicTable()->get_elem(key);

                if (value->getType() != memcell_type::table_m)
                    value = value->copy(value);
                else
                    value->getDynamicTable()->inc_ref_counter();

                cpu::retval->getDynamicTable()->set_elem(key, value);
            }
        }
    }
}

void libfunc_sqrt() {
    unsigned long num_of_actuals = cpu::env.get_totalactuals();

    if (num_of_actuals != 1) {
        // FIXME
        std::cerr << BRED "ERROR: Too many arguments in 'sqrt' call. Expected 1, got " << num_of_actuals << "!" RST << std::endl;
        cpu::execution_finished = true;
        cpu::retval = new nilMemcell();
    } else {
        memcell *arg = cpu::env.get_actual(0);

        if (arg->getType() != memcell_type::number_m) {
            // FIXME
            std::cerr << BRED "ERROR: Argument of type " << arg->getTypeName() << " not suitable for operation sqrt" RST << std::endl;
            cpu::execution_finished = true;
            cpu::retval = new nilMemcell();
        } else if (arg->getNumber() < 0) {
            // FIXME
            std::cerr << BYEL "WARNING: Square root of negative number " << arg->getNumber() << RST << std::endl;
            cpu::retval = new nilMemcell();
        } else {
            cpu::retval = new numberMemcell(sqrt(arg->getNumber()));
        }
    }
}

void libfunc_cos() {
    unsigned long num_of_actuals = cpu::env.get_totalactuals();

    if (num_of_actuals != 1) {
        // FIXME
        std::cerr << BRED "ERROR: Too many arguments in 'cos' call. Expected 1, got " << num_of_actuals << "!" RST << std::endl;
        cpu::execution_finished = true;
        cpu::retval = new nilMemcell();
    } else {
        memcell *arg = cpu::env.get_actual(0);

        if (arg->getType() != memcell_type::number_m) {
            // FIXME
            std::cerr << BRED "ERROR: Argument of type " << arg->getTypeName() << " not suitable for operation sqrt" RST << std::endl;
            cpu::execution_finished = true;
            cpu::retval = new nilMemcell();
        } else {
            cpu::retval = new numberMemcell(cos(arg->getNumber() / 180 * M_PI));
        }
    }
}

void libfunc_sin() {
    unsigned long num_of_actuals = cpu::env.get_totalactuals();

    if (num_of_actuals != 1) {
        // FIXME
        std::cerr << BRED "ERROR: Too many arguments in 'sin' call. Expected 1, got " << num_of_actuals << "!" RST << std::endl;
        cpu::execution_finished = true;
        cpu::retval = new nilMemcell();
    } else {
        memcell *arg = cpu::env.get_actual(0);

        if (arg->getType() != memcell_type::number_m) {
            // FIXME
            std::cerr << BRED "ERROR: Argument of type " << arg->getTypeName() << " not suitable for operation sqrt" RST << std::endl;
            cpu::execution_finished = true;
            cpu::retval = new nilMemcell();
        } else {
            cpu::retval = new numberMemcell(sin(arg->getNumber() / 180 * M_PI));
        }
    }
}

void libfunc_strtonum() {
    unsigned long num_of_actuals = cpu::env.get_totalactuals();

    if (num_of_actuals != 1) {
        // FIXME
        std::cerr << BRED "ERROR: Too many arguments in 'strtonum' call. Expected 1, got " << num_of_actuals << "!" RST << std::endl;
        cpu::execution_finished = true;
        cpu::retval = new nilMemcell();
    } else {
        memcell *arg = cpu::env.get_actual(0);

        if (arg->getType() != memcell_type::string_m) {
            // FIXME
            std::cerr << BRED "ERROR: Argument of type " << arg->getTypeName() << " not suitable for strtonum" RST << std::endl;
            cpu::execution_finished = true;
            cpu::retval = new nilMemcell();
        } else {
            if (is_number(arg->getString())) {
                cpu::retval = new numberMemcell(std::stod(arg->getString()));
            } else {
                // FIXME
                std::cerr << BYEL "WARNING: String " << arg->getString() << " does not represent a number" RST << std::endl;
                cpu::retval = new nilMemcell();
            }
        }
    }
}

void libfunc_argument() {
    unsigned long p_topsp = cpu::env.get_envvalue(cpu::topsp + 1); // AVM_SAVEDTOPSP_OFFSET
    delete cpu::retval;

    if (!p_topsp) {
        // FIXME
        std::cerr << BRED "WARNING: Function 'argument' called outside of function!" RST << std::endl;
        cpu::retval = new nilMemcell();
    } else {
        memcell *arg = cpu::env.get_actual(0);
        assert(arg->getType() == memcell_type::number_m);
        if (arg->getNumber() >= 0) {
            unsigned long index = static_cast<unsigned long>(arg->getNumber());
            assert(static_cast<double>(index) == arg->getNumber());

            if (index < cpu::env.get_envvalue(p_topsp + 4))
                cpu::retval = cpu::stack[p_topsp + 4 + 1 + index];
            else {
                // FIXME
                std::cerr << BRED "ERROR: Argument with index " << index << " doesn't belong to most recently called function!" RST << std::endl;
                cpu::execution_finished = true;
                cpu::retval = new nilMemcell();
            }
        } else {
            // FIXME
            std::cerr << BRED "ERROR: Argument with index " << arg->getNumber() << " doesn't belong to most recently called function!" RST << std::endl;
            cpu::execution_finished = true;
            cpu::retval = new nilMemcell();
        }
    }
}