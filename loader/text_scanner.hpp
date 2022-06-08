#include <iostream>
using namespace std;

const int NUM = 0, OPA = 1, OPM = 2, LP = 3, RP = 4, STOP = 5;

extern int yylval; // All semantic values of tokens are int's

int yylex();