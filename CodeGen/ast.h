#ifndef _AST_H
#define _AST_H

#include <map>
#include <list>
#include <string>
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include "controllers.h"
using namespace std;

#define SIZE_FLAGS 10

#define DEFINE_BINARY_EXPR(name) \
    class name##Expr : public BinaryExpr { \
    public:                                 \
        name##Expr(Expr* expr1, Expr* expr2) : BinaryExpr(expr1, expr2) {} \
        name##Expr() : BinaryExpr() {}                                      \
        string generate(); \
    }


class Expr {//abstract by def
protected:
    Expr() { }
    ~Expr() { }
public:
    Gen mips_code;
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
    NumberExpr(int value) : Expr()
    {
        this->value = value;
    }
    ~NumberExpr() { }
    int value;
    string generate();
};

//RTTI: RunTime Type Info

class VarExpr : public Expr {
public:
    VarExpr(string* index)
    {
        this->index = *index;
    }
    string index;
    string generate();
};

DEFINE_BINARY_EXPR(Add);
DEFINE_BINARY_EXPR(Sub);
DEFINE_BINARY_EXPR(Mul);
#endif
