%{
#include "text_scanner.hpp"
%}

%option noyywrap

%%

[0-9]+   { yylval = atoi(yytext); return NUM; }
[\+\-]   { yylval = yytext[0]; return OPA; }
[\*/]    { yylval = yytext[0]; return OPM; }
"("      { return LP; }
")"      { return RP; }
";"      { return STOP; }
<<EOF>>  { return 0; }
[ \t\n]+ { }
.        { cerr << "Unrecognized token!" << endl; exit(1); }
%%