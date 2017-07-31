%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int yylex();
extern int yylineno;
int array[8];
void yyerror(const char* msg)
{
    printf("Line:%d %s\n", yylineno, msg);
}

#define YYERROR_VERBOSE 1

%}

%token OP_ADD OP_SUB OP_MUL OP_DIV TK_LEFT_PAR TK_RIGHT_PAR
%token TK_NUMBER TK_EOF TK_EOL
%token TK_ERROR
%token TK_PRINT
%token TK_EQ
%token TK_ID
%token TK_COMMA
%token KW_DEC KW_HEX KW_BIN

%%

start: expr
    | expr TK_EOL
    | expr TK_EOL start
;

expr: TK_ID TK_EQ expr_op { array[$1] = $3; $$ = $1; }
    | TK_PRINT expr_op TK_COMMA expr_format {
        if(strcmp($4, "hex")) { printf("%x\n", $2); } else if(strcmp($4, "dec")) { printf("%x\n", $2); } )
        else if(strcmp($4, "bin")) { printf("Bin option %d\n", $2); }
        }
    |
;

expr_format: KW_DEC     { $$ = $1; }
            | KW_HEX    { $$ = $1; }
            | KW_BIN    { $$ = $1; }
;

expr_op: expr_op OP_ADD term { $$ = $1 + $3; }
    | expr_op OP_SUB term { $$ = $1 - $3; }
    | term { $$ = $1; }
;

term: term OP_MUL factor { $$ = $1 * $3; }
    | term OP_DIV factor { $$ = $1 / $3; }
    | factor { $$ = $1; }
;

factor: TK_NUMBER { $$ = $1; }
    | TK_ID { $$ = array[$1]; }
    | TK_LEFT_PAR expr_op TK_RIGHT_PAR { $$ = $2; }
;
