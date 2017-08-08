#include "ast.h"

map<string, int> vars;

#define IMPLEMENT_BINARY_EXPR_EVAL(name, op) \
    int name##Expr::eval() {               \
        int v1 = expr1->eval();             \
        int v2 = expr2->eval();             \
                                            \
        return v1 op v2;                    \
    }

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
    return (vars.at(index));
}

void AssignStatement::exec()
{
    vars[(this->index)] = this->expr->eval();
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

void PrintStatement::exec()
{
    switch(this->format)
    {
        case 0:
            printf("%x\n", this->expr->eval());
            break;
        case 1:
            printf("%d\n", this->expr->eval());
            break;
        case 2:
            printf("%s\n", byte_to_binary(this->expr->eval()));
            break;
    }
    printf("%d \n", this->expr->eval());
}

void BlockStatement::exec()
{
    for (std::list<Statement*>::iterator it = statementList.begin(); it != statementList.end(); ++it)
    {
        (*it)->exec();
    }
}

void IfStatement::exec()
{
    int result = this->condition_expr->eval();
    if(result == 1)
    {
        if(if_body != NULL)
            this->if_body->exec();
    }else
    {
        if(else_body != NULL)
            this->else_body->exec();
    }
}

IMPLEMENT_BINARY_EXPR_EVAL(Equal, ==);
IMPLEMENT_BINARY_EXPR_EVAL(NotEqual, !=);
IMPLEMENT_BINARY_EXPR_EVAL(LessThan, <);
IMPLEMENT_BINARY_EXPR_EVAL(LessEqual, <=);
IMPLEMENT_BINARY_EXPR_EVAL(GreaterThan, >);
IMPLEMENT_BINARY_EXPR_EVAL(GreaterEqual, >=);
