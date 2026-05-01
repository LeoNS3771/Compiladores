/*** Configuração do Bison C++***/
%skeleton "lalr1.cc"
%require "3.2"
%language "c++"	

%define api.value.type variant
%define api.token.constructor

%code requires{
	#include <string>
    #include "tokens.hh"
	#include "runtime.hh"
}

%code{
    #include "y.tab.hh"
	yy::parser::symbol_type yylex();
}

%{
#include "tokens.hh"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "runtime.hh"
using namespace std;

/*** Variáveis globais  ***/
int tmp_var_count;
string code;
vector<symbol> symbols;	//Tabela de símbolos
vector<string> variables;	//Variáveis temporárias

/*** Variáveis externas ***/
extern int yylineno;

/*** Geradores de código  ***/
string gen_tmp_variable();
string gen_declarations(); 

/*** Funções auxiliares ***/
symbol* search_symbol(string label);
node gen_expr(const node& l, string op, const node& r);
string what_type(const node& l, const node&r); // Função que retorna o tipo de uma operação.
%}

/*** Declaração de tokens ***/
%token <literal> TK_INT TK_FLOAT TK_TYPE TK_CHAR TK_BOOL
%token <symbol> TK_ID
%token TK_VAR
%token OP_EQ OP_NE OP_LE OP_GE OP_LT OP_GT
%token OP_AND OP_OR OP_NOT OP_AT

/*** Declaração de nódulos ***/
%type <node> COMMANDS STATEMENT DECL ATRI EXPR
%start S

%right OP_AT
%left  OP_EQ OP_NE OP_LE OP_GE OP_LT OP_GT
%left  OP_OR
%left  OP_AND
%left  '+' '-'
%left  '*' '/' '%'
%right OP_NOT

%%

S			: COMMANDS
			{
				code = "/*Compilador FOCA*/\n#include <stdio.h>\n#include \"runtime.h\"\nint main(void) {\n";
				code += gen_declarations();
				code += "\n" + $1.translation;
				code += "\treturn 0;\n}\n";
			};


COMMANDS 	: COMMANDS STATEMENT {$$.translation = $1.translation + $2.translation;}
			| STATEMENT 		 {$$.translation = $1.translation;};

STATEMENT 	: DECL {$$.translation = $1.translation;}
			| ATRI {$$.translation = $1.translation;}
			| EXPR {$$.translation = $1.translation;};
			
DECL		: TK_VAR TK_ID ';' 
			{
				symbol sym;
				sym.name = $2.label;
				sym.type = ""; // Sem tipo na declaração
				symbols.push_back(sym);  
				$$.translation = "";
			};

ATRI 		: TK_ID OP_AT EXPR ';'
			{
				symbol* sym = search_symbol($1.label);
				if(sym){
					$$.label = sym->label;
					sym->type = $3.type ;
					$$.translation = $3.translation;
				}
			};
			
			/*** Operadores numéricos ***/
			// Precisa fazer a verificação de tipo e conversão de tipo. Melhor lugar é na função gen_expr
