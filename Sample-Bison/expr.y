%{
#include <stdio.h>
int yylex();
void yyerror(const char* msg)
{
    printf("%s\n", msg);
}

#define YYERROR_VERBOSE 1

%}

%token OP_ADD OP_SUB OP_MUL OP_DIV TK_LEFT_PAR TK_RIGHT_PAR
%token TK_NUMBER TK_EOF TK_EOL
%token TK_ERROR

%%

start: expr { printf("%d\n", $1); }
    | expr TK_EOL { printf("%d\n", $1); }
    | expr TK_EOL start { printf("%d\n", $1); }
;

expr: expr OP_ADD term { $$ = $1 + $3; }
    | expr OP_SUB term { $$ = $1 - $3; }
    | term { $$ = $1; }
;

term: term OP_MUL factor { $$ = $1 * $3; }
    | term OP_DIV factor { $$ = $1 / $3; }
    | factor { $$ = $1; }
;

factor: TK_NUMBER { $$ = $1; }
    | TK_LEFT_PAR expr TK_RIGHT_PAR { $$ = $2; }
;
