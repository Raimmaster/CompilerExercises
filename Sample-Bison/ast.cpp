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
    vars[this->index] = this->expr->eval();
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
