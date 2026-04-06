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

[+*-/]			{ return *yytext; }
[()]            {return *yytext; } 
[=]             {return *yytext; }
[a-zA-Z][a-zA-Z0-9_]* { yylval.label = yytext; return TK_ID; }

{NUM}		{ yylval.label = yytext; return TK_NUM; }

.			{ fprintf(stderr, "Caractere nao reconhecido na linha %d: %s\n", linha, yytext); }

%%
