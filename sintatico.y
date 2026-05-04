/*** Configuração do Bison C++***/
%skeleton "lalr1.cc"
%require "3.2"
%language "c++"	

/*** Configurações de Template/Construtor C++ ***/
%define api.value.type variant
%define api.token.constructor
%define parse.error verbose

%code requires {
    #include "tokens.hh"
}

%code{
	#include <iostream>
	#include <fstream>
	#include "tokens.hh"

	yy::parser::symbol_type yylex();
	using namespace std;

	/*** Variáveis globais  ***/
	int tmp_var_count = 0;
	string code;
	map<string,string> variables;
	map<string, shared_ptr<symbol>> symbols;

	/*** Variáveis externas ***/
	extern int yylineno;

	/*** Geradores de código  ***/
	string gen_tmp_variable();
	string gen_declarations(); 
	
	void gen_literal(node& n, const string& type, const string& literal);
	void materialize(node& n);
	
	node gen_unary(const string& side, const string& op, node& t);
	node gen_expr(node& l, const string& op, node& r);

	/*** Funções auxiliares: temporários***/
	shared_ptr<symbol> lookup_symbol(const string& name);
	const string lookup_variables(const string& label);
	
	/*** Funções auxiliares: conversão ***/
	bool is_numeric(const string& s);
	const string get_type(node& n);

	void check_conversion(const string& l, const string& r);
	node conversion(node& t, const string& type);
	void coercion(node& l, node& r);
	node casting(node& t, const string& type);

	/*** Funções auxiliares: inferência ***/
	void promote_symbol(node& n, const string& type);

	/*** Funções auxiliares: debug ***/
	void report_error(const string& msg);
	/*TODO: Lançar exceção para main capturar */
}

/*** Declaração de tokens ***/
%token <std::string> TK_INT TK_FLOAT TK_CHAR TK_BOOL TK_TYPE TK_VAR TK_CAST
%token <std::shared_ptr<symbol>> TK_ID

/*** Declaração de nódulos ***/
%type <node> COMMANDS STATEMENT DECLARATION ASSIGNMENT LVAL RVAL EXPR 
%start S

%right OP_AT
%left  OP_EQ OP_NE OP_LE OP_GE OP_LT OP_GT
%left  OP_OR
%left  OP_AND
%left  OP_ADD OP_MINUS
%left  OP_MULT OP_DIV
%left  OP_MOD
%right OP_NOT TK_CAST

%% 
			/*TODO: Alterar o nome do compilador - MAKEFILE e Casos de Teste */
S			: COMMANDS
			{
				code = "/*Compilador FOCA*/\n#include <stdio.h>\nint main(void) {\n";
				code += gen_declarations();
				code += "\n" + $1.translation;
				code += "\treturn 0;\n}\n";
			};


COMMANDS 	: COMMANDS STATEMENT {$$.translation = $1.translation + $2.translation;}
			| STATEMENT 		 {$$.translation = $1.translation;};

STATEMENT 	: DECLARATION {$$.translation = $1.translation;}
			| ASSIGNMENT  {$$.translation = $1.translation;}

			/* TODO: Criação de blocos pela identação ou marcador END e/ou identação*/
DECLARATION : TK_VAR TK_ID ';'
			{
				auto sym = lookup_symbol($2->name);
				if(sym){
						string msg = "Variável '" + sym->name + "' já declarada.";
						report_error(msg);
					}
				$2->type = "wildcard";
				$$.translation = "";

				auto [it, inserted] = symbols.try_emplace($2->name, $2);
			}
			| TK_VAR TK_ID ':' TK_TYPE ';'
			{
				auto sym = lookup_symbol($2->name);
				if(sym){
						string msg = "Variável '" + $2->name + "' já declarada.";
						report_error(msg);
					}
				//sym->is_dynamic = false;
				$2->type = $4;
				$$.translation = "";

				auto [it, inserted] = symbols.try_emplace($2->name, $2);
			};

