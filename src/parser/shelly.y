%{
    #include <stdio.h>
    #include <stdlib.h>
    // Declare stuff from Flex that Bison needs to know about:
    extern int yylex();
    extern int yyparse();
    void yyerror(const char *s){
        printf(stderr, "%s\n", s);
    }
%}

/*
*
* Unions can hold all of the types of tokens that Flex could return, and this this means
* we can return ints or floats or strings cleanly.  Bison implements this mechanism with the %union directive:
*
*/

%union {
    int ival;
    float fval;
    char *sval;
}

/*
*
* Define the "terminal symbol" token types I'm going to use (in CAPS<Paste>
* by convention), and associate each with a field of the %union:
*
*/

%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%%
shelly:
    INT shelly {
        fprintf(stdout, "Bison found an int -> %d\n", $1);
        }
    |
    FLOAT shelly {
        fprintf(stdout, "Bison found a float -> %f\n", $1);
        }
    |
    STRING shelly {
        fprintf(stdout, "Bison found a string -> %s\n", $1);
        free($1);
        }
    |
    INT {
        fprintf(stdout, "Bison found an int -> %d\n", $1);
        }
    |
    FLOAT {
        fprintf(stdout, "Bison found a float -> %f\n", $1);
        }
    |
    STRING {
        fprintf(stdout, "Bison found a string -> %s\n", $1);
        free($1);
        }
    ;
%%

int main(int argc, char **argv){
    while (yyparse());
}
