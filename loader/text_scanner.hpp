#include <iostream>

enum text_type { INVALID = -1,
                 END,
                 LONG,
                 CHAR,
                 DOUBLE };

extern double yylval; // All semantic values of tokens are doubles
