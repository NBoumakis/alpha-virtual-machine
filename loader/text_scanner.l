%{
#include "text_scanner.hpp"
%}

%option c++
%option noyywrap

DIGIT       [0-9]
DOUBLE      DIGIT+\.DIGIT+
CHARACTER   .|\n
%%

[+-]?{DIGIT}+       { yylval = std::stod(yytext); return LONG; }
{CHARACTER}         { yylval = yytext[0]; return CHAR; }
{DOUBLE}            { yylval = std::stod(yytext); return DOUBLE; }
<<EOF>>             { return END; }
%%