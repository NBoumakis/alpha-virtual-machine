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
};

class number {
private:
    double value;

public:
    number(double);
    ~number();
};
