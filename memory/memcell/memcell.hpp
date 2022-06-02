#include "lib/vmarg.h"
#include <string>

enum memcell_type {
    number_m,
    string_m,
    bool_m,
    table_m,
    userfunc_m,
    libfunc_m,
    nil_m,
    undefined_m
};

class memcell {
public:
    memcell();
    ~memcell();

    friend memcell *translate_operand(vmarg *, memcell *);

    virtual operator std::string() = 0;
    virtual operator bool() = 0;
    virtual void operator=(memcell *); // avm_assign
};

class number : public memcell {
private:
    double value;

public:
    number(double);
    ~number();
};

class string : public memcell {
private:
    std::string value;

public:
    string(std::string &);
    ~string();
};

class bool : public memcell {
private:
    bool value;

public:
    bool(bool);
    ~bool();
};