////*** Configuração do Bison C++***////
%skeleton "lalr1.cc"
%require "3.2"
%language "c++"	

////*** Configurações de Template/Construtor C++ ***////
%define api.value.type variant
%define api.token.constructor
%define parse.error verbose //TODO: Mensagens customizadas de erro sintático

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
	vector<string> errors;
	vector<pair<string,string>> variables;
	map<string,shared_ptr<symbol>> symbols;

	////*** Variáveis externas ***////
	extern int yylineno;

	////*** Geradores de código  ***////
	string gen_tmp_variable();
	string gen_declarations(); 
	
	void gen_literal(node& n, const string& type, const string& literal);
	void materialize(node& n);
	
	node gen_binary_expr(node& l, const op& op, node& r);
	node gen_unary_expr(const string& side, const op& op, node& t);
	node gen_casting(node& t, const string& type);
	
	////*** Funções auxiliares: temporários***////
	shared_ptr<symbol> lookup_symbol(const string& name);
	
	////*** Funções auxiliares: conversão ***////
	void expr_coercion(const string& category, const string& l, const string& r,node& n);
	void binary_coercion(const string& category, node& l, node& r, node& n);
	void expr_coercion(const string& category, node& t, node& n);
	void expr_cast(const string& target, node& t, node& n);
	node expr_conversion(node& t, const string& type);

	////*** Funções auxiliares: inferência ***////
	void promote_symbol(node& n, node& type);

	////*** Funções auxiliares: debug ***////
	void semantic_error(const string& msg);

	////*TODO: Lançar exceção para main capturar *////
}

/*** Declaração de tokens ***/
%token <std::string> TK_INT TK_FLOAT TK_CHAR TK_BOOL TK_TYPE TK_VAR TK_CAST
%token <std::shared_ptr<symbol>> TK_ID
%token <op> OP_ADD OP_MINUS OP_MULT OP_DIV OP_MOD
%token <op> OP_EQ OP_NE OP_LE OP_GE OP_LT OP_GT
%token <op> OP_OR OP_AND OP_NOT

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
			/*TODO: Separar headers e responsabilidades semânticas e sintáticas */
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

STATEMENT 	: DECLARATION ';'
			{
				auto sym = lookup_symbol($1.label);
				if(sym && sym->is_static) materialize($1);
				$$.translation = $1.translation;
			}
			| ASSIGNMENT ';' {$$.translation = $1.translation;}

			/* TODO: Criação de blocos pela identação ou marcador END e/ou identação*/
DECLARATION : TK_VAR TK_ID
			{
				auto sym = lookup_symbol($2->name);
				if(sym){
					semantic_error("Variável '" + $2->name + "' já declarada.");
					$$.has_error = true;
				}
				$2->type = "undefined";
				$2->is_static = false;

				symbols.try_emplace($2->name, $2);

				$$.label = $2->name;
				$$.type  = "undefined";
				$$.translation = "";
			}
			| TK_VAR TK_ID ':' TK_TYPE
			{
				auto sym = lookup_symbol($2->name);
				if(sym){
					semantic_error("Variável '" + $2->name + "' já declarada.");
					$$.has_error = true;
				} 

				$2->type = $4;
				$2->is_static = true;

				symbols.try_emplace($2->name, $2);

				$$.label = $2->name;
				$$.type = $4;
				$$.translation = "";
				//materialize($$);
			};

ASSIGNMENT : LVAL OP_AT RVAL
			{	
				if(!$1.has_error && !$3.has_error){
					materialize($3);
					promote_symbol($1, $3);
					materialize($1);
						
					$$.translation = $3.translation + $1.translation;
					$$.translation += "\t" + $1.label + " = " + $3.label + ";\n";
				}
				else{
					$$.translation = $3.translation; 
					$$.has_error = true;
				}
			}

LVAL 		: TK_ID 
			{
				auto sym = lookup_symbol($1->name);
				if(!sym){
					semantic_error("Variável '" + $1->name + "' usada, mas não declarada.");
					$$.has_error = true;
				}
				else{
					$$.type  = sym->type;
					$$.label = sym->name;
					$$.translation = "";
				}
			};
			| DECLARATION {$$ = $1;}


RVAL 		: EXPR {$$ = $1;};

	
			/*** Operadores numéricos ***/
