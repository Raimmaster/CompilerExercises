#include "ast.h"

int vars[8];

int AddExpr::eval()
{
    int v1 = expr1->eval();
    int v2 = expr2->eval();

    return v1 + v2;
}

int SubExpr::eval()
{
    int v1 = expr1->eval();
    int v2 = expr2->eval();

    return v1 - v2;
}

int MulExpr::eval()
{
    int v1 = expr1->eval();
    int v2 = expr2->eval();

    return v1 * v2;
}

int DivExpr::eval()
{
    int v1 = expr1->eval();
    int v2 = expr2->eval();

    return v1 / v2;
}

int VarExpr::eval()
{
    return vars[index];
}

void AssignStatement::exec()
{

}

void PrintStatement::exec()
{

}

void BlockStatement::exec()
{
    
}
