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
	
	node gen_unary(const string& side, const op& op, node& t);
	node gen_expr(node& l, const op& op, node& r);
	
	////*** Funções auxiliares: temporários***////
	shared_ptr<symbol> lookup_symbol(const string& name);
	
	////*** Funções auxiliares: conversão ***////
	string expr_type(const string& category, const string& l, const string& r);
	string unary_type(const string& category, const string& type);
	string cast_type(const string& target, const string& source);

	node conversion(node& t, const string& type);
	string coercion(const string& category, node& l, node& r);
	node casting(node& t, const string& type);

	////*** Funções auxiliares: inferência ***////
	void promote_symbol(node& n, const string& type);

	////*** Funções auxiliares: debug ***////
	void report_error(const string& msg);
	bool is_invalid(const string& l, const string& r);
	bool is_invalid(const string& t);

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

STATEMENT 	: DECLARATION {$$.translation = $1.translation;}
			| ASSIGNMENT  {$$.translation = $1.translation;}

			/* TODO: Criação de blocos pela identação ou marcador END e/ou identação*/
DECLARATION : TK_VAR TK_ID ';'
			{
				auto sym = lookup_symbol($2->name);
				if(sym) report_error("Variável '" + $2->name + "' já declarada.");

				$2->type = "undefined";
				$2->is_static = false;
				$$.translation = "";

				symbols.try_emplace($2->name, $2);
			}
			| TK_VAR TK_ID ':' TK_TYPE ';'
			{
				auto sym = lookup_symbol($2->name);
				if(sym) report_error("Variável '" + $2->name + "' já declarada.");

				$2->type = $4;
				$2->is_static = true;
				$$.translation = "";

				symbols.try_emplace($2->name, $2);
			};

ASSIGNMENT : LVAL OP_AT RVAL ';'
			{
				if(!is_invalid($1.type,$3.type)){
					materialize($3);
					promote_symbol($1, $3.type);
					materialize($1);
						
					$$.translation = $3.translation + $1.translation;
					$$.translation += "\t" + $1.label + " = " + $3.label + ";\n";
				}
				else{
					$$.translation = $3.translation; 
					$$.type = "invalid";
				}
			}

			| TK_VAR TK_ID OP_AT RVAL ';'
            {
                auto sym = lookup_symbol($2->name);
                if(sym) report_error("Variável '" + $2->name + "' já declarada.");

                if(!is_invalid($4.type)){
                    materialize($4);
                    
                    $2->is_static = false;
                    $2->type = $4.type;
                    $2->label = gen_tmp_variable();
                    variables.push_back({$2->label, $2->type == "bool" ? "int" : $2->type});

                    symbols.try_emplace($2->name, $2);
                    $$.translation = $4.translation;
                    $$.translation += '\t' + $2->label + " = " + $4.label + ";\n";
                } 
				else{
                    $$.translation = $4.translation;
                    $$.type = "invalid";
                }
            }

			| TK_VAR TK_ID ':' TK_TYPE OP_AT RVAL ';'
            {
                auto sym = lookup_symbol($2->name);
                if(sym) report_error("Variável '" + $2->name + "' já declarada.");

                if(!is_invalid($6.type)){
                    materialize($6);

                    if($4 != $6.type){
                        report_error("Variável '" + $2->name + "' do tipo '" + $4 + "' não pode receber '" + $6.type + "'");
                        $$.type = "invalid";
                        $$.translation = $6.translation;
                    } 
					else{
                        $2->is_static = true;
                        $2->type = $4;
                        $2->label = gen_tmp_variable();
                        variables.push_back({$2->label, $2->type == "bool" ? "int" : $2->type});

                        symbols.try_emplace($2->name, $2);
                        $$.translation = $6.translation;
                        $$.translation += '\t' + $2->label + " = " + $6.label + ";\n";
                    }
                }
				else{
                    $$.translation = $6.translation;
                    $$.type = "invalid";
                }
            }