EXPR 		: EXPR '+' EXPR {$$ = gen_expr($1,"+",$3);}
			| EXPR '-' EXPR {$$ = gen_expr($1,"-",$3);}
			| EXPR '*' EXPR {$$ = gen_expr($1,"*",$3);}
			| EXPR '/' EXPR {$$ = gen_expr($1,"/",$3);}
			| EXPR '%' EXPR {$$ = gen_expr($1,"%",$3);}

			/*** Operadores relacionais ***/
			| EXPR OP_EQ EXPR {$$ = gen_expr($1,"==",$3);}
			| EXPR OP_NE EXPR {$$ = gen_expr($1,"!=",$3);}
			| EXPR OP_LE EXPR {$$ = gen_expr($1,"<=",$3);}
			| EXPR OP_GE EXPR {$$ = gen_expr($1,">=",$3);}
			| EXPR OP_LT EXPR {$$ = gen_expr($1,"<",$3);}
			| EXPR OP_GT EXPR {$$ = gen_expr($1,">",$3);}

			/*** Operadores lógicos ***/
			| EXPR OP_OR  EXPR {$$ = gen_expr($1,"||",$3);}
			| EXPR OP_AND EXPR {$$ = gen_expr($1,"&&",$3);}
			| OP_NOT EXPR 	   
			{
				$$.label = gen_tmp_variable();
				variables.push_back($$.label);
				$$.translation = $2.translation + "\t" + 
				$$.label + " = " + "not(" + $2.label + ")" + ";\n";
				$$.type = $2.type;
			}

			| '(' EXPR ')' {$$ = $2;}

			
			| TK_INT 
			{
				$$.label = gen_tmp_variable();
				$$.type = "int";
				variables.push_back($$.label);
				$$.translation = "\t" + $$.label + " = make_int(" + $1.label + ");\n";
			}

			| TK_FLOAT 
			{
				$$.label = gen_tmp_variable();
				$$.type = "float";
				variables.push_back($$.label);
				$$.translation = "\t" + $$.label + " = make_float(" + $1.label + ");\n";
			}

			| TK_CHAR
			{ 	
				$$.label = $1.label;
				$$.type = "char";
				$$.translation = "\t" + $$.label + " = make_char(" + $1.label + ");\n";
			}

			| TK_BOOL
			{
				$$.label = $1.label;
				$$.type = "int";
				$$.translation = "\t" + $$.label + " = make_bool(" + $1.label + ");\n";
			}

			| TK_ID 
			{
				symbol *sym = search_symbol($1.label);
				$$.label = sym->label;
				$$.type = sym->type;
				$$.translation = "";
			};

%%

void yy::parser::error(const std::string& s){
    std::cerr << "Erro na linha " << yylineno << ": " << s << std::endl;
}

string gen_tmp_variable()
{
	tmp_var_count++;
	return "t" + to_string(tmp_var_count);
}

string gen_declarations(){
	string res;
    for(const auto& var : variables)
        res += std::string("\t") + "Value " + var + ";\n";
    return res;
}

node gen_expr(const node& l, string op, const node& r){
    node v;
    v.label = gen_tmp_variable(); 
    variables.push_back(v.label);
	string func; // Qual a função que vai ser usada
	if(op == "+") func = "add";
	else if(op == "-") func = "sub";
	else if(op == "*") func = "mul";
	else if(op == "/") func = "div";
	else if(op == "/") func = "mod";

	else if(op == "==") func = "equal";
	else if(op == "!=") func = "nequal";
	else if(op == "<=") func = "lequal";
	else if(op == ">=") func = "gequal";
	else if(op == "<") func = "less";
	else if(op == ">") func = "great";

	else if(op == "||") func = "or";
	else if(op == "&&") func = "and";

    v.translation = l.translation + r.translation + "\t" + 
                    v.label + " = " + func + "(" + l.label + "," + r.label + ")" + ";\n";
	v.type = what_type(l,r);
    return v;
}
string what_type(const node& l, const node&r){
	// Se um dos operandos for float, novo nó é float
	if(l.type == "float" || l.type == "float") return "float";
	else return "int";
}	
// Procurar a variavel na tabela
symbol* search_symbol(string label){
	for(symbol& sym : symbols){ 
		if(sym.name == label){
			if(sym.label.empty()){
				sym.label = gen_tmp_variable(); 
				variables.push_back(sym.label);
			}
			return &sym;
		}
	}	
	return nullptr; 
}

int main(int argc, char* argv[]){
    tmp_var_count = 0;
    yy::parser p;
    
    if (p.parse() == 0){ 
        cout << code;
        
        ofstream outFile("code.c");
        if(outFile.is_open()) outFile << code << endl;
        
        ofstream ofile("tabela_de_simbolos.txt");
        if(ofile.is_open()) {
            for(const auto& sym : symbols) {
                ofile << sym.type << " | " << sym.name << " | " << sym.label << endl;
            }
        }
    }
    return 0;
}