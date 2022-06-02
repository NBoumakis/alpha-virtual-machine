#ifndef __MEMCELL_H
#define __MEMCELL_H

#include "lib/vmarg.h"
#include "table/dynamic_table.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

static const std::unordered_map < memcell_type, std::function<memcell *(memcell const &)> dispatch = {
                                                    {memcell_type::number_m, [](memcell const &) -> memcell * { return new numberMemcell; }},
                                                    {memcell_type::string_m, [](memcell const &) -> memcell * { return new stringMemcell; }},
                                                    {memcell_type::bool_m, [](memcell const &) -> memcell * { return new boolMemcell; }},
                                                    {memcell_type::table_m, [](memcell const &) -> memcell * { return new dynamicTableMemcell; }},
                                                    {memcell_type::userfunc_m, [](memcell const &) -> memcell * { return new userfuncMemcell; }},
                                                    {memcell_type::libfunc_m, [](memcell const &) -> memcell * { return new libfuncMemcell; }},
};

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
    void assign(memcell &*, memcell *);
    virtual memcell_type getType(void) const = 0;
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