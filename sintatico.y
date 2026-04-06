%{
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define YYSTYPE atributos

using namespace std;

//
int var_temp_qnt;
int linha = 1;
string codigo_gerado;
vector<string> variables; // Vetor que guarda os nomes das variaveis temporarias criadas

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

vector<simbolo> simbolos; // Vetor que guarda as variaveis(não temporarias) criadas


int yylex(void);
void yyerror(string);
string gentempcode();
string genVar();
%}

// Token 
%token TK_NUM TK_ID TK_INT TK_FLOAT TK_BOOL TK_CHAR

//
%start S

%left '+'

%left '*'


%%



S 			: COMANDOS
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

COMANDOS	: COMANDOS E 
			{
				$$.traducao = $1.traducao + $2.traducao;

			}
			
			| COMANDOS DECL 
			{
				$$.traducao = $1.traducao + $2.traducao;
				
			}

			| E 
			{
				$$.traducao = $1.traducao;
			
			}
			
			| DECL
			{
				$$.traducao = $1.traducao;
			}
			;

DECL		: TK_INT TK_ID ';' // Definição de variaveis inteira
			{
				simbolo sim;
				sim.nome = $2.label;
				sim.tipo = $1.label;
				sim.label = gentempcode();
				simbolos.push_back(sim);
				variables.push_back(sim.label);
				$$.traducao = "";
			}
			
			| TK_FLOAT TK_ID ';'
			{
				simbolo sim;
				sim.nome = $2.label;
				sim.tipo = $1.label;
				sim.label = gentempcode();
				simbolos.push_back(sim);
				variables.push_back(sim.label);
				$$.traducao = "";

			}
			
			| TK_CHAR TK_ID ';'
			{
				simbolo sim;
				sim.nome = $2.label;
				sim.tipo = $1.label;
				sim.label = gentempcode();
				simbolos.push_back(sim);
				variables.push_back(sim.label);
				$$.traducao = "";
			}

			| TK_BOOL TK_ID ';'
			{
				simbolo sim;
				sim.nome = $2.label;
				sim.tipo = $1.label;
				sim.label = gentempcode();
				simbolos.push_back(sim);
				variables.push_back(sim.label);
				$$.traducao = "";
			}
			;

E 			: E '+' E
			{
				$$.label = gentempcode();
				variables.push_back($$.label);
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label +
					" = " + $1.label + " + " + $3.label + ";\n";
			}
			
			| E '*' E
			{
				$$.label = gentempcode();
				variables.push_back($$.label);
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
				variables.push_back($$.label);
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
			}

			| TK_ID 
			{

				for( simbolo sim : simbolos ){ // Procurar variavel na tabela
					if(sim.nome == $1.label){
						$$.label = sim.label;
						$$.traducao = "";
					}

				}
				
			}
			
			| TK_ID '=' E
			{
				
				for( simbolo sim : simbolos ){ // Procurar a variavel na tabela
					if(sim.nome == $1.label){
						$$.label = sim.label;
						$$.traducao = $3.traducao + "\t" + sim.label + " = " + $3.label + ";\n";

					}

				}				

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
	for(int i = 0; i < simbolos.size(); i++)
		resultado += "\t" + simbolos[i].tipo +" " + simbolos[i].label + ";\n";
	
	return resultado;
}

int main(int argc, char* argv[])
{
	ofstream outFile("codigo_gerado.c");
	ofstream ofile("tabela de simbolos.txt");
	var_temp_qnt = 0;

	if (yyparse() == 0)
		cout << codigo_gerado;

	for(simbolo sim : simbolos){
		if(ofile.is_open())
			ofile << sim.tipo + " | " + sim.nome + " | "  + sim.label << endl;
	}
	
	if(outFile.is_open())
		outFile << codigo_gerado << endl;

	outFile.close();
	return 0;
}

void yyerror(string MSG)
{
	cerr << "Erro na linha " << linha << ": " << MSG << endl;
}
