#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

int finalResult = 0;
int token;
int expr();
int term();
int factor();
int yylex();
extern char* yytext;

int list_expr()
{
    switch(token)
    {
        case TK_NUMBER:
        case TK_LEFT_PAR:
        case TK_EOL:
        {
            int op = token;
            int result = expr();
            if(op != TK_EOL)
            {
                printf("Result: %d\n", result);
            }
            list_expr();
            return 0;
        }
        case TK_RIGHT_PAR:
            printf("Wrong start! Expect a valid operand, number, or '('\n");
            return -1;
        default:
            printf("The end!\n");
            return 0;
    }
}

int expr()
{
    // printf("Checking expr!\n");
    int result = term();
    switch(token)
    {
        case OP_ADD:
        case OP_SUB:
        {
            // printf("Sub or sum\n");
            while (token == OP_ADD || token == OP_SUB)
            {
                int op = token;
                token = yylex();
                if(op == OP_ADD)
                    result += term();
                else
                    result -= term();
            }
            break;
        }
        default:
            break;
    }
    return result;
}

int term()
{
    // printf("Checking term!\n");
    int result = factor();
    switch(token)
    {
        case OP_MUL:
        case OP_DIV:
        {
            // printf("Div or mul\n");
            while (token == OP_MUL || token == OP_DIV)
            {
                int op = token;
                token = yylex();
                if(op == OP_MUL)
                    result *= factor();
                else
                    result /= factor();
                }
            break;
        }
        default:
            break;
    }
    return result;
}

int factor()
{
    // printf("Checking factor!\n");
    int result = 0;
    switch(token)
    {
        case TK_NUMBER:
            // printf("Found num %s\n", yytext);
            result = atoi(yytext);
            token = yylex();
            return result;

        case TK_LEFT_PAR:
            token = yylex();
            result = expr();
            if(token == TK_RIGHT_PAR)
            {
                // printf("Consuming ) \n" );
                token = yylex();
            }else
            {
                printf("Error expected ')'\n");
            }

            return result;
        case TK_EOL:
        // {
            // printf("END OF LINE: %d\n", result);
            //result = 0;
            token = yylex();
            return result;
        // }
        default:
            printf("Error: expected '(' or a number.\n");
            return -1;
    }
}
