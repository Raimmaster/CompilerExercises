#include "ast.h"

map<string, int> vars;

#define IMPLEMENT_BINARY_EXPR_EVAL(name, op) \
    int name##Expr::eval() {               \
        int v1 = expr1->eval();             \
        int v2 = expr2->eval();             \
                                            \
        return v1 op v2;                    \
    }

int VarExpr::eval()
{
    return (vars.at(this->index));
}

void AssignStatement::exec()
{
    vars[(this->index)] = this->expr->eval();
}

void BlockStatement::exec()
{
    for (auto it = statementList.begin(); it != statementList.end(); ++it)
    {
        (*it)->exec();
    }
}

IMPLEMENT_BINARY_EXPR_EVAL(Add, +);
IMPLEMENT_BINARY_EXPR_EVAL(Sub, -);
IMPLEMENT_BINARY_EXPR_EVAL(Mul, *);
