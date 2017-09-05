%option noyywrap
%option yylineno

%{
#include "tokens.h"
#include <stdio.h>

%}

%%


[ \t\n]                 { /*NOTHING*/ }
[0-9]+                  { return LIT_INT; }
[_a-zA-Z][a-zA-Z0-9]*   { return TK_ID; }
"("                     { return TK_LEFT_PAR; }
")"                     { return TK_RIGHT_PAR; }
"="                     { return OP_ASSIGN; }
";"                     { return TK_EOS; }
","                     { return TK_COMMA; }
"+"                     { return OP_SUM; }
"-"                     { return OP_SUB; }
"*"                     { return OP_STAR; }
.                       { yyterminate(); }
%%
