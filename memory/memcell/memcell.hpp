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

    virtual void setString(const std::string &string);
    virtual std::string getString(void) const = 0;

    virtual void setBool(const bool boolean);
    virtual bool getBool(void) const = 0;

    virtual void setUserFunc(const unsigned long userfunc);
    virtual unsigned long getUserFunc(void) const = 0;

    virtual void setLibFunc(const std::string &libfunc);
    virtual std::string getLibFunc(void) const = 0;

    virtual void operator=(memcell *); // avm_assign
    virtual std::string getTypeName() = 0;
};

class numberMemcell final : public memcell {
private:
    double value;

public:
    numberMemcell();
    ~numberMemcell() = default;

    void setNumber(const double number);
    double getNumber(void) const override;
    memcell_type getType(void) const override;
};

class stringMemcell final : public memcell {
private:
    std::string value;

public:
    stringMemcell();
    ~stringMemcell() = default;

    void setString(const std::string &string);
    std::string getString(void) const override;
    memcell_type getType(void) const override;
};

class boolMemcell final : public memcell {
private:
    bool value;

public:
    boolMemcell();
    ~boolMemcell() = default;

    void setBool(const bool boolean);
    bool getBool(void) const override;
    memcell_type getType(void) const override;
};

class userfuncMemcell final : public memcell {
private:
    unsigned long value;

public:
    userfuncMemcell();
    ~userfuncMemcell() = default;

    void setUserFunc(const unsigned long userfunc);
    unsigned long getUserFunc(void) const override;
    memcell_type getType(void) const override;
};

class libfuncMemcell final : public memcell {
private:
    std::string value;

public:
    libfuncMemcell();
    ~libfuncMemcell() = default;

    void setLibFunc(const std::string &userfunc);
    std::string getLibFunc(void) const override;
    memcell_type getType(void) const override;
};