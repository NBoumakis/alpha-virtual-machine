#include "lib/vmarg.h"
#include <string>

enum class memcell_type {
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

    virtual memcell_type getType(void) const = 0;

    friend memcell *translate_operand(vmarg *, memcell *);

    virtual void setNumber(const double number);
    virtual double getNumber(void) const = 0;

    virtual operator std::string() = 0;
    virtual operator dynamic_table() = 0;
    virtual operator userfunc() = 0;
    virtual operator libfunc() = 0;    
    virtual operator bool() = 0;
    virtual void operator=(memcell *); // avm_assign
};

class numberMemcell final: public memcell {
private:
    double value;

public:
    void setNumber(const double);
    double getNumber(void) const override;
    memcell_type getType() const override;
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

//maybe change the structure
class userfunc : public memcell {
private:
    unsigned long value;

public:
    userfunc(unsigned long);
    ~userfunc();
};

class libfunc : public memcell {
private:
    std::string value;

public:
    libfunc(std::string &);
    ~libfunc();
};