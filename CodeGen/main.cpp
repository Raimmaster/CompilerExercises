#include "ast.h"
#include <stdio.h>
#include "tokens.h"

void *ParserAlloc(void *(*allocProc)(size_t));
void *Parser(void *, int, Token *);
void *ParserFree(void *, void (*freeProc)(void *));
int yylex();
extern Token *current_token;

int main(int argc, char *argv[])
{
    void *parser = ParserAlloc(malloc);
    int token = yylex();

    while (token != 0)
    {
        Parser(parser, token, current_token);
        token = yylex();
    }
    Parser(parser, 0, current_token);

    ParserFree(parser, free);

    return 0;
}
