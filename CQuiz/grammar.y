%include{
    #include <stdio.h>
    #include <assert.h>
}

%start_symbol input

input::= stmt_list .

type::= KW_INT .
type::= KW_CHAR .

stmt_list::= stmt_list stmt .
stmt_list::= stmt .

stmt::= declaration_stmt TK_EOS .
/*stmt::= function_declaration_stmt .*/
stmt::= assignment_stmt TK_EOS .
stmt::= print_stmt TK_EOS .

declaration_stmt::= type TK_ID OP_ASSIGN expr .

/*function_declaration_stmt::= type_or_void TK_ID TK_LEFT_PAR arg_list TK_RIGHT_PAR block_stmt .*/

/*type_or_void::= type .*/
/*type_or_void::= KW_VOID .*/

/*arg_list::= arg_list TK_COMMA arg .
arg_list::= arg .

arg::= type TK_ID .

block_stmt::= TK_LEFT_CB stmt_list TK_RIGHT_CB .*/

assignment_stmt::= TK_ID OP_ASSIGN expr .

print_stmt::= KW_PRINT TK_LEFT_PAR expr TK_RIGHT_PAR .

expr::= expr TK_SUM factor .
expr::= expr TK_SUB factor .
expr::= factor .

factor::= LIT_INT .
factor::= LIT_CHAR .
factor::= TK_LEFT_PAR expr TK_RIGHT_PAR .
