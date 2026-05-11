%{
#include <iostream>
#include <string>
#include "symbols.hh"
#include "y.tab.hh"

#define YY_DECL yy::parser::symbol_type yylex()
extern std::vector<std::string> errors;
void lexical_error();
%}

%option noyywrap yylineno

SPACE   [ \t\n]
DELIM   {SPACE}+
DIGIT   [0-9]
LETTER  [a-zA-Z]
FRAC    \.{DIGIT}+
EXP     [eE][+\-]?{DIGIT}+

FLOAT   ({DIGIT}+{FRAC}({EXP})?)|({DIGIT}+{EXP})
INT     {DIGIT}+
TYPE    int|float|bool|char
CAST    \({TYPE}\)
ID      {LETTER}({LETTER}|{DIGIT}|_)*
CHAR    \'([^\\\'\n]|\\.)\' /* Validação léxica será adicionada depois */

%%

{DELIM} {}

"+"     {return yy::parser::make_OP_ADD({yytext, "arithmetic"});}
"-"     {return yy::parser::make_OP_MINUS({yytext, "arithmetic"});}
"*"     {return yy::parser::make_OP_MULT({yytext, "arithmetic"});}
"/"     {return yy::parser::make_OP_DIV({yytext, "arithmetic"});}
"%"     {return yy::parser::make_OP_MOD({yytext, "arithmetic"});}

"=="     {return yy::parser::make_OP_EQ({yytext, "relational"});}
"!="     {return yy::parser::make_OP_NE({yytext, "relational"});}
"<="     {return yy::parser::make_OP_LE({yytext, "relational"});}
">="     {return yy::parser::make_OP_GE({yytext, "relational"});}
"<"      {return yy::parser::make_OP_LT({yytext, "relational"});}
">"      {return yy::parser::make_OP_GT({yytext, "relational"});}

"||"     {return yy::parser::make_OP_OR({yytext, "logical"});}
"&&"     {return yy::parser::make_OP_AND({yytext, "logical"});}
"!"      {return yy::parser::make_OP_NOT({yytext, "logical"});}
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
            //attr = (attr == "bool") ? "int" : yytext;
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

[;:()]  {return *yytext;}
        
.       {lexical_error();}
            

%%

void lexical_error(){
    errors.push_back("ERRO LÉXICO: linha (" + std::to_string(yylineno) + "): símbolo inválido '" + std::string(yytext) + "'");
}