EXPR 		: EXPR OP_ADD  	EXPR {$$ = gen_binary_expr($1,$2,$3);}
			| EXPR OP_MINUS EXPR {$$ = gen_binary_expr($1,$2,$3);}
			| EXPR OP_MULT 	EXPR {$$ = gen_binary_expr($1,$2,$3);}
			| EXPR OP_DIV 	EXPR {$$ = gen_binary_expr($1,$2,$3);}
			| EXPR OP_MOD 	EXPR {$$ = gen_binary_expr($1,$2,$3);}

			/*** Operadores relacionais ***/
			| EXPR OP_EQ EXPR {$$ = gen_binary_expr($1,$2,$3);}
			| EXPR OP_NE EXPR {$$ = gen_binary_expr($1,$2,$3);}
			| EXPR OP_LE EXPR {$$ = gen_binary_expr($1,$2,$3);}
			| EXPR OP_GE EXPR {$$ = gen_binary_expr($1,$2,$3);}
			| EXPR OP_LT EXPR {$$ = gen_binary_expr($1,$2,$3);}
			| EXPR OP_GT EXPR {$$ = gen_binary_expr($1,$2,$3);}

			/*** Operadores lógicos ***/
			| EXPR OP_OR  EXPR {$$ = gen_binary_expr($1,$2,$3);}
			| EXPR OP_AND EXPR {$$ = gen_binary_expr($1,$2,$3);}
			| OP_NOT EXPR  {$$ = gen_unary_expr("left",$1,$2);}
			| TK_CAST EXPR {$$ = gen_casting($2,$1);}
			
			| '(' EXPR ')' {$$ = $2;}

			| TK_INT   	{gen_literal($$,"int",$1);}
			| TK_FLOAT 	{gen_literal($$,"float",$1);}
			| TK_CHAR	{gen_literal($$,"char",$1);}
			| TK_BOOL	{gen_literal($$,"bool", $1);}
			| TK_ID 
			{
				auto sym = lookup_symbol($1->name);
				if(!sym){
					semantic_error("Variável '" + $1->name + "' usada, mas não declarada.");
					$$.has_error = true;
				}
				else if(!sym->is_initialized){
					if(sym->is_static) semantic_error("Variável estática '" + sym->name + "' usada, mas não inicializada.");
					else semantic_error("Variável dinâmica '" + sym->name + "' usada, mas não inferida.");
					$$.has_error = true;
				}
				else{
					$$.label = sym->name;
					$$.type  = sym->type;
					$$.translation = "";
				}
			};
%%

void gen_literal(node& n, const string& type, const string& literal){
	n.label = literal;
	n.type = type;
	n.translation = "";
}

////*** GERADOR DE VARIÁVEIS TEMPORÁRIAS ***////

