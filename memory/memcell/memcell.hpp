#ifndef __MEMCELL_H
#define __MEMCELL_H

#include "lib/vmarg.h"
#include "table/dynamic_table.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

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

    friend memcell *translate_operand(vmarg *, memcell *);

    virtual void setNumber(double number) {
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

    virtual void setDynamicTable(dynamic_table *table) {
        assert(false);
    }
    virtual dynamic_table *getDynamicTable(void) const {
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

    virtual operator std::string() const = 0;
    virtual operator bool() const = 0;

    virtual bool operator==(const memcell *op) const = 0;
    virtual bool operator!=(const memcell *op) const {
        return !(*this == *op);
    }
    virtual memcell_type getType(void) const = 0;
    virtual std::string getTypeName() const = 0;
};

class numberMemcell final : public memcell {
private:
    double value;

public:
    numberMemcell() = default;
    numberMemcell(numberMemcell const &b) = default;
    numberMemcell(double);
    ~numberMemcell() = default;

    void setNumber(double number);
    double getNumber(void) const override;
    memcell_type getType(void) const override;
    std::string getTypeName() const override;

    operator std::string() const override;
    operator bool() const override;
    bool operator==(const memcell *op) const override;
};

class stringMemcell final : public memcell {
private:
    std::string value;

public:
    stringMemcell() = default;
    stringMemcell(stringMemcell const &b) = default;
    stringMemcell(const std::string &);
    ~stringMemcell() = default;

    void setString(const std::string &string);
    std::string getString(void) const override;
    memcell_type getType(void) const override;
    std::string getTypeName() const override;
    operator std::string() const override;
    operator bool() const override;
    bool operator==(const memcell *op) const override;
};

class boolMemcell final : public memcell {
private:
    bool value;

public:
    boolMemcell() = default;
    boolMemcell(boolMemcell const &b) = default;
    boolMemcell(bool);
    ~boolMemcell() = default;

    void setBool(bool boolean);
    bool getBool(void) const override;
    memcell_type getType(void) const override;
    std::string getTypeName() const override;
    operator std::string() const override;
    operator bool() const override;
    bool operator==(const memcell *op) const override;
};

class dynamicTableMemcell final : public memcell {
private:
    dynamic_table *value;

public:
    dynamicTableMemcell() = default;
    dynamicTableMemcell(dynamicTableMemcell const &b) = default;
    dynamicTableMemcell(dynamic_table *);
    ~dynamicTableMemcell() = default;

    void setDynamicTable(dynamic_table *table);
    dynamic_table *getDynamicTable(void) const override;
    memcell_type getType(void) const override;
    std::string getTypeName() const override;
    operator std::string() const override;
    operator bool() const override;
    bool operator==(const memcell *op) const override;
};

class userfuncMemcell final : public memcell {
private:
    unsigned long value;

public:
    userfuncMemcell() = default;
    userfuncMemcell(userfuncMemcell const &b) = default;
    userfuncMemcell(const unsigned long);
    ~userfuncMemcell() = default;

    void setUserFunc(const unsigned long userfunc);
    unsigned long getUserFunc(void) const override;
    memcell_type getType(void) const override;
    std::string getTypeName() const override;
    operator std::string() const override;
    operator bool() const override;
    bool operator==(const memcell *op) const override;
};

class libfuncMemcell final : public memcell {
private:
    std::string value;

public:
    libfuncMemcell() = default;
    libfuncMemcell(libfuncMemcell const &b) = default;
    libfuncMemcell(const std::string &);
    ~libfuncMemcell() = default;

    void setLibFunc(const std::string &userfunc);
    std::string getLibFunc(void) const override;
    memcell_type getType(void) const override;
    std::string getTypeName() const override;
    operator std::string() const override;
    operator bool() const override;
    bool operator==(const memcell *op) const override;
};

class nilMemcell final : public memcell {
private:
    std::string value;

public:
    nilMemcell() = default;
    nilMemcell(nilMemcell const &b) = default;
    ~nilMemcell() = default;

    memcell_type getType(void) const override;
    std::string getTypeName() const override;
    operator std::string() const override;
    operator bool() const override;
    bool operator==(const memcell *op) const override;
};

memcell *assign(memcell *&, memcell *);

#endif /* ___MEMCELL_H */