ASSIGNMENT : LVAL OP_AT RVAL ';'
			{
				materialize($3);

				if(get_type($3) != "undefined"){
					promote_symbol($1,$3.type);
				} 
				else coercion($1,$3); 

				materialize($1);
				$$.translation = $3.translation + $1.translation;
				$$.translation += "\t" + $1.label + " = " + $3.label + ";\n";
			};
			/* TODO: Expansão para atribuição em sequência */
LVAL 		: TK_ID 
			{
				auto sym = lookup_symbol($1->name);
				if(!sym){
					string msg = "Identificador '" + $1->name + "' não declarado.";
					report_error(msg);
				}
				$$.type  = sym->type;
				$$.label = sym->name;
				$$.translation = "";
			};


RVAL 		: EXPR {$$ = $1;};

	
			/*** Operadores numéricos ***/
EXPR 		: EXPR OP_ADD  	EXPR {$$ = gen_expr($1,"+",$3);}
			| EXPR OP_MINUS EXPR {$$ = gen_expr($1,"-",$3);}
			| EXPR OP_MULT 	EXPR {$$ = gen_expr($1,"*",$3);}
			| EXPR OP_DIV 	EXPR {$$ = gen_expr($1,"/",$3);}
			| EXPR OP_MOD 	EXPR {$$ = gen_expr($1,"%",$3);}

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
			| OP_NOT EXPR  {$$ = gen_unary("left","!",$2);}
			| TK_CAST EXPR {$$ = casting($2,$1);}
			
			| '(' EXPR ')' {$$ = $2;}

			| TK_INT   	{gen_literal($$,"int",$1);}
			| TK_FLOAT 	{gen_literal($$,"float",$1);}
			| TK_CHAR	{gen_literal($$,"char",$1);}
			| TK_BOOL	{gen_literal($$,"int", $1);}
			| TK_ID 
			{
				auto sym = lookup_symbol($1->name);
				if (!sym){
					string msg = "Identificador '" + $1->name + "' não declarado.";
					report_error(msg);
				}
				$$.label = sym->name;
				$$.type  = sym->type;
				$$.translation = "";
			};
%%

void gen_literal(node& n, const string& type, const string& literal){
	n.label = literal;
	n.type = type;
	n.translation = "";
}

void materialize(node& n){
    if(!n.is_materialized){
		/* Verifica se é um identificador pela tabela de símbolos */
		auto sym = lookup_symbol(n.label);
		if(sym){
			/* Reutiliza um temporário previamente registrado  */
			if(!sym->label.empty()) n.label = sym->label;
		
			/* Gera um temporário novo para um identificador */
			else{
				string label = gen_tmp_variable();
				sym->label = label;

				variables[label] = n.type;
				n.label = label;
			}
		}
		/* Verifica se é um literal pela ausência de tradução */
		else if(n.translation.empty()){
			string label = gen_tmp_variable();
			n.translation += "\t" + label + " = " + n.label + ";\n";

			n.label = label;
			variables[n.label] = n.type;
		}
		n.is_materialized = true;
	}
}



/*** GERADORES DE CÓDIGO INTERMEDIÁRIO ***/

/* Gerador de rótulos temporários */
string gen_tmp_variable(){
	tmp_var_count++;
	return "t" + to_string(tmp_var_count);
}

/* Gerador de declarações de temporários */
string gen_declarations(){
	string decl;
    for(const auto& [var, type] : variables){
       	 	decl += "\t" + type + " " + var + ";\n";
		}
    return decl;
}

/* Gerador de expressões binárias */
node gen_expr(node& l, const string& op, node& r)
{
    materialize(l);
    materialize(r);

    coercion(l,r); 

    node n;
    n.type = get_type(l);
    materialize(n);

    n.translation = l.translation + r.translation;
    n.translation += "\t" + n.label + " = " + l.label + " " + op + " " + r.label + ";\n";
    return n;
}

