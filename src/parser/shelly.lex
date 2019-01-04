%{
    // C declarations
    #include <stdio.h>
    #include "shelly.tab.h"
%}

INTEGER [0-9]
FLOATING_POINT_NUMBER {INTEGER}+\.{INTEGER}+
CHAR [a-zA-Z0-9]
STR {CHAR}+
NEWLINE \n

%option noyywrap

%%

[ \t{NEWLINE}] ;  // ignore all whitespace

{INTEGER}+ {
    yylval.ival = atoi(yytext);
    return INT;
}
{FLOATING_POINT_NUMBER} {
    yylval.fval = atof(yytext);
    return FLOAT;
}
{STR} {
    yylval.sval = strdup(yytext);
    return STRING;
}

%%

