%{
#include <stdio.h>
#include <string.h>     /* strcat */
int yylex();
extern int yylineno;
/*int array[8];*/
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

%type <statement_t> statement assign_statement print_statement
%type <expr_t> expr term factor

%token          OP_ADD OP_SUB OP_MUL OP_DIV TK_LEFT_PAR TK_RIGHT_PAR
%token<int_t>   TK_NUMBER
%token          TK_EOF TK_EOL
%token          TK_ERROR
%token          TK_PRINT
%token          TK_EQ
%token<int_t>   TK_ID
%token          KW_HEX
%token          KW_DEC
%token          KW_BIN
%token          TK_COMMA

%%

start: expr
    | expr TK_EOL
    | expr TK_EOL start
;

expr: TK_ID TK_EQ expr_op { array[$1] = $3; $$ = $1; }
    | TK_PRINT expr_op TK_COMMA format_expr { if($4 == KW_HEX) { printf("Hex: %x\n", $2); }
        else if ($4 == KW_DEC) { printf("Dec: %d\n", $2); } else if ($4 == KW_BIN) { printf("Bin: %s\n", byte_to_binary($2)); }
        }
    |
;

format_expr:  KW_HEX { $$ = KW_HEX; }
            | KW_DEC { $$ = KW_DEC; }
            | KW_BIN { $$ = KW_BIN; }
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
