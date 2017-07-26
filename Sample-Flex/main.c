#include <stdio.h>
#include "tokens.h"

int yylex();
int list_expr();
extern int token;

int main()
{
    token = yylex();
    list_expr();
    // int r = 0;
    // printf("Result final = %d\n", r);
}
