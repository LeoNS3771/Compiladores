%{
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define YYSTYPE atributos

using namespace std;

int var_temp_qnt;
int linha = 1;
string codigo_gerado;
vector<string> varCode;

struct atributos
{
	string label;
	string traducao;
};

struct simbolo {
	string nome;
	string tipo;
	string label;
};

vector<simbolo> simbolos;


int yylex(void);
void yyerror(string);
string gentempcode();
string genVar();
%}

%token TK_NUM TK_ID

%start S

%left '+'

%left '*'


%%

S 			: E
			{
				codigo_gerado = "/*Compilador FOCA*/\n"
								"#include <stdio.h>\n"
								"int main(void) {\n";
				codigo_gerado += genVar();
				codigo_gerado += "\n"; 
				codigo_gerado += $1.traducao;

				codigo_gerado += "\treturn 0;"
							"\n}\n";
			}
			;

E 			: E '+' E
			{
				$$.label = gentempcode();
				varCode.push_back($$.label);
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label +
					" = " + $1.label + " + " + $3.label + ";\n";
			}
			
			| E '*' E
			{
				$$.label = gentempcode();
				varCode.push_back($$.label);
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
				" = " + $1.label + " * " + $3.label + ";\n";
			}
			
			| '('E')'
			{
				$$ = $2; // O valor semantico é o mesmo do $2 (nó de dentro)
			}
			

			| TK_NUM
			{
				$$.label = gentempcode();
				varCode.push_back($$.label);
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
			}

			| TK_ID 
			{
				simbolo sim;
				sim.nome = $1.label;
				sim.tipo = "int";
				sim.label = gentempcode(); 
				varCode.push_back(sim.label);
				
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
			}
			
			| TK_ID '=' E
			{
				$$.label = $1.label;
				simbolo sim = {$1.label, $3.traducao};
				simbolos.push_back(sim);

				$$.traducao = $3.traducao + "\t" + $1.label + " = " + $3.label + ";\n";
				cout << $$.traducao << " Aquiiii!!! " << endl;
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

string genVar(){
	string resultado;
	for(int i = 0; i < varCode.size(); i++)
		resultado += "\tint " + varCode[i] + ";\n";
	return resultado;
}

int main(int argc, char* argv[])
{
	ofstream outFile("codigo_gerado.c");
	var_temp_qnt = 0;

	if (yyparse() == 0)
		cout << codigo_gerado;
	if(outFile.is_open())
		outFile << codigo_gerado << endl;
	outFile.close();
	return 0;
}

void yyerror(string MSG)
{
	cerr << "Erro na linha " << linha << ": " << MSG << endl;
}
