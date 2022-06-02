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
    virtual ~memcell() = default;

    virtual memcell_type getType(void) const = 0;

    friend memcell *translate_operand(vmarg *, memcell *);

    
    virtual void setNumber(const double number);
    virtual double getNumber(void) const = 0;

    virtual void setString(const std::string string&);
    virtual std::string getString(void) const = 0;
    
    virtual void setBool(const bool boolean);
    virtual bool getBool(void) const = 0;

    
    virtual void operator=(memcell *); // avm_assign
};

class numberMemcell final: public memcell {
private:
    double value;

public:
    numberMemcell();
    ~numberMemcell() = default;

    void setNumber(const double);
    double getNumber(void) const override;
    memcell_type getType() const override;
};

class stringMemcell : public memcell {
private:
    std::string value;

public:
    stringMemcell();
    ~stringMemcell() = default;

    void setString(const std::string&);
    double getString(void) const override;
    memcell_type getType() const override;
};

class boolMemcell : public memcell {
private:
    bool value;

public:
    bool();
    ~bool() = default;

    void setBool(const bool boolean);
    bool getBool(void) const override;
    memcell_type getType() const override;
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