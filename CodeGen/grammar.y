%include{
    #include "ast.h"
    #include <stdio.h>
    #include <assert.h>
}

%start_symbol input

/*input(I)::= stmt_list (S) . { I = S->generate(); }*/

input(I)::= expr . { I->generate(); }

/*stmt_list(S)::= stmt_list(ST) stmt(SM) . { S = ST; ((BlockStatement*)ST)->addStatement(SM); }*/
/*stmt_list(S)::= stmt(SM) . { S = SM; }*/

/*stmt(S)::= assignment_stmt(A) TK_EOS . { S = A; }*/

/*assignment_stmt(A)::= TK_ID(I) OP_ASSIGN expr(E) . { A = new AssignmentStatement(I, E); }*/

expr(E)::= expr(L) OP_SUM sup_expr(R) . { E = new SumExpr(L, R); }
expr(E)::= expr(L) OP_SUB sup_expr(R) . { E = new SubExpr(L, R); }
expr(E)::= sup_expr(S) .             { E = S; }

sup_expr(S)::= sup_expr(L) OP_STAR factor(R) . { E = new MulExpr(L, R); }
sup_expr(S)::= factor(F) . { S = F; }

factor(F)::= LIT_INT(N) . { F = new NumberExpr(N); }
factor(F)::= TK_LEFT_PAR expr(E) TK_RIGHT_PAR . { F = E; }
