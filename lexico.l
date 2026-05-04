%{
#include <iostream>
#include <string>
#include "symbols.hh"
#include "y.tab.hh"

#define YY_DECL yy::parser::symbol_type yylex()
%}

%option noyywrap yylineno

SPACE   [ \t\n]
DELIM   {SPACE}+
DIGIT   [0-9]
LETTER  [a-zA-Z]
FRAC    \.{DIGIT}*
EXP     [eE][+\-]?{DIGIT}+

FLOAT   ({DIGIT}+{FRAC}{EXP}?)|({DIGIT}+{EXP})
INT     {DIGIT}+
TYPE    int|float|bool|char
CAST    \({TYPE}\)
ID      {LETTER}({LETTER}|{DIGIT}|_)*
CHAR    \'([^\'\\\n]|\\.)\'

%%

{DELIM} {}

"+"     {return yy::parser::make_OP_ADD();}
"-"     {return yy::parser::make_OP_MINUS();}
"*"     {return yy::parser::make_OP_MULT();}
"/"     {return yy::parser::make_OP_DIV();}
"%"     {return yy::parser::make_OP_MOD();}

"=="     {return yy::parser::make_OP_EQ();}
"!="     {return yy::parser::make_OP_NE();}
"<="     {return yy::parser::make_OP_LE();}
">="     {return yy::parser::make_OP_GE();}
"<"      {return yy::parser::make_OP_LT();}
">"      {return yy::parser::make_OP_GT();}

"||"     {return yy::parser::make_OP_OR();}
"&&"     {return yy::parser::make_OP_AND();}
"!"      {return yy::parser::make_OP_NOT();}
"="      {return yy::parser::make_OP_AT();}

"var"   {
            std::string attr = yytext;
            return yy::parser::make_TK_VAR(attr);
        }

"true"  {
            std::string attr = "1";
            return yy::parser::make_TK_BOOL(attr);
        }

"false" {
            std::string attr = "0";
            return yy::parser::make_TK_BOOL(attr);
        }

{FLOAT} {
            std::string attr = yytext;
            return yy::parser::make_TK_FLOAT(attr);
        }

{INT}   {
            std::string attr = yytext;
            return yy::parser::make_TK_INT(attr);
        }   

{TYPE}  { 
            std::string attr = yytext;
            attr = (attr == "bool") ? "int" : yytext;
            return yy::parser::make_TK_TYPE(attr);
        }

{CAST}  {
            std::string attr = yytext;
            return yy::parser::make_TK_CAST(attr.substr(1,attr.size()-2));
        }

{ID}    {
            std::string name = yytext;
            auto sym = std::make_shared<symbol>(name);
            return yy::parser::make_TK_ID(sym);
        }

{CHAR}  {
            std::string attr = yytext;
            return yy::parser::make_TK_CHAR(attr);
        }

[;:()]   {return *yytext;}
        
.	    { std::cerr << "Erro lexico na linha " << yylineno << ": " << yytext << std::endl;}

%%