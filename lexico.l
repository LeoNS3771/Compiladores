%{
#include <iostream>
#include <string>
#include "symbols.hh"
#include "loops.hh"
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
TYPE    int|float|bool|char|string|void
CAST    \({TYPE}\)
ID      {LETTER}({LETTER}|{DIGIT}|_)*
CHAR    \'[^'\n]?\'
STRING  \"[^"\n]*\"

%%
{DELIM} {}

{STRING} {
    std::string attr = yytext;
    return yy::parser::make_TK_STRING(attr);
}
"#"[^\n]* {}


"fun" {return yy::parser::make_TK_FUNCTION(yytext);} 
"return" {return yy::parser::make_TK_RETURN(yytext);}

"out" { return yy::parser::make_TK_PRINT(yytext); }
"outl" { return yy::parser::make_TK_PRINTL(yytext); }
"input" { return yy::parser::make_TK_INPUT(yytext); }

"if" { return yy::parser::make_TK_IF(yytext); }
"else" { return yy::parser::make_TK_ELSE(yytext); }
"while" { return yy::parser::make_TK_WHILE(yytext); }
"do" { return yy::parser::make_TK_DO(yytext); }
"break" { return yy::parser::make_TK_BREAK(yytext); }
"continue" { return yy::parser::make_TK_CONTINUE(yytext); }
"switch"  { return yy::parser::make_TK_SWITCH(yytext); }
"case"    { return yy::parser::make_TK_CASE(yytext); }
"default" { return yy::parser::make_TK_DEFAULT(yytext); }
"for" { return yy::parser::make_TK_FOR(yytext); }
"in" { return yy::parser::make_TK_IN(yytext); }
"range" { return yy::parser::make_TK_RANGE(yytext); }

"vector" { return yy::parser::make_TK_VECTOR(yytext); }
"append" { return yy::parser::make_TK_APPEND(yytext); }


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

"{"  { return yy::parser::make_TK_SBLOCK(yytext); }

"}"  { return yy::parser::make_TK_EBLOCK(yytext); }


[;:(),.]   {return *yytext;}
"["     { return '['; }
"]"     { return ']'; }
        
.	    { std::cerr << "Erro lexico na linha " << yylineno << ": " << yytext << std::endl;}

%%
