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
vector<pair<string, string>> variables; // Vetor que guarda os nomes das variaveis temporarias criadas

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
simbolo* searchSymbol(string label);
				
%}

// Token 
%token TK_TYPE TK_NUM_INT TK_NUM_FLOAT TK_ID TK_CHAR_VALUE TK_BOOL_VALUE TK_REL TK_AND TK_OR TK_NOT

//
%start S

%left TK_OR
%left TK_AND
%right TK_NOT // operador unario
%left TK_REL
%left '+' '-'
%left '*' '/'


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

DECL		: TK_TYPE TK_ID ';' // Definição de variaveis inteira
			{
				simbolo sim;
				sim.nome = $2.label;
				sim.tipo = $1.label;
				//sim.label = gentempcode();
				simbolos.push_back(sim);  
				$$.traducao = "";
			}

	// OPERAÇÕES INTEIROS
E 			: E '+' E
			{
				$$.label = gentempcode();
				variables.push_back({$$.label, "int"});
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label +
					" = " + $1.label + " + " + $3.label + ";\n";
			}
			
			| E '-' E
			{
				$$.label = gentempcode();
				variables.push_back({$$.label, "int"});
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
				" = " + $1.label + " - " + $3.label + ";\n";
			}
			
			| E '*' E
			{
				$$.label = gentempcode();
				variables.push_back({$$.label, "int"});
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
				" = " + $1.label + " * " + $3.label + ";\n";
			}
			
			| E '/' E
			{
				$$.label = gentempcode();
				variables.push_back({$$.label, "int"});
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
				" = " + $1.label + " / " + $3.label + ";\n";
			}
			

			
			| '('E')'
			{
				$$ = $2; // O valor semantico é o mesmo do $2 (nó de dentro)
			}
			

			| TK_NUM_INT
			{
				$$.label = gentempcode();
				variables.push_back({$$.label, "int"});
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
			}
	// FLOAT
			| TK_NUM_FLOAT
			{
				$$.label = gentempcode();
				variables.push_back({$$.label, "float"});
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
			}
			| TK_ID 
			{

				simbolo *sim = searchSymbol($1.label);
				$$.label = sim->label;
				$$.traducao = "";
				
			}

			| TK_ID '=' E // <---------------- FORMA GENÉRICA DE ATRIBUÇÃO
			{
				// Procurar variavel nos simbolos
				simbolo* sim = searchSymbol($1.label);
				if(sim){
					$$.label = sim->label;
					$$.traducao = $3.traducao + "\t" + sim->label + " = " + $3.label + ";\n";
				}
			}

			| TK_ID '=' TK_CHAR_VALUE ';'
			{
				simbolo* sim = searchSymbol($1.label);
				if(sim){
					$$.label = sim->label;
					$$.traducao = "\t" + sim->label + " = " + $3.label + ";\n";
				}
			}

			| TK_ID '=' TK_BOOL_VALUE ';'
			{
				simbolo* sim = searchSymbol($1.label);
				if(sim){
					$$.label = sim->label;
					$$.traducao = "\t" + sim->label + " = " + $3.label + ";\n";
				}
			}
			
	// OPERADORES RELACIONAIS EM TODOS OS TIPOS???
			| E TK_REL E 
			{
				$$.label = gentempcode();
				variables.push_back({$$.label, "int"});
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
				" = " + $1.label + " " + $2.label + " " + $3.label + ";\n";

			}
			
	// OPERADORES LÓGICOS
			| E TK_OR E
			{
				$$.label = gentempcode();
				variables.push_back({$$.label, "int"});
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
				" = " + $1.label + " " + $2.label + " " + $3.label + ";\n";

			}
			
			| E TK_AND E
			{
				$$.label = gentempcode();
				variables.push_back({$$.label, "int"});
				$$.traducao = $1.traducao + $3.traducao + "\t" + $$.label + 
				" = " + $1.label + " " + $2.label + " " + $3.label + ";\n";

			}

			| TK_NOT E
			{
				$$.label = gentempcode();
				variables.push_back({$$.label, "int"});
				$$.traducao = $2.traducao + "\t" + $$.label + " = " + $1.label + $2.label + ";\n";
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
	for(auto var : variables){
		resultado += "\t" + var.second + " " + var.first + ";\n";
	}

	return resultado;
}

simbolo* searchSymbol(string label){

	for( simbolo& sim : simbolos ){ // Procurar a variavel na tabela
		if(sim.nome == label){
			if(sim.label.empty()){
				sim.label = gentempcode(); // Se nao tiver label alocada, aloca
				variables.push_back({sim.label, sim.tipo});
			}
			return &sim;
		}
	}	
	return nullptr; // Não tem 
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
