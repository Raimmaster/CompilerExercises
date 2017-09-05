#ifndef _AST_H
#define _AST_H

#include <list>
#include <string>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <map>
using namespace std;

#define DEFINE_BINARY_EXPR(name) \
    class name##Expr : public BinaryExpr { \
    public:                                 \
        name##Expr(Expr* expr1, Expr* expr2) : BinaryExpr(expr1, expr2) {} \
        name##Expr() : BinaryExpr() {}                                      \
        int eval(); \
    }

class Token{
public:
    Token()
    {

    }
    Token(string* lexem, int code)
    {
        this->lexem = lexem;
        this->code = code;
    }
    ~Token()
    {
        printf("Destroying the token of code: %d\n", code);
    }
    string* lexem;
    int code;
};

class Expr {//abstract by def
protected:
    Expr()
    {

    }
public:
    // virtual int eval() = 0;
    virtual string generate() = 0;
};

class BinaryExpr : public Expr
{//abstract by def
protected:
    BinaryExpr(Expr *expr1, Expr *expr2)
    {
        this->expr1 = expr1;
        this->expr2 = expr2;
    };
    BinaryExpr(){}
public:
    Expr *expr1, *expr2;

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
    VarExpr(string* index)
    {
        this->index = *index;
    }
    string index;
    // int eval();
    string generate();
};

class Statement {
protected:
    Statement()
    {

    }
public:
    // virtual void exec() = 0;
    virtual string generate() = 0;
};

class AssignStatement : public Statement {
public:
    AssignStatement(string* index, Expr *expr) : Statement()
    {
        this->index = *index;
        this->expr = expr;
    }
    // void exec();
    string generate();
    string index;
    Expr*   expr;
};

class BlockStatement : public Statement {
public:
    BlockStatement() {}

    void addStatement(Statement *statement)
    {
        statementList.push_back(statement);
    }

    // void exec();
    string generate();
    list<Statement*> statementList;
};



DEFINE_BINARY_EXPR(Add);
DEFINE_BINARY_EXPR(Sub);
DEFINE_BINARY_EXPR(Div);
#endif
