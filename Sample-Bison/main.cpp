#include <stdio.h>

int yylex();
void yyparse();
extern FILE* yyin;
int push_file(char *);
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        return 1;
    }
    if(push_file(argv[1]) != 0)
    {
        return 1;
    }
    yyparse();

    return 0;
}
