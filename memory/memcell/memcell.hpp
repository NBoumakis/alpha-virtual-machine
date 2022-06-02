#ifndef __MEMCELL_H
#define __MEMCELL_H

#include "lib/vmarg.h"
#include "table/dynamic_table.hpp"
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
    memcell() = default;
    virtual ~memcell() = default;

    virtual memcell_type getType(void) const = 0;

    friend memcell *translate_operand(vmarg *, memcell *);

    virtual void setNumber(const double number) {
        assert(false);
    }
    virtual double getNumber(void) const {
        assert(false);
        return 0;
    };

    virtual void setString(const std::string &string) {
        assert(false);
    }
    virtual std::string getString(void) const {
        assert(false);
        return "";
    }

    virtual void setBool(const bool boolean) {
        assert(false);
    }
    virtual bool getBool(void) const {
        assert(false);
        return false;
    }

    virtual void setDynamicTable(const dynamic_table table) {
        assert(false);
    }
    virtual dynamic_table getDynamicTable(void) const {
        assert(false);
        return nullptr;
    }

    virtual void setUserFunc(const unsigned long userfunc) {
        assert(false);
    }
    virtual unsigned long getUserFunc(void) const {
        assert(false);
        return 0;
    }

    virtual void setLibFunc(const std::string &libfunc) {
        assert(false);
    }
    virtual std::string getLibFunc(void) const {
        assert(false);
        return "";
    }

    virtual operator std::string() = 0;
    virtual operator bool() = 0;

    virtual void operator=(memcell *); // avm_assign
    virtual std::string getTypeName() = 0;
};

class numberMemcell final : public memcell {
private:
    double value;

public:
    numberMemcell(const double);
    ~numberMemcell() = default;

    void setNumber(const double number);
    double getNumber(void) const override;
    memcell_type getType(void) const override;
    std::string getTypeName() const override;
    operator std::string() override;
    operator bool() override;
};

class stringMemcell final : public memcell {
private:
    std::string value;

public:
    stringMemcell(const std::string &);
    ~stringMemcell() = default;

    void setString(const std::string &string);
    std::string getString(void) const override;
    memcell_type getType(void) const override;
    std::string getTypeName() const override;
    operator std::string() override;
    operator bool() override;
};

class boolMemcell final : public memcell {
private:
    bool value;

public:
    boolMemcell(const bool);
    ~boolMemcell() = default;

    void setBool(const bool boolean);
    bool getBool(void) const override;
    memcell_type getType(void) const override;
    std::string getTypeName() const override;
    operator std::string() override;
    operator bool() override;
};

class dynamicTableMemcell final : public memcell {
private:
    dynamic_table value;

public:
    dynamicTableMemcell(const dynamic_table);
    ~dynamicTableMemcell() = default;

    void setDynamicTable(const dynamic_table table);
    dynamic_table getDynamicTable(void) const override;
    memcell_type getType(void) const override;
    std::string getTypeName() const override;
    operator std::string() override;
    operator bool() override;
};

class userfuncMemcell final : public memcell {
private:
    unsigned long value;

public:
    userfuncMemcell(const unsigned long);
    ~userfuncMemcell() = default;

    void setUserFunc(const unsigned long userfunc);
    unsigned long getUserFunc(void) const override;
    memcell_type getType(void) const override;
    std::string getTypeName() const override;
    operator std::string() override;
    operator bool() override;
};

class libfuncMemcell final : public memcell {
private:
    std::string value;

public:
    libfuncMemcell(const std::string &);
    ~libfuncMemcell() = default;

    void setLibFunc(const std::string &userfunc);
    std::string getLibFunc(void) const override;
    memcell_type getType(void) const override;
    std::string getTypeName() const override;
    operator std::string() override;
    operator bool() override;
};

#endif /* ___MEMCELL_H */