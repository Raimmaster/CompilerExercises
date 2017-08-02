%code requires {
    #include "ast.h"
}

%{
#include <stdio.h>
#include <string.h>

int yylex();
extern int yylineno;
void yyerror(const char* msg)
{
    printf("Line:%d %s\n", yylineno, msg);
}

const char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

#define YYERROR_VERBOSE 1

%}

%union {
    Statement* statement_t;
    Expr* expr_t;
    int int_t;
}

%type<statement_t> statement assign_statement print_statement statement_list
%type<expr_t> expr_op term
%type<expr_t> factor
%type<int_t> format_expr

%token          OP_ADD OP_SUB OP_MUL OP_DIV TK_LEFT_PAR TK_RIGHT_PAR
%token<int_t>   TK_NUMBER
%token<int_t>   TK_ID
%token          TK_EOF TK_EOL
%token          TK_ERROR
%token          TK_PRINT
%token          TK_EQ
%token          KW_HEX
%token          KW_DEC
%token          KW_BIN
%token          TK_COMMA

%%

code: optional_eol_list statement_list optional_eol_list { $2->exec(); }
;

statement_list:   statement_list optional_eol_list statement { $$ = $1; ((BlockStatement *)$$)->addStatement($3); }
                | statement optional_eol_list                { $$ = new BlockStatement; ((BlockStatement*)$$)->addStatement($1); }
;

optional_eol_list: optional_eol_list optional_eol
                | optional_eol

optional_eol: TK_EOL
    |
;

statement: print_statement  { $$ = $1; }
    | assign_statement      { $$ = $1; }
;

assign_statement: TK_ID TK_EQ expr_op { $$ = new AssignStatement($1, $3); }
;

print_statement: TK_PRINT expr_op TK_COMMA format_expr { $$ = new PrintStatement($2, $4); }
;

format_expr:  KW_HEX            { $$ = KW_HEX; }
            | KW_DEC            { $$ = KW_DEC; }
            | KW_BIN            { $$ = KW_BIN; }
;

expr_op:  expr_op OP_ADD term        { $$ = new AddExpr($1, $3); }
        | expr_op OP_SUB term       { $$ = new SubExpr($1, $3); }
        | term                      { $$ = $1; }
;

term: term OP_MUL factor    { $$ = new MulExpr($1, $3); }
    | term OP_DIV factor    { $$ = new DivExpr($1, $3); }
    | factor                { $$ = $1; }
;

factor:   TK_NUMBER                           { $$ = new NumberExpr($1); }
        | TK_ID                             { $$ = new VarExpr($1); }
        | TK_LEFT_PAR expr_op TK_RIGHT_PAR  { $$ = $2; }
