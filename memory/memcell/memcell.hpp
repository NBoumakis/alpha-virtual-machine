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

    virtual void setUserFunc(unsigned long userfunc);
    virtual unsigned long getUserFunc(void) const = 0;
    

    virtual void operator=(memcell *); // avm_assign
};

class numberMemcell final: public memcell {
private:
    double value;

public:
    numberMemcell();
    ~numberMemcell() = default;

    void setNumber(const double number);
    double getNumber(void) const override;
    memcell_type getType(void) const override;
};

class stringMemcell final: public memcell {
private:
    std::string value;

public:
    stringMemcell();
    ~stringMemcell() = default;

    void setString(const std::string string&);
    double getString(void) const override;
    memcell_type getType(void) const override;
};

class boolMemcell final: public memcell {
private:
    bool value;

public:
    boolMemcell();
    ~boolMemcell() = default;

    void setBool(const bool boolean);
    bool getBool(void) const override;
    memcell_type getType(void) const override;
};

class userfuncMemcell final: public memcell {
private:
    unsigned long value;

public:
    userfuncMemcell();
    ~userfuncMemcell() = default;

    void setUserFunc(unsigned long userfunc);
    unsigned long getUserFunc(void) const override;
    memcell_type getType(void) const override;
};

class libfunc : public memcell {
private:
    std::string value;

public:
    libfunc(std::string &);
    ~libfunc();
};