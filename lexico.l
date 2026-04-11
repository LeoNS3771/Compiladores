%{
#include <string>
#include "y.tab.hh"
#include "tokens.hh"

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
ID      {LETTER}({LETTER}|{DIGIT}|_)*
CHAR    \'([^\'\\\n]|\\.)\'

%%

{DELIM} {}

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

"true"  {
            literal attr; 
            attr.label = "1"; 
            return yy::parser::make_TK_BOOL(attr);
        }

"false" {
            literal attr; 
            attr.label = "0"; 
            return yy::parser::make_TK_BOOL(attr);
        }

{FLOAT} {
            literal attr;
            attr.label = yytext;
            return yy::parser::make_TK_FLOAT(attr);
        }

{INT}   {
            literal attr;
            attr.label = yytext;
            return yy::parser::make_TK_INT(attr);
        }   

{TYPE}  { 
            std::string s = yytext;
            literal attr;
            attr.label = (s == "bool") ? "int" : s;
            return yy::parser::make_TK_TYPE(attr);
        }

{ID}    { 
            symbol attr;
            attr.label = yytext;
            return yy::parser::make_TK_ID(attr);
        }

{CHAR}  {
            literal attr;
            attr.label = yytext;
            return yy::parser::make_TK_CHAR(attr);
        }

[;()]   {return *yytext;}
[+\-*/%] {return *yytext;}
        
.	    { std::cerr << "Erro lexico na linha " << yylineno << ": " << yytext << std::endl;}

%%