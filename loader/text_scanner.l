%{
#include "text_scanner.hpp"
%}

%option c++
%option noyywrap

DIGIT       [0-9]
DOUBLE      DIGIT+\.DIGIT+
CHARACTER   .|\n
%%

[+-]?[0-9]+\.[0-9]+              { yylval = std::stod(yytext); return DOUBLE; }
[+-]?{DIGIT}+       { yylval = std::stod(yytext); return LONG; }
{CHARACTER}         { yylval = yytext[0]; return CHAR; }
<<EOF>>             { return END; }

%%