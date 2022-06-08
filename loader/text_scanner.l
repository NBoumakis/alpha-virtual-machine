%{
#include "text_scanner.hpp"
%}

%option c++
%option noyywrap

DIGIT       [0-9]
SPACE       [ ]
NULLTERM    [\0]
BYTE        [+-]?DIGIT{1,3}
DOUBLE      DIGIT+\.DIGIT+

%%

{DIGIT}+            { yylval = std::stod(yytext); return ULONG; }
{SPACE}             { yylval = yytext[0]; return SPACE; }
[.]                 { yylval = yytext[0]; return CHAR; }
{NULLTERM}          { return NTERM; }
{BYTE}              { return BYTE; }
{DOUBLE}            { return DOUBLE; }
<<EOF>>             { return END; }
%%