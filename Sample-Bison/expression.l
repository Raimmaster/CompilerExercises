%option noyywrap
%option yylineno
%x comment
%x include

%{
  #include <stdio.h>
  #include "tokens.h"

  typedef struct include_stack{
    struct include_stack* previous_stack;
    FILE*                 file;
    YY_BUFFER_STATE       buffer_state;
    int                   prev_lineno;
    char*                 filename;
  } include_stack_t;

  include_stack_t* incl_stack = NULL;
  char* yyfilename;
  int push_file(char*);
  int pop_file();
%}

%%
[ \t]+  { /* NADA */ }
"/*"                        { BEGIN(comment); }
"//".*\n                    { return TK_EOL; }
^"#"[ \t]*"include"[ \t]*\" { BEGIN(include); }
"+"                         { return OP_ADD; }
"-"                         { return OP_SUB; }
"*"                         { return OP_MUL; }
"/"                         { return OP_DIV; }
"("                         { return TK_LEFT_PAR; }
")"                         { return TK_RIGHT_PAR; }
"$"[0-7]                    { yylval = atoi(yytext + 1) ; return TK_ID; }
"print"                     { return TK_PRINT; }
"="                         { return TK_EQ; }
[0-9]+                      { yylval = atoi(yytext); return TK_NUMBER; }
"\n"                        { return TK_EOL; }
<<EOF>>                     {
                                if(pop_file() != 0)
                                {
                                    yyterminate();
                                }
                            }
.                           { return TK_ERROR; }

<include>[^\"\n]+   {
                      {
                        int c;
                        while((c = input()) && c!= '\n');
                        ++yylineno;
                        if(push_file(yytext) != 0)
                        {
                            yyterminate();
                        }

                        BEGIN(INITIAL);
                      }
                    }

<comment>"*/"     { BEGIN(INITIAL); }
<comment>.|\n     { /* Nothing */ }
<comment><<EOF>>  { printf("Line: %d: Block comment without end.\n", yylineno); return 0;}
%%

int push_file(char *filename)
{
  FILE* f = fopen(filename, "r");
  if( f == NULL)
  {
    fprintf(stderr, "File %s not found.", filename);
    return 1;
  }

  include_stack_t* istack = malloc(sizeof(include_stack_t));
  if(istack == NULL)
  {
      fprintf(stderr, "Out of memory.");
      return 1;
  }

  istack->file = f;
  istack->prev_lineno = yylineno;
  istack->filename = yyfilename;
  istack->buffer_state = yy_create_buffer(f, YY_BUF_SIZE);
  istack->previous_stack = incl_stack;
  incl_stack = istack;
  yyfilename = filename;
  yylineno = 1;
  yy_switch_to_buffer(istack->buffer_state);
  return 0;
}

int pop_file()
{
    include_stack_t* prev_is = incl_stack->previous_stack;
    fclose(incl_stack->file);
    yy_delete_buffer(incl_stack->buffer_state);
    yylineno = incl_stack->prev_lineno;
    yyfilename = incl_stack->filename;

    free(incl_stack);

    if(prev_is == NULL)
    {
      return 1;
    }

    yy_switch_to_buffer(prev_is->buffer_state);
    incl_stack = prev_is;

    return 0;
}
