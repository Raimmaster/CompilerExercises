#include "ast.h"

#define IMPLEMENT_THREE_REG_EXPR_GEN(name, op) \
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

#define IMPLEMENT_EXPR_GET_TYPE(className, typeName) \
    EXPR_TYPE className##Expr::getType() \
    {   \
        return typeName##_EXPR; \
    }   

#define IMPLEMENT_TWO_REG_EXPR_GEN(name, op) \
    string name##Expr::generate() \
    {                                   \
        string v1 = expr1->generate();  \
        string v2 = expr2->generate();      \
        reg_control->freePlace(expr1->mips_code.place); \
        reg_control->freePlace(expr2->mips_code.place); \
        stringstream code;      \
        code<<v1<<v2;   \
        this->mips_code.place = reg_control->getNext(); \
        code<< op <<" $t"<<expr1->mips_code.place<<", $t"<<expr2->mips_code.place<<endl; \
        this->mips_code.place = reg_control->getNext();                                   \
        code<<"mflo $t"<<this->mips_code.place<<endl;                                      \
        this->mips_code.code = code.str();  \
        return this->mips_code.code;    \
    }

#define IMPLEMENT_EXPR_EVAL(name, op) \
    int name##Expr::eval(){ \
        int v1 = expr1->eval(); \
        int v2 = expr2->eval(); \
        return v1 op v2;    \
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

string VarExpr::generate()
{
    stringstream code;
    this->mips_code.place = reg_control->getNext();
    code<<"lw $t"<<this->mips_code.place<<", "<<this->index<<endl;
    this->mips_code.code = code.str();

    return this->mips_code.code;
}

string AddExpr::generate() 
{                
    EXPR_TYPE type_expr1 = expr1->getType();                  
    EXPR_TYPE type_expr2 = expr2->getType();
    
    if(type_expr1 == NUM_EXPR || type_expr1 == IMM_EXPR)
    {
        if(type_expr2 == NUM_EXPR || type_expr2 == IMM_EXPR)
        {
            //Must add immmediates
            this->type = IMM_EXPR;
            string empty = "";
            return empty;
        }
    }
    
    string v1 = expr1->generate();  
    string v2 = expr2->generate();      
    reg_control->freePlace(expr1->mips_code.place); 
    reg_control->freePlace(expr2->mips_code.place); 
    stringstream code;      
    code<<v1<<v2;   
    this->mips_code.place = reg_control->getNext(); 
    code<<"add $t"<<this->mips_code.place<<", $t"<<expr1->mips_code.place<<", $t"<<expr2->mips_code.place<<endl; 
    this->mips_code.code = code.str(); 
    return this->mips_code.code;    
}

// IMPLEMENT_THREE_REG_EXPR_GEN(Add, "add");
IMPLEMENT_THREE_REG_EXPR_GEN(Sub, "sub");
IMPLEMENT_TWO_REG_EXPR_GEN(Mul, "mult");

IMPLEMENT_EXPR_EVAL(Add, +);

// #IMPLEMENT_EXPR_GET_TYPE(Add, ADD);
// #IMPLEMENT_EXPR_GET_TYPE(Sub, SUB);
// #IMPLEMENT_EXPR_GET_TYPE(Mul, MULT);
// #IMPLEMENT_EXPR_GET_TYPE(Var, VAR);
// #IMPLEMENT_EXPR_GET_TYPE(Num, NUM);