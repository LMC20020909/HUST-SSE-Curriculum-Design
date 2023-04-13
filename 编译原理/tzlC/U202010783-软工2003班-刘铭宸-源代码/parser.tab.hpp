/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    ID = 259,
    TYPE = 260,
    FLOAT = 261,
    DPLUS = 262,
    DMINUS = 263,
    PLUSD = 264,
    MINUSD = 265,
    LP = 266,
    RP = 267,
    LB = 268,
    RB = 269,
    LC = 270,
    RC = 271,
    SEMI = 272,
    COMMA = 273,
    PLUS = 274,
    MINUS = 275,
    STAR = 276,
    DIV = 277,
    MOD = 278,
    GE = 279,
    GT = 280,
    LE = 281,
    LT = 282,
    NE = 283,
    EQ = 284,
    ASSIGN = 285,
    AND = 286,
    OR = 287,
    NOT = 288,
    IF = 289,
    ELSE = 290,
    WHILE = 291,
    RETURN = 292,
    FOR = 293,
    BREAK = 294,
    CONTINUE = 295,
    SWITCH = 296,
    CASE = 297,
    DEFAULT = 298,
    COLON = 299,
    EXT_DEF_LIST = 300,
    EXT_VAR_DEF = 301,
    FUNC_DEF = 302,
    FUNC_DEC = 303,
    EXT_DEC_LIST = 304,
    PARAM_LIST = 305,
    PARAM_DEC = 306,
    VAR_DEF = 307,
    DEC_LIST = 308,
    DEF_LIST = 309,
    COMP_STM = 310,
    STM_LIST = 311,
    EXP_STMT = 312,
    IF_THEN = 313,
    IF_THEN_ELSE = 314,
    FUNC_CALL = 315,
    ARGS = 316,
    FUNCTION = 317,
    PARAM = 318,
    ARG = 319,
    CALL = 320,
    CALL0 = 321,
    LABEL = 322,
    GOTO = 323,
    JLT = 324,
    JLE = 325,
    JGT = 326,
    JGE = 327,
    JEQ = 328,
    JNE = 329,
    END = 330,
    ARRASSIGN = 331,
    ARRLOAD = 332,
    UMINUS = 333,
    UPLUS = 334,
    LOWER_THEN_ELSE = 335
  };
#endif

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */
