/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_TOKENS_H_INCLUDED
# define YY_YY_TOKENS_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "expr.y" /* yacc.c:1909  */

    #include "ast.h"

#line 48 "tokens.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OP_ADD = 258,
    OP_SUB = 259,
    OP_MUL = 260,
    OP_DIV = 261,
    TK_LEFT_PAR = 262,
    TK_RIGHT_PAR = 263,
    TK_NUMBER = 264,
    TK_ID = 265,
    TK_EOF = 266,
    TK_EOL = 267,
    TK_ERROR = 268,
    TK_PRINT = 269,
    TK_EQ = 270,
    KW_HEX = 271,
    KW_DEC = 272,
    KW_BIN = 273,
    TK_COMMA = 274,
    TK_LEFT_CURLY_BRACK = 275,
    TK_RIGHT_CURLY_BRACK = 276,
    TK_COMPARE = 277,
    TK_NOT_EQ = 278,
    TK_GREATER_THAN = 279,
    TK_GREATER_EQUAL = 280,
    TK_LESS_THAN = 281,
    TK_LESS_EQUAL = 282,
    KW_IF = 283,
    KW_ELSE = 284
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 22 "expr.y" /* yacc.c:1909  */

    Statement* statement_t;
    Expr* expr_t;
    int int_t;
    string* string_t;

#line 97 "tokens.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TOKENS_H_INCLUDED  */
