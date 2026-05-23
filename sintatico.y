////*** Configuração do Bison C++***////
%skeleton "lalr1.cc"
%require "3.2"
%language "c++"	

////*** Configurações de Template/Construtor C++ ***////
%define api.value.type variant
%define api.token.constructor
%define parse.error verbose

%code requires{
    #include "tokens.hh"
}

%code{
	#include <iostream>
	#include <fstream>
	#include "tokens.hh"
	using namespace std;

	yy::parser::symbol_type yylex();
	
	////*** Variáveis globais  ***////
	int tmp_var_count = 0;
	string code;
	
	vector<pair<string,string>> variables;
	vector<map<string,shared_ptr<symbol>>> scope_stack;

	////*** Variáveis externas ***////
	extern int yylineno;

	////*** Geradores de código  ***////
	string gen_tmp_variable();
	string gen_declarations(); 
	
	void gen_literal(node& n, const string& type, const string& literal);
	void materialize(node& n);
	
	node gen_unary(const string& side, const op& op, node& t);
	node gen_expr(node& l, const op& op, node& r);

	////*** Funções auxiliares: temporários***////
	shared_ptr<symbol> lookup_symbol(const string& name);
	
	// Funções responsaveis pelo escopo //
	void open_block();
	void close_block();
	void register_symbol(const string& name, shared_ptr<symbol> sym);
	
	////*** Funções auxiliares: conversão ***////
	bool is_numeric(const string& s);
	void check_conversion(const string& l, const string& r);
	node conversion(node& t, const string& type);
	void coercion(node& l, node& r);
	node casting(node& t, const string& type);

	////*** Funções auxiliares: inferência ***////
	void promote_symbol(node& n, const string& type);

	////*** Funções auxiliares: debug ***////
	void report_error(const string& msg);
	////*TODO: Lançar exceção para main capturar *////
}

/*** Declaração de tokens ***/
%token <std::string> TK_INT TK_FLOAT TK_CHAR TK_BOOL TK_TYPE TK_VAR TK_CAST TK_SBLOCK TK_EBLOCK
%token <std::shared_ptr<symbol>> TK_ID
%token <op> OP_ADD OP_MINUS OP_MULT OP_DIV OP_MOD
%token <op> OP_EQ OP_NE OP_LE OP_GE OP_LT OP_GT
%token <op> OP_OR OP_AND OP_NOT

/*** Declaração de nódulos ***/
%type <node> COMMANDS STATEMENT DECLARATION ASSIGNMENT LVAL RVAL EXPR BLOCK
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
				code = "/*Compilador*/\n#include <stdio.h>\nint main(void) {\n";
				code += gen_declarations();
				code += "\n" + $1.translation;
				code += "\treturn 0;\n}\n";
			};

COMMANDS 	: COMMANDS STATEMENT {$$.translation = $1.translation + $2.translation;}
			| STATEMENT 		 {$$.translation = $1.translation;};

STATEMENT 	: DECLARATION 	{$$.translation = $1.translation;}
			| ASSIGNMENT  	{$$.translation = $1.translation;}
			| BLOCK			{$$.translation = $1.translation;}
	
DECLARATION : TK_VAR TK_ID ';'
			{

				$2->type = "undefined";
				$2->is_static = false;
				$$.translation = "";

				register_symbol($2->name, $2);
			}
			| TK_VAR TK_ID ':' TK_TYPE ';'
			{
				$2->type = $4;
				$2->is_static = true;
				$$.translation = "";
				register_symbol($2->name, $2);($2->name, $2);
			};

ASSIGNMENT : LVAL OP_AT RVAL ';'
			{
				
				// Se for estático não pode receber um tipo diferente do definido
				if($1.is_static) {
					if($3.type != $1.type){
						report_error("Variavel '" + $1.label + "' do tipo estatico'" + $1.type + "' recebendo outro tipo '" + $3.type + "'"); // Colocar uma mensagem condizente
					}
				}

				materialize($3);
				promote_symbol($1,$3.type);
				materialize($1);

				//coercion($1,$3); 
				$$.translation = $3.translation + $1.translation;
				$$.translation += "\t" + $1.label + " = " + $3.label + ";\n";
			}
			
			| TK_VAR TK_ID OP_AT RVAL ';'
			{

				materialize($4);
				// Materializando manualmente
				$2->is_static = false;
				$2->type = $4.type;
				$2->label = gen_tmp_variable();
				variables.push_back({$2->label, $2->type});

				register_symbol($2->name, $2);
				$$.translation = $$.translation + $4.translation;
				$$.translation += '\t' + $2->label + " = " + $4.label + ";\n";

			}

			| TK_VAR TK_ID ':' TK_TYPE OP_AT  RVAL ';'
			{
				
				materialize($6);
				if($4 != $6.type)
				 	report_error("Variável '" + $2->name + "' do tipo '" + $4 + "' recebendo " + "tipo '" + $6.type + "'");

				$2->is_static = true;
				$2->type = $4;
				$2->label = gen_tmp_variable();
				variables.push_back({$2->label, $2->type});

				register_symbol($2->name, $2);
				$$.translation = $$.translation + $6.translation;
				$$.translation += '\t' + $2->label + " = " + $6.label + ";\n";

			}
			;

