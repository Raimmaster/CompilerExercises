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

enum EXPR_TYPE {
    NUM_EXPR,
    ADD_EXPR,
    SUB_EXPR,
    MULT_EXPR,
    VAR_EXPR
    IMM_EXPR;
}

#define DEFINE_BINARY_EXPR(name, t) \
    class name##Expr : public BinaryExpr { \
    public:                                 \
        name##Expr(Expr* expr1, Expr* expr2) : BinaryExpr(expr1, expr2) { this->type = t##_EXPR; } \
        name##Expr() : BinaryExpr() {}                                      \
        string generate(); \
    }

class Expr {//abstract by def
protected:
    Expr() { }
    ~Expr() { }
public:
    Gen mips_code;
    EXPR_TYPE type;
    virtual int eval() = 0;
    virtual string generate() = 0;
    EXPR_TYPE getType() { return type; }
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
        this->type = NUM_EXPR;
    }
    ~NumberExpr() { }
    int value;
    int eval() { return value; }
    string generate();
};

//RTTI: RunTime Type Info

class VarExpr : public Expr {
public:
    VarExpr(string* index)
    {
        this->index = *index;
        this->type = VAR_EXPR;
    }
    string index;
    int eval() { return 0; }
    string generate();
};

DEFINE_BINARY_EXPR(Add, ADD);
DEFINE_BINARY_EXPR(Sub, SUB);
DEFINE_BINARY_EXPR(Mul, MULT);
#endif
