/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 61 "grammer.y" /* yacc.c:1909  */

	#include <vector>
	using namespace std;

#line 49 "y.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    FOR = 261,
    INT = 262,
    FLOAT = 263,
    BOOLEAN = 264,
    SEMI_COLON = 265,
    ASSIGN = 266,
    LEFT_BRACKET = 267,
    RIGHT_BRACKET = 268,
    LEFT_CURLY_BRACKET = 269,
    RIGHT_CURLY_BRACKET = 270,
    COMMA = 271,
    PRINT = 272,
    I_NUM = 273,
    F_NUM = 274,
    BOOL = 275,
    ID = 276,
    ARITH_OP = 277,
    RELA_OP = 278,
    BOOL_OP = 279
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define FOR 261
#define INT 262
#define FLOAT 263
#define BOOLEAN 264
#define SEMI_COLON 265
#define ASSIGN 266
#define LEFT_BRACKET 267
#define RIGHT_BRACKET 268
#define LEFT_CURLY_BRACKET 269
#define RIGHT_CURLY_BRACKET 270
#define COMMA 271
#define PRINT 272
#define I_NUM 273
#define F_NUM 274
#define BOOL 275
#define ID 276
#define ARITH_OP 277
#define RELA_OP 278
#define BOOL_OP 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 66 "grammer.y" /* yacc.c:1909  */

	/* values */
	int iVal, boolVal;
	char *idLexVal, *opLexVal;
	float fVal;	

	/* types */
	int sType;
	struct {
		vector<int> *nextList;
	} stmt_type;
	struct {
		int sType;
	} expr_type;
	struct {
		vector<int> *trueList, *falseList;
	} bexpr_type;

#line 128 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
