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
    stringstream code;
    string v1, v2;
    string op;
    bool first_reg_is_number = type_expr1 == IMM_EXPR;
    bool second_reg_is_number = type_expr2 == IMM_EXPR;
    // cout<<"Is reg1: "<<first_reg_is_number<<" and reg2: "<<second_reg_is_number<<endl;
    printf("R1: %d R2: %d \n", first_reg_is_number, second_reg_is_number);
    if((first_reg_is_number) && (second_reg_is_number))
    {
        cout<<"My old type: "<<getType()<<endl;
        this->type = IMM_EXPR;
        string empty = ""; 
        cout<<"L and R are imms"<<endl;
        stringstream st;
        int result = expr1->eval() + expr2->eval();
        mips_code.place = reg_control->getNext();
        code<<"li $t"<<mips_code.place<<", "<<result<<endl;
        mips_code.code = code.str();
        cout<<"My type: "<<getType()<<endl;
        return mips_code.code;   
    }else if (first_reg_is_number)
    {
        v2 = expr2->generate();
        reg_control->freePlace(expr2->mips_code.place);
        this->mips_code.place = reg_control->getNext();
        code<<v2;
        code<<"addi $t"<<mips_code.place<<", $t"<<expr2->mips_code.place<<", "<<expr1->eval()<<endl;
        cout<<"L is imm"<<endl;
        this->mips_code.code = code.str();
        return this->mips_code.code;
    }else if (second_reg_is_number)
    {
        v1 = expr1->generate();
        reg_control->freePlace(expr1->mips_code.place);
        this->mips_code.place = reg_control->getNext();
        code<<v1;
        code<<"addi $t"<<mips_code.place<<", $t"<<expr1->mips_code.place<<", "<<expr2->eval()<<endl;
        cout<<"R is imm"<<endl;       
        this->mips_code.code = code.str(); 
        return this->mips_code.code;
    }
    v1 = expr1->generate();  
    v2 = expr2->generate();      
    reg_control->freePlace(expr1->mips_code.place); 
    reg_control->freePlace(expr2->mips_code.place); 
    cout<<"Normal add"<<endl;
    code<<v1<<v2;   
    this->mips_code.place = reg_control->getNext(); 
    code<<"add $t"<<this->mips_code.place<<", $t"<<expr1->mips_code.place<<", $t"<<expr2->mips_code.place<<endl; 
    this->mips_code.code = code.str(); 
    return this->mips_code.code;    
}

IMPLEMENT_THREE_REG_EXPR_GEN(Sub, "sub");
IMPLEMENT_TWO_REG_EXPR_GEN(Mul, "mult");

IMPLEMENT_EXPR_EVAL(Add, +);
IMPLEMENT_EXPR_EVAL(Sub, -);
IMPLEMENT_EXPR_EVAL(Mul, *);