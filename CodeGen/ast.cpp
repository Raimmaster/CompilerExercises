#include "ast.h"

#define IMPLEMENT_EXPR_GEN(name, op) \
    string name##Expr::generate() \
    {                                   \
        string v1 = expr1->generate();  \
        string v2 = expr2->generate();      \
        reg_control->freePlace(expr1->mips_code.place); \
        reg_control->freePlace(expr2->mips_code.place); \
        stringstream code;      \
        code<<v1<<v2;   \
        this->mips_code.place = reg_control->getNext(); \
        code<< op <<" $t"<<this->mips_code.place<<", $t"<<expr1->mips_code.place<<", $t"<<expr2->mips_code.place<<endl; \
        this->mips_code.code = code.str(); \
        return this->mips_code.code;    \
    }

RegisterControl* reg_control = new RegisterControl();

string NumberExpr::generate()
{
    stringstream code;
    this->mips_code.place = reg_control->getNext();
    code<<"li $t"<<mips_code.place<<", "<<this->value<<endl;
    this->mips_code.code = code.str();
    return this->mips_code.code;
}

string MulExpr::generate()
{
    stringstream code;
    string v1 = expr1->generate();
    string v2 = expr2->generate();
    reg_control->freePlace(expr1->mips_code.place);
    reg_control->freePlace(expr2->mips_code.place);
    code<<v1<<v2;
    code<<"mult $t"<<expr1->mips_code.place<<", $t"<<expr2->mips_code.place<<endl;
    reg_control->freePlace(this->mips_code.place);
    this->mips_code.place = reg_control->getNext();
    code<<"mflo $t"<<this->mips_code.place<<endl;
    this->mips_code.code = code.str();
    return this->mips_code.code;
}

string VarExpr::generate()
{
    stringstream code;
    this->mips_code.place = reg_control->getNext();
    code<<"lw $t"<<this->mips_code.place<<", "<<this->index<<endl;
    this->mips_code.code = code.str();

    return this->mips_code.code;
}

IMPLEMENT_EXPR_GEN(Add, "add");
IMPLEMENT_EXPR_GEN(Sub, "sub");
