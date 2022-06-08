#include <iostream>
using namespace std;

enum text_type { END,
                 ULONG,
                 SPACE,
                 CHAR,
                 NTERM,
                 BYTE,
                 DOUBLE };

extern double yylval; // All semantic values of tokens are int's

int yylex();