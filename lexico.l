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

[+*/\-]			{ return *yytext; }
[()]            {return *yytext; } 
[=;]             {return *yytext; }
"int" { yylval.label = yytext; return TK_INT; }
"float" { yylval.label = yytext; return TK_FLOAT; }
"bool" { yylval.label = yytext; return TK_BOOL; }
"char" { yylval.label = yytext; return TK_CHAR; }
[a-zA-Z][a-zA-Z0-9_]* { yylval.label = yytext; return TK_ID; }


{NUM}		{ yylval.label = yytext; return TK_NUM; }

.			{ fprintf(stderr, "Caractere nao reconhecido na linha %d: %s\n", linha, yytext); }

%%