void materialize(node& n){
	if(n.has_error) return;
	
    if(!n.is_materialized){
		auto sym = lookup_symbol(n.label);
		if(sym){
			/* Reutiliza um temporário previamente registrado  */
			if(!sym->label.empty()) n.label = sym->label;
			/* Gera um temporário novo para um identificador */
			else{
				string label = gen_tmp_variable();
				sym->label = label;

				n.label = label;
				variables.push_back({label, n.type == "bool" ? "int" : n.type});
			}
		}
		/* Verifica se é um literal pela ausência de tradução */
		else if(n.translation.empty()){
			string label = gen_tmp_variable();
			n.translation += "\t" + label + " = " + n.label + ";\n";

			n.label = label;
			variables.push_back({label,n.type == "bool" ? "int" : n.type});
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
node gen_binary_expr(node& l, const op& op, node& r)
{
    node n;
    binary_coercion(op.category,l,r,n);

	if(!n.has_error){
        materialize(l);
        materialize(r);
        materialize(n);

        n.translation = l.translation + r.translation;
        n.translation += "\t" + n.label + " = " + l.label + " " + op.label + " " + r.label + ";\n";
    }
	else n.translation = l.translation + r.translation;

	return n;
}


/* Gerador de expressões unárias */
node gen_unary_expr(const string& side, const op& op, node& t){

    node n;
    expr_coercion(op.category, t, n);

	if(!n.has_error){
		materialize(t);
		materialize(n);

		n.translation = t.translation;
		if(side == "left"){
			n.translation += "\t" + n.label + " = " + op.label + t.label + ";\n";
		} 
		if(side == "right"){
			n.translation += "\t" + n.label + " = " + t.label + op.label + ";\n";
    	}
	}
	else n.translation = t.translation;
	
    return n;
}


////*** CONVERSÃO: IMPLÍCITA E EXPLÍCITA ***////

/* Função de conversão implícita */
void binary_coercion(const string& category, node& l, node& r, node& n){

	if(l.has_error || r.has_error){
        n.has_error = true;
        return;
	}

	expr_coercion(category,l.type,r.type,n);

	if(n.has_error) return;

	if(category == "arithmetic"){
		if(l.type != n.type) l = expr_conversion(l, n.type);
		if(r.type != n.type) r = expr_conversion(r, n.type);
	}
	else if(category == "relational"){
		if(l.type != r.type){
			string target = (l.type == "float" || r.type == "float") ? "float" : l.type;
			if(l.type != target) l = expr_conversion(l, target);
			if(r.type != target) r = expr_conversion(r, target);
		}
	}
}


/* Função de conversão explícita */
node gen_casting(node& t, const string& type){

    node n;
	expr_cast(type, t, n);
	if(n.has_error) return n;
	if(n.type == t.type) return t;

    return expr_conversion(t, n.type);
}


/* Função auxiliar para conversão */
node expr_conversion(node& t, const string& type){
	if(t.has_error) return t;
	
	materialize(t);
    node n;
    n.type = type;
    materialize(n);

    n.translation = t.translation;
    n.translation += "\t" + n.label + " = (" + type + ") " + t.label + ";\n";
    
    return n;
}



////*** TIPO DINÂMICO ***////

/* Modificação e atualização do mapa de variáveis */
void promote_symbol(node& n, node& t){
    if(t.has_error){
        n.has_error = true;
        return;
    }

	auto sym = lookup_symbol(n.label);
	if(!sym){
    n.has_error = true;
    return;
	}
	if(sym->type != t.type){
		if(sym->is_static){
			semantic_error("Variável estática '" + sym->name + "' do tipo (" + sym->type + ") não pode receber (" + t.type + ")");
			n.has_error = true;
			return;
		}
		else{
			string label = gen_tmp_variable();
			sym->label = label;
			sym->type = t.type;

			variables.push_back({label, t.type == "bool" ? "int" : t.type});

			n.label = label;
			n.type  = t.type;
			n.is_materialized = true;
		}
	}
	sym->is_initialized = true;
}

////*** VALIDAÇÃO E ERROS ***////

/* Validação de expressões binárias */
void expr_coercion(const string& category, const string& l, const string& r, node& n){
	if(n.has_error) return;

    if(binary_table.count(category)){
        if(binary_table[category].count({l, r})){
            n.type = binary_table[category].at({l, r});
			return;
        }
    }
	semantic_error("Operação binária com categoria '" + category + "' não permitida para tipos (" + l + ") e (" + r + ")");
	n.has_error = true;
}



/* Validação de expressões unárias */
void expr_coercion(const string& category, node& t, node& n){
    if(t.has_error){
		n.has_error = true;
        return;
    }
    
    if (unary_table.count(category)) {
        if (unary_table[category].count(t.type)) {
            n.type = unary_table[category].at(t.type);
			return;
        }
    }
    semantic_error("Operação unária com categoria '" + category + "' não permitida para o tipo (" + t.type + ")");
    n.has_error = true;
}

void expr_cast(const string& target, node& t, node& n){
    if(t.has_error){
        n.has_error = true;
        return;
    }
	
    if(target == t.type){
        n.type = target;
        return;
    }

    if(cast_table.count({t.type,target})){
        n.type = target;
        return;
    }
	semantic_error("Conversão explícita de (" + t.type + ") para (" + target + ") não permitida.");
    n.has_error = true;
}



////*** BUSCA NAS TABELAS  ***////

/* Busca variável na tabela de símbolos */
shared_ptr<symbol> lookup_symbol(const string& name){
	auto it = symbols.find(name);
	if (it != symbols.end()) return it->second; 
	else return nullptr;
}

////*** MAIN ***////

int main(int argc, char* argv[]){
    tmp_var_count = 0;
    yy::parser p;
	
	init_conversion_table();

    if(p.parse() == 0 && errors.empty()){ 
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
	else{
		for(const auto& err : errors)
        cerr << err << endl;
	}
    return 0;
}

/*TODO: Trocar essa função por uma versão customizada */
void yy::parser::error(const std::string& msg){
    errors.push_back("ERRO SINTÁTICO: linha (" + to_string(yylineno) +"): " + msg);
}
/*
void syntax_error(const string& msg){
    errors.push_back("ERRO SINTÁTICO: linha (" + to_string(yylineno) +"): " + msg);
}*/

void semantic_error(const string& msg){
	errors.push_back("ERRO SEMÂNTICO: linha (" + to_string(yylineno) + "): " + msg);
}