/* Gerador de expressões unárias */
node gen_unary(const string& side, const string& op, node& t){
	
	/* Criação de temporário para o nó */
	materialize(t);

	string tt = get_type(t);

	/* TODO: Regras de conversão por tipo de operação */
	check_conversion(tt, t.type);
	conversion(t, tt);

    node n;
	n.type = get_type(t);
	materialize(n);
    
    n.translation = t.translation;
	/* TODO: Trocar por comparação de enum */
	/* Operação unária à esquerda */
    if(side == "left"){
		n.translation += "\t" + n.label + " = " + op + t.label + ";\n";
	}
	/* Operação unária à direita */
	else if(side == "right"){
		n.translation += "\t" + n.label + " = " +  t.label + op  + ";\n";
	}
    return n;
}




/*** CONVERSÃO: IMPLÍCITA E EXPLÍCITA ***/

/* Conversões numéricas perimitidas: (int) e (float) */
bool is_numeric(const string& s){
	return s == "int" || s == "float";
}

/* Validação da conversão */
void check_conversion(const string& l, const string& r){

	/*TODO: Aceitar outros tipos de conversão */
	if(!is_numeric(l) || !is_numeric(r)){
		report_error("Conversão não permitida entre tipos ("+ l +") e ("+ r +")");
	}
	if(l == "undefined" || r == "undefined"){
        report_error("Uso de variável não inicializada na expressão.");
	}
}

/* Função de conversão explícita */
node casting(node& t, const string& type) {
    
	materialize(t);
    string tt = get_type(t);
    
    if (tt == type) return t; 
    check_conversion(tt, type);

    return conversion(t, type);
}

/* Função auxiliar para conversão */
node conversion(node& t, const string& type) {
   
    node n;
    n.type = type;
    materialize(n);

    n.translation = t.translation;
    n.translation += "\t" + n.label + " = (" + type + ") " + t.label + ";\n";
    
    return n;
}

/* Função de conversão implícita */
void coercion(node& l, node& r) {
    string lt = get_type(l);
    string rt = get_type(r);

    check_conversion(lt, rt);

    if (lt == "float" && rt == "int"){
        r = conversion(r, "float");
    } 
    else if (lt == "int" && rt == "float"){
        l = conversion(l, "float");
    }
}


/*** INFERÊNCIA DE TIPAGEM ***/

/* Modificação do tipo e atualização do mapa de variáveis */
void promote_symbol(node& n, const string& type){
	/* Verifica se é um identificador pela tabela de símbolos */
	auto sym = lookup_symbol(n.label);

	/* Promove o tipo do indetificador */
	if(sym && sym->type == "wildcard"){
		string label = gen_tmp_variable();
		sym->label = label;

		variables[label] = type;
		n.label = label;
		n.type = type;
		n.is_materialized = true;
	}
}

const string get_type(node& n){
    if(n.type != "wildcard") return n.type;
    
    auto sym = lookup_symbol(n.label);
    if(sym && !sym->label.empty()){
        return variables[sym->label];
    }

	auto var = lookup_variables(n.label);
	if(!var.empty()){
		return var;
	}
    return "undefined";
}

shared_ptr<symbol> lookup_symbol(const string& name){
	auto it = symbols.find(name);
	
	if (it != symbols.end()) return it->second; 
	else return nullptr;
}

const string lookup_variables(const string& label){
	auto it = variables.find(label);
	
	if (it != variables.end()) return it->second; 
	else return {};
}

/*** MAIN ***/

int main(int argc, char* argv[]){
    tmp_var_count = 0;
    yy::parser p;
    
    if (p.parse() == 0){ 
        cout << code;
        
        ofstream outFile("code.c");
        if(outFile.is_open()) outFile << code << endl;
        
		/* TODO: Organizar a escrita na tabela de símbolos */
        ofstream ofile("symbol_table.txt");
        if(ofile.is_open()) {
            for(const auto& [key, sym] : symbols) {
                ofile << sym->type << " | " << sym->name << " | " << sym->label << endl;
            }
        }
    }
    return 0;
}

void yy::parser::error(const std::string& s){
    std::cerr << "ERRO: linha (" << yylineno << "): " << s << std::endl;
}

/*TODO: Trocar essa função, capturando erros pelo yy::parser::error */
void report_error(const string& msg){
	std::cerr << "ERRO: Linha [" << yylineno << "]: " << msg << std::endl;
	exit(1);
}