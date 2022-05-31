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

    virtual operator std::string() = 0;
    virtual operator bool() = 0;
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
