#ifndef _AST_H
#define _AST_H

#include <list>
#include <stdio.h>
#include <string.h>

using namespace std;

class Expr {//abstract by def
protected:
    Expr()
    {

    }
public:
    virtual int eval() = 0;
};

class BinaryExpr : public Expr
{//abstract by def
protected:
    BinaryExpr(Expr *expr1, Expr *expr2)
    {
        this->expr1 = expr1;
        this->expr2 = expr2;
    };
public:
    Expr *expr1, *expr2;

};

class AddExpr : public BinaryExpr {
public:
    AddExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2)
    {

    }
    int eval();
};

class SubExpr : public BinaryExpr {
public:
    SubExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2)
    {

    }
    int eval();
};

class MulExpr : public BinaryExpr {
public:
    MulExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2)
    {

    }
    int eval();
};

class DivExpr : public BinaryExpr {
public:
    DivExpr(Expr *expr1, Expr *expr2) : BinaryExpr(expr1, expr2)
    {

    }
    int eval();
};

class NumberExpr : public Expr {
public:
    NumberExpr(int value)
    {
        this->value = value;
    }
    int value;
    int eval()
    {
        return value;
    }
};
//RTTI: RunTime Type Info
class VarExpr : public Expr {
public:
    VarExpr(int index)
    {
        this->index = index;
    }
    int index;
    int eval();
};

class Statement {
protected:
    Statement()
    {

    }
public:
    virtual void exec() = 0;
};

class AssignStatement : public Statement {
public:
    AssignStatement(int index, Expr *expr) : Statement()
    {
        this->index = index;
        this->expr = expr;
    }
    void exec();

    int     index;
    Expr*   expr;
};

class PrintStatement : public Statement {
public:
    PrintStatement(Expr *expr, int format) : Statement()
    {
        this->expr = expr;
        this->format = format;
    }
    void exec();

    Expr *expr;
    int format;
};

class BlockStatement : public Statement {
public:
    BlockStatement() {}

    void addStatement(Statement *statement)
    {
        statementList.push_back(statement);
    }

    void exec();

    list<Statement*> statementList;
};

class ConditionalExpr : public BinaryExpr {
public:
    ConditionalExpr(Expr* left_side, Expr* right_side) : BinaryExpr(left_side, right_side)
    {
    }
    int eval();
}

class IfStatement : public Statement {
public:
    IfStatement(ConditionalExpr* condition_expr, BlockStatement* if_body, BlockStatement* else_body)
    {
        this->condition_expr = condition_expr;
        this->if_body = if_body;
        this->else_body = else_body;
    }
    ConditionalExpr* condition_expr;
    BlockStatement* if_body;
    BlockStatement* else_body;

    void exec();
}

#endif
