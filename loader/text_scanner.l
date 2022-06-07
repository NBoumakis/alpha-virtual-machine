/* Flex options */
%option noyywrap
%option yylineno

DIGITS       ([0-9]+)
SPACE        [ ]

{UNSIGNED_LONG} {
    return UNSIGNED_LONG;
}