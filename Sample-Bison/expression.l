%option noyywrap
%{
  #include <stdio.h>
  #include "tokens.h"
%}

%%
[ \t]+  { /* NADA */ }
"+"         { return OP_ADD; }
"-"         { return OP_SUB; }
"*"         { return OP_MUL; }
"/"         { return OP_DIV; }
"("         { return TK_LEFT_PAR; }
")"         { return TK_RIGHT_PAR; }
"$"[0-7]    { yylval = atoi(yytext + 1) ; return TK_ID; }
"print"     { return TK_PRINT; }
"="         { return TK_EQ; }
[0-9]+      { yylval = atoi(yytext); return TK_NUMBER; }
"\n"        { return TK_EOL; }
.           { return TK_ERROR; }

%%