BLOCK : 	TK_SBLOCK { open_block(); } COMMANDS TK_EBLOCK
			{
				close_block();

				$$.translation = $3.translation;
			}

			// Escopo vazio
			| TK_SBLOCK{open_block();} TK_EBLOCK
			{
				close_block();
				$$.translation = "";
			}

			;
			
			/* TODO: Expansão para atribuição em sequência */
LVAL 		: TK_ID 
			{
				auto sym = lookup_symbol($1->name);
				if(!sym){
					report_error("Variável '" + $1->name + "' não declarada.");
				}
				$$.type  = sym->type;
				$$.label = sym->name;
				$$.is_static = sym->is_static;
				$$.translation = "";
			};


RVAL 		: EXPR {$$ = $1;};

	
			/*** Operadores numéricos ***/
EXPR 		: EXPR OP_ADD  	EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_MINUS EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_MULT 	EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_DIV 	EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_MOD 	EXPR {$$ = gen_expr($1,$2,$3);}

			/*** Operadores relacionais ***/
			| EXPR OP_EQ EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_NE EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_LE EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_GE EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_LT EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_GT EXPR {$$ = gen_expr($1,$2,$3);}

			/*** Operadores lógicos ***/
			| EXPR OP_OR  EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_AND EXPR {$$ = gen_expr($1,$2,$3);}
			| OP_NOT EXPR  {$$ = gen_unary("left",$1,$2);}
			| TK_CAST EXPR {$$ = casting($2,$1);}
			
			| '(' EXPR ')' {$$ = $2;}

			| TK_INT   	{gen_literal($$,"int",$1);}
			| TK_FLOAT 	{gen_literal($$,"float",$1);}
			| TK_CHAR	{gen_literal($$,"char",$1);}
			| TK_BOOL	{gen_literal($$,"bool", $1);}
			| TK_ID 
			{
				auto sym = lookup_symbol($1->name);
				if (!sym){
					report_error("Variável '" + $1->name + "' não declarada.");
				}
				$$.label = sym->name;
				$$.type  = sym->type;
				$$.is_static = sym->is_static;
				$$.translation = "";
			};
%%

void gen_literal(node& n, const string& type, const string& literal){
	n.label = literal;
	n.type = type;
	n.translation = "";
}


////*** GERADOR DE VARIÁVEIS TEMPORÁRIAS ***////

void materialize(node& n){
    if(!n.is_materialized){
		/* Verifica se é um identificador pela tabela de símbolos */
		auto sym = lookup_symbol(n.label);
		if(sym){
			/* Verifica se a variável com tipo dinâmico foi inferida */
			if(sym->type == "undefined"){
            report_error("Variável '" + sym->name + "' usada sem ser inicializada.");
        	}
			/* Reutiliza um temporário previamente registrado  */
			if(!sym->label.empty()) n.label = sym->label;
			/* Gera um temporário novo para um identificador */
			else{
				string label = gen_tmp_variable();
				sym->label = label;

				n.label = label;
				variables.push_back({label,n.type});
			}
		}
		/* Verifica se é um literal pela ausência de tradução */
		else if(n.translation.empty()){
			string label = gen_tmp_variable();
			n.translation += "\t" + label + " = " + n.label + ";\n";

			n.label = label;
			variables.push_back({label,n.type});
		}
		n.is_materialized = true;
	}
}



////*** GERADORES DE CÓDIGO INTERMEDIÁRIO ***////

/* Gerador de rótulos temporários */
string gen_tmp_variable(){
	tmp_var_count++;
	return "t" + to_string(tmp_var_count);
}

/* Gerador de declarações de temporários */
string gen_declarations(){
    string decl;
    for(const auto& var : variables)
        decl += "\t" + var.second + " " + var.first + ";\n";
    return decl;
}

