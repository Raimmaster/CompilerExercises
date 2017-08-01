#ifndef _AST_H
#define _AST_H

class Expr {//abstract by def
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
    Expr *expr1, expr2;

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
}
//RTTI: RunTime Type Info
class VarExpr : public Expr {
public:
    VarExpr(int index)
    {
        this->index = index;
    }
    int index;
    int eval();
}

#endif
