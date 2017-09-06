%include{
    #include "ast.h"
    #include <stdio.h>
    #include <iostream>
    #include <assert.h>

    using namespace std;
}

%token_type { Token * }
%default_type { Expr* }
%name Parser

%type expr { Expr* }
%type sub_expr { Expr* }
%type factor { Expr* }

%start_symbol input

input::= expr(E) . { cout<<"Generated: "<<endl<<endl<<E->generate()<<endl; }

expr(E)::= expr(L) OP_SUM sup_expr(R) . { E = new AddExpr(L, R); }
expr(E)::= expr(L) OP_SUB sup_expr(R) . { E = new SubExpr(L, R); }
expr(E)::= sup_expr(S) .                { E = S; }

sup_expr(S)::= sup_expr(L) OP_STAR factor(R) . { S = new MulExpr(L, R); }
sup_expr(S)::= factor(F) .                     { S = F; }

factor(F)::= LIT_INT(N) . { F = new NumberExpr(N->val); delete N; }
factor(F)::= TK_ID(N) . { F = new VarExpr(N->lexem); delete N; }
factor(F)::= TK_LEFT_PAR expr(E) TK_RIGHT_PAR . { F = E; }
