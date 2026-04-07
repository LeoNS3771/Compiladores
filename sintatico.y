%{
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#define YYSTYPE atributos

using namespace std;

int var_temp_qnt;
int linha = 1;
string codigo_gerado;

struct atributos
{
	string label;
	string traducao;
};

struct simbolo
{
	string nome;
	//string tipo;
};

unordered_map<string, simbolo> tabelaSimbolos;

int yylex(void);
void yyerror(string);
string gentempcode();
string getVar(string);
%}

%token TK_NUM TK_ID

%start S


%left '+''-'
%left '*''/'

%%

S 			: E
			{
				codigo_gerado = "/*Compilador FOCA*/\n"
								"#include <stdio.h>\n"
								"int main(void) {\n";

				for(int i = 1; i<var_temp_qnt+1; i++){
					codigo_gerado += "\tint t" + to_string(i) + ";\n";
				}
				codigo_gerado += "\n";

				codigo_gerado += $1.traducao;

				codigo_gerado += "\treturn 0;"
							"\n}\n";
			}
			;
			
E			: '(' E ')'
			{
				$$ = $2;
			}

			| E '+' E
			{
				$$.label = gentempcode();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label +
					" = " + $1.label + " + " + $3.label + ";\n";
			}
			

			| E '-' E
			{
				$$.label = gentempcode();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label +
					" = " + $1.label + " - " + $3.label + ";\n";
			}
			

			| E '*' E
			{
				$$.label = gentempcode();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label +
					" = " + $1.label + " * " + $3.label + ";\n";
			}
			

 			| E '/' E
			{
				$$.label = gentempcode();
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label +
					" = " + $1.label + " / " + $3.label + ";\n";
			}

			| TK_NUM
			{
				$$.label = gentempcode();
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
			}

			| TK_ID
			{	
				string nome = gentempcode();

				$$.label = nome;
				$$.traducao = "\t" + nome + " = " + $1.label + ";\n";

				tabelaSimbolos[$1.label] = {nome};
			}

			| TK_ID '=' E
			{
				$$.label = $1.label;
				$$.traducao = $3.traducao + "\t" + $$.label + " = " + $3.label + ";\n";
			}
			;

%%

#include "lex.yy.c"

int yyparse();

string gentempcode()
{
	var_temp_qnt++;
	return "t" + to_string(var_temp_qnt);
}

string getVar(string var){
	if(tabelaSimbolos.find(var) != tabelaSimbolos.end()){
		return tabelaSimbolos[var].nome;
	}
	else cout << "tem nada na tabela n chefe :/\n";
}

int main(int argc, char* argv[])
{
	var_temp_qnt = 0;

	if (yyparse() == 0)
		cout << codigo_gerado;

	return 0;
}

void yyerror(string MSG)
{
	cerr << "Erro na linha " << linha << ": " << MSG << endl;
}
