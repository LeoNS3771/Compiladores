%{
#include <string>
%}

%option noyywrap

ESPACO [ \t]
DIGITO [0-9]

DELIM {ESPACO}+
NUM {DIGITO}+

%%

"\n"		{ linha++; }

{DELIM} 	{}

[+*/\-=;()]			{ return *yytext; }

"int"           { yylval.label = yytext; return TK_TYPE; }
"float"         { yylval.label = yytext; return TK_TYPE; }
"bool"          { yylval.label = "int"; return TK_TYPE; }
"char"          { yylval.label = yytext; return TK_TYPE; }

"true" { fprintf(stderr, "DEBUG: true reconhecido\n"); yylval.label = "1"; return TK_BOOL_VALUE; }
"false"         {yylval.label = "0"; return TK_BOOL_VALUE; }

"<"             {yylval.label = yytext; return TK_REL; }
">"             {yylval.label = yytext; return TK_REL; }
"<="            {yylval.label = yytext; return TK_REL; }
">="            {yylval.label = yytext; return TK_REL; }
"=="            {yylval.label = yytext; return TK_REL; }
"!="            {yylval.label = yytext; return TK_REL; }

"&&"            {yylval.label = yytext; return TK_AND; }
"||"            {yylval.label = yytext; return TK_OR; }
"!"             {yylval.label = yytext; return TK_NOT; }



[a-zA-Z][a-zA-Z0-9_]* { yylval.label = yytext; return TK_ID;}
['][a-zA-Z]+['] {yylval.label = yytext; return TK_CHAR_VALUE; }

[0-9]+"."[0-9]+ { yylval.label = yytext; return TK_NUM_FLOAT; } 
{NUM}		    { yylval.label = yytext; return TK_NUM_INT; }

.			    { fprintf(stderr, "Caractere nao reconhecido na linha %d: %s\n", linha, yytext); }

%%
