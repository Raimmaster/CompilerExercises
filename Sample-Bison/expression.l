%option noyywrap
%option yylineno
%x comment
%x comment_in_eol
%x include
%x eol

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
  char * trim(char* s, char* val);
  extern void yyerror(const char*);
%}

%%
[ \t]+                          { /* NADA */ }
"/*"                            { BEGIN(comment); }
"//".*\n                        { BEGIN(eol); }
^"#"[ \t]*"include"[ \t]*       { BEGIN(include); }
"+"                             { return OP_ADD; }
"-"                             { return OP_SUB; }
"/"                             { return OP_DIV; }
"*"                             { return OP_MUL; }
"("                             { return TK_LEFT_PAR; }
")"                             { return TK_RIGHT_PAR; }
"{"                             { return TK_LEFT_CURLY_BRACK; }
"}"                             { return TK_RIGHT_CURLY_BRACK; }
","                             { return TK_COMMA; }
"print"                         { return TK_PRINT; }
"="                             { return TK_EQ; }
"=="                            { return TK_COMPARE; }
"!="                            { return TK_NOT_EQ; }
">"                             { return TK_GREATER_THAN; }
"<"                             { return TK_LESS_THAN; }
">="                            { return TK_GREATER_EQUAL; }
"<="                            { return TK_LESS_EQUAL; }
"hex"                           { return KW_HEX; }
"dec"                           { return KW_DEC; }
"bin"                           { return KW_BIN; }
"if"                            { return KW_IF; }
"else"                          { yyerror("Keyword 'else' unexpected here."); return KW_ELSE; }
[_a-zA-Z][a-zA-Z0-9_]*          { yylval.string_t = new string(yytext); return TK_ID; }
[0-9]+                          { yylval.int_t = atoi(yytext); return TK_NUMBER; }
"\n"                            { BEGIN(eol); }
<<EOF>>                         {
                                    if(pop_file() != 0)
                                    {
                                        yyterminate();
                                    }
                                }
.                               { return TK_ERROR; }
<include>[\"<][^\"\n]+[\">]     {
                                    {
                                        int c;
                                        char* original_text = yytext;
                                        int len = strlen(original_text);
                                        char* filename = (char*)malloc(sizeof(char) * (len + 1));
                                        memset(filename, '\0', len);
                                        strncpy(filename, original_text, len);
                                        filename = trim(filename, " ");
                                        char init_char = filename[0];
                                        char final_char = filename[len-1];
                                        if(init_char != final_char)
                                        {
                                            if(!(init_char == '<' && final_char == '>'))
                                            {
                                                fprintf(
                                                    stderr,
                                                    "Enclosing characters must be the same. Init is %c and final is %c\n",
                                                    init_char,
                                                    final_char
                                                    );
                                                free(filename);
                                                yyterminate();
                                            }
                                        }
                                        if(init_char == '"')
                                        {
                                            filename = trim(filename, "\"");
                                        }else
                                        {
                                            filename = trim(filename, "<");
                                            filename = trim(filename, ">");
                                        }
                                        if(push_file(filename) != 0)
                                        {
                                            free(filename);
                                            yyterminate();
                                        }
                                        free(filename);
                                        BEGIN(INITIAL);
                                    }
                                }
<include>.\n                    {
                                    fprintf(stderr, "Bad included line at : %d \n", yylineno);
                                    yyterminate();
                                }
<comment>"*/"                   { BEGIN(INITIAL); }
<comment><<EOF>>                { printf("Line: %d: Block comment without end.\n", yylineno); return 0;}
<comment>.|\n                   { /* Nothing */ }
<eol>\n                         { /* Nothing */ }
<eol>"//".*\n                   { /* Nothing */ }
<eol>"/*"                       { BEGIN(comment_in_eol); }
<eol>[ \t]                      { /* Nothing */ }
<eol>"else"                     { BEGIN(INITIAL); return KW_ELSE; }
<eol>^"#"[ \t]*"include"[ \t]*  { BEGIN(include); return TK_EOL; }
<eol><<EOF>>                    { BEGIN(INITIAL); return TK_EOL; }
<eol>.                          { BEGIN(INITIAL); unput(yytext[0]); return TK_EOL; }

<comment_in_eol>"*/"            { BEGIN(eol); }
<comment_in_eol>\n              { /* Nothing */ }
%%

int push_file(char *filename)
{
  FILE* f = fopen(filename, "r");
  if( f == NULL)
  {
    fprintf(stderr, "File %s not found.", filename);
    return 1;
  }

  include_stack_t* istack = (include_stack_t*)malloc(sizeof(include_stack_t));
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

char * trim(char* s, char* val) {
    int l = strlen(s);

    while(s[l - 1] == *val) --l;
    while(* s && * s == *val) ++s, --l;

    return strndup(s, l);
}
