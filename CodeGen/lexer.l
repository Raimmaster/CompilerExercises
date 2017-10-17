%option noyywrap
%option yylineno

%{
#include "ast.h"
#include "tokens.h"
#include <stdio.h>

Token* current_token = NULL;
%}

%%


[ \t\n]                 { /*NOTHING*/ }
[0-9]+                  { current_token = new Token((string*)NULL, atoi(yytext)); return LIT_INT; }
[_a-zA-Z][a-zA-Z0-9]*   { string* n = new string(yytext); current_token = new Token(n, -1); return TK_ID; }
"("                     { return TK_LEFT_PAR; }
")"                     { return TK_RIGHT_PAR; }
"+"                     { return OP_SUM; }
"-"                     { return OP_SUB; }
"*"                     { return OP_STAR; }
.                       { yyterminate(); }
%%
