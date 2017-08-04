%code requires {
    #include "ast.h"
}

%{
#include <stdio.h>

int yylex();
extern int yylineno;
void yyerror(const char* msg)
{
    printf("Line:%d %s\n", yylineno, msg);
}

#define YYERROR_VERBOSE 1

%}
%expect 1
%union {
    Statement* statement_t;
    Expr* expr_t;
    int int_t;
}

%type<statement_t> statement assign_statement print_statement statement_list
%type<statement_t> conditional_statement
%type<statement_t> block_statement
%type<statement_t> optional_else
%type<expr_t> compare_ops conditional_expression
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
%token          TK_LEFT_CURLY_BRACK TK_RIGHT_CURLY_BRACK
%token          TK_COMPARE TK_NOT_EQ
%token          TK_GREATER_THAN TK_GREATER_EQUAL
%token          TK_LESS_THAN TK_LESS_EQUAL
%token          KW_IF
%token          KW_ELSE

%%
/*NO PROBLEM*/
code: optional_eol statement_list optional_eol { $2->exec(); }
;
/*NO PROBLEM*/
statement_list: statement_list eol_list statement { $$ = $1; ((BlockStatement *)$$)->addStatement($3); }
    | statement     { $$ = new BlockStatement; ((BlockStatement*)$$)->addStatement($1); }
;
/*NO PROBLEM*/
eol_list: eol_list TK_EOL
    | TK_EOL
;
/*NO PROBLEM*/
optional_eol: eol_list
    |
;
/*NO PROBLEM*/
statement: print_statement  { $$ = $1; }
    | assign_statement      { $$ = $1; }
    | conditional_statement { $$ = $1; }
;
/*NO PROBLEM*/
assign_statement: TK_ID TK_EQ expr_op { $$ = new AssignStatement($1, $3); }
;
/*NO PROBLEM*/
print_statement: TK_PRINT expr_op TK_COMMA format_expr { $$ = new PrintStatement($2, $4); }
;

conditional_statement: KW_IF TK_LEFT_PAR conditional_expression TK_RIGHT_PAR eol_list block_statement eol_list optional_else {
        $$ = new IfStatement($3, $6, $8);
    }
;

conditional_expression: expr_op compare_ops expr_op { $$ = $2; ((BinaryExpr*)$$)->expr1 = $1; ((BinaryExpr*)$$)->expr2 = $3; }
;

compare_ops: TK_COMPARE { $$ = new EqualExpr; }
    | TK_NOT_EQ         { $$ = new NotEqualExpr; }
    | TK_GREATER_THAN   { $$ = new GreaterThanExpr; }
    | TK_GREATER_EQUAL  { $$ = new GreaterEqualExpr; }
    | TK_LESS_THAN      { $$ = new LessThanExpr; }
    | TK_LESS_EQUAL     { $$ = new LessEqualExpr; }
;

block_statement: statement                                     { $$ = new BlockStatement; ((BlockStatement*)$$)->addStatement($1); }
    | TK_LEFT_CURLY_BRACK statement_list TK_RIGHT_CURLY_BRACK  { $$ = $2; }
;

optional_else: KW_ELSE eol_list block_statement  { $$ = new BlockStatement; ((BlockStatement*)$$)->addStatement($3); }
    |                                                { $$ = NULL; }
;
/*NO PROBLEM*/
format_expr:  KW_HEX            { $$ = 0; }
            | KW_DEC            { $$ = 1; }
            | KW_BIN            { $$ = 2; }
;
/*NO PROBLEM*/
expr_op:  expr_op OP_ADD term       { $$ = new AddExpr($1, $3); }
        | expr_op OP_SUB term       { $$ = new SubExpr($1, $3); }
        | term                      { $$ = $1; }
;
/*NO PROBLEM*/
term: term OP_MUL factor    { $$ = new MulExpr($1, $3); }
    | term OP_DIV factor    { $$ = new DivExpr($1, $3); }
    | factor                { $$ = $1; }
;

factor: TK_NUMBER                         { $$ = new NumberExpr($1); }
    | TK_ID                               { $$ = new VarExpr($1); }
    | TK_LEFT_PAR expr_op TK_RIGHT_PAR    { $$ = $2; }
;