LVAL 		: TK_ID 
			{
				auto sym = lookup_symbol($1->name);
				if(!sym){
					report_error("Variável '" + $1->name + "' usada, mas não declarada.");
					$$.type = "invalid";
				}
				else{
					$$.type  = sym->type;
					$$.label = sym->name;
					$$.is_static = sym->is_static;
					$$.translation = "";
				}
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
					report_error("Variável '" + $1->name + "' usada, mas não declarada.");
					$$.type = "invalid";
				}
				else{
					$$.label = sym->name;
					$$.type  = sym->type;
					$$.is_static = sym->is_static;
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
	if(is_invalid(n.type)) return;
	
    if(!n.is_materialized){
		auto sym = lookup_symbol(n.label);
		if(sym){
			if(sym->type == "undefined"){
            	report_error("Variável Dinâmica '" + sym->name + "' usada, mas não inferida.");
			}
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
node gen_expr(node& l, const op& op, node& r)
{
    node n;
    n.type = coercion(op.category,l,r);

	if(!is_invalid(n.type)){
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
node gen_unary(const string& side, const op& op, node& t){

    node n;
    n.type = unary_type(op.category, t.type);

	if(!is_invalid(n.type)){
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
string coercion(const string& category, node& l, node& r){
	string type = expr_type(category,l.type,r.type);

	if(is_invalid(type)) return "invalid";

	if(category == "arithmetic"){
		if(l.type != type) l = conversion(l, type);
		if(r.type != type) r = conversion(r, type);
	}
	else if(category == "relational"){
        if(l.type != r.type){
            string target = (l.type == "float" || r.type == "float") ? "float" : l.type;
            if(l.type != target) l = conversion(l, target);
            if(r.type != target) r = conversion(r, target);
        }
    }
	return type;
}


/* Função de conversão explícita */
node casting(node& t, const string& type){

    node n;
    n.type = cast_type(type, t.type);
    if(is_invalid(t.type) || n.type == t.type) return t; 

    return conversion(t, n.type);
}


/* Função auxiliar para conversão */
node conversion(node& t, const string& type){
	if(is_invalid(t.type)) return t;
	
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
void promote_symbol(node& n, const string& type){
	if(is_invalid(type)) return;
    auto sym = lookup_symbol(n.label);

	if(sym){
		if(n.is_static){
			if (sym->type != type){
				report_error("Variavel estática '" + sym->name + "' do tipo (" + sym->type + ") não pode receber (" + type + ")");
				n.type = "invalid";
			}
		}
		if(!n.is_static){
			if(sym->type == "undefined" || sym->type != type){
				string label = gen_tmp_variable();
				sym->label = label;
				sym->type = type;
				variables.push_back({label, type == "bool" ? "int" : type});
				
				n.label = label;
				n.type = type;
				n.is_materialized = true;
			}
		}
    } 
}



////*** VALIDAÇÃO E ERROS ***////

/* Validação de expressões binárias */
string expr_type(const string& category, const string& l, const string& r){
	if(is_invalid(l,r)) return "invalid";

    if(binary_table.count(category)){
        auto& table = binary_table[category];
        if(table.count({l, r})){
            return table.at({l, r});
        }
    }
	if(l != "undefined" && r != "undefined"){
		report_error("Operação binária com categoria '" + category + "' não permitida para tipos (" + l + ") e (" + r + ")");
	}
	return "invalid";
}



/* Validação de expressões unárias */
string unary_type(const string& category, const string& type){
    if(is_invalid(type)) return "invalid";
    
    if (unary_table.count(category)) {
        if (unary_table[category].count(type)) {
            return unary_table[category].at(type);
        }
    }
	if(type != "undefined"){
    	report_error("Operação unária com categoria '" + category + "' não permitida para o tipo (" + type + ")");
	}
    return "invalid";
}

string cast_type(const string& target, const string& source){
    if(is_invalid(source)) return "invalid";
    if(target == source) return target;

    if(cast_table.count({source,target})) return target;

	if(source != "undefined"){
		report_error("Conversão explícita de (" + source + ") para (" + target + ") não permitida.");
	}
    return "invalid";
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

void yy::parser::error(const std::string& s){
    std::cerr << "ERRO: linha (" << yylineno << "): " << s << std::endl;
}

/*TODO: Trocar essa função, capturando erros pelo yy::parser::error */
void report_error(const string& msg){
	errors.push_back("ERRO: linha (" + to_string(yylineno) + "): " + msg);
}

bool is_invalid(const string& l, const string& r){
	return l == "invalid" || r == "invalid";
}

bool is_invalid(const string& t){
	return t == "invalid";
}