/* Gerador de expressões binárias */
node gen_expr(node& l, const op& op, node& r){
    materialize(l);
    materialize(r);
	
    coercion(l,r); 

    node n;
    n.type = l.type;
    materialize(n);

    n.translation = l.translation + r.translation;
    n.translation += "\t" + n.label + " = " + l.label + " " + op.label + " " + r.label + ";\n";
    return n;
}

/* Gerador de expressões unárias */
node gen_unary(const string& side, const op& op, node& t){
	
	/* Criação de temporário para o nó */
	materialize(t);

	/* TODO: Regras de conversão  */
	//check_conversion(tt, t.type);
	//conversion(t, tt);

    node n;
	n.type = t.type;
	materialize(n);
    
    n.translation = t.translation;
	/* Operação unária à esquerda */
    if(side == "left"){
		n.translation += "\t" + n.label + " = " + op.label + t.label + ";\n";
	}
	/* Operação unária à direita */
	else if(side == "right"){
		n.translation += "\t" + n.label + " = " +  t.label + op.label  + ";\n";
	}
    return n;
}

////*** CONVERSÃO: IMPLÍCITA E EXPLÍCITA ***////

/* Conversões numéricas perimitidas: (int) e (float) */
bool is_numeric(const string& s) {return s == "int" || s == "float";}

/* Validação da conversão */
void check_conversion(const string& l, const string& r){
	/*TODO: Aceitar outros tipos de conversão */
	if(!is_numeric(l) || !is_numeric(r)){
		report_error("Conversão não permitida entre tipos ("+ l +") e ("+ r +")");
	}
}

void check_conversion(const string& category, const string& l, const string& r){
	
}

/* Função de conversão explícita */
node casting(node& t, const string& type){
    
	materialize(t);
    string tt = t.type;
    
    if (tt == type) return t; 
    check_conversion(tt, type);

    return conversion(t, type);
}

/* Função de conversão implícita */
void coercion(node& l, node& r){
    string lt = l.type;
    string rt = r.type;

    check_conversion(lt, rt);

    if (lt == "float" && rt == "int"){
        r = conversion(r, "float");
    } 
    else if (lt == "int" && rt == "float"){
        l = conversion(l, "float");
    }
}

/* Função auxiliar para conversão */
node conversion(node& t, const string& type){

    node n;
    n.type = type;
    materialize(n);

    n.translation = t.translation;
    n.translation += "\t" + n.label + " = (" + type + ") " + t.label + ";\n";
    
    return n;
}

////*** TIPO DINÂMICO ***////

/* Modificação e atualização do mapa de variáveis */
void promote_symbol(node& n, const string& type){
    auto sym = lookup_symbol(n.label);
    //if(!sym) return; //Símbolo sempre existe, pois é checado antes em LVAL
    if(!n.is_static && sym->type != type){
        string label = gen_tmp_variable();
        sym->label = label;
        sym->type = type;

		variables.push_back({label,type});
        
        n.label = label;
        n.type = type;
        n.is_materialized = true;
    }
}



// Abrir novo escopo ()
void open_block(){
	scope_stack.push_back({});
}
// Fechar escopo
void close_block(){
	scope_stack.pop_back();
}

////*** BUSCA NAS TABELAS  ***////

//* Agora é uma pilha de tabelas de simbolos *//
shared_ptr<symbol> lookup_symbol(const string& name){
	for( auto it = scope_stack.rbegin(); it != scope_stack.rend(); ++it) 
	{
		auto found = it->find(name);
		if (found != it->end()) return found->second;
	}

	return nullptr;
}
// Registra um simbolo no escopo que está no topo da pilha //
void register_symbol(const string& name, shared_ptr<symbol> sym){

	if(scope_stack.back().count(name)) // Se ja tem uma variavel com esse nome no topo, dá erro
		report_error("Variavel '" + name + "' já declarada nesse escopo.");
	
	// Coloca no escopo atual
	else {
		scope_stack.back().try_emplace(name, sym);
	}

}


////*** MAIN ***////

int main(int argc, char* argv[]){
    tmp_var_count = 0;
    yy::parser p;
    open_block(); // Escopo globsl
    if (p.parse() == 0){ 
        cout << code;
        
        ofstream outFile("code.c");
        if(outFile.is_open()) outFile << code << endl;
        
		/* TODO: Organizar a escrita na tabela de símbolos */
        ofstream ofile("symbol_table.txt");
        if(ofile.is_open()) {
			for(const auto& scope : scope_stack){
				for(const auto& [name, sym] : scope){
					ofile << sym->type << " | " << sym->name << " | " << sym->label << endl;
				}
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
	//exit(1);
}