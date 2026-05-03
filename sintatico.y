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
	shared_ptr<symbol> lookup_symbols(const string& name);
	void promote_symbol(node& n, const string& type);

	/*** Funções auxiliares: conversão ***/
	bool is_numeric(const string& s);

	void check_conversion(const string& l, const string& r);
	node conversion(const string& type, node& t);
	void coercion(node& l, node& r);
	node casting(const string& type, node& t);

	/*** Funções auxiliares: inferência ***/
	void inference(node& l, node& r);

	/*** Funções auxiliares: debug ***/
	void report_error(const string& msg);
	/*TODO: Lançar exceção para main capturar */
}

/*** Declaração de tokens ***/
%token <std::string> TK_INT TK_FLOAT TK_CHAR TK_BOOL TK_TYPE TK_VAR OP_CAST
%token <std::shared_ptr<symbol>> TK_ID

/*** Declaração de nódulos ***/
%type <node> COMMANDS STATEMENT DECL ATRI EXPR RVAL LVAL
%start S

%right OP_AT OP_CAST
%left  OP_EQ OP_NE OP_LE OP_GE OP_LT OP_GT
%left  OP_OR
%left  OP_AND
%left  OP_ADD OP_MINUS
%left  OP_MULT OP_DIV
%left  OP_MOD
%right OP_NOT

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

STATEMENT 	: DECL  {$$.translation = $1.translation;}
			| ATRI  {$$.translation = $1.translation;}

			/* TODO: Criação de blocos pela identação ou marcador END e/ou identação*/
DECL 		: TK_VAR TK_ID ';'
			{
				if(!$2->type.empty()){
						string msg = "Variável '" + $2->name + "' já declarada.";
						report_error(msg);
					}
				$2->type = "undefined";
				$$.translation = "";
			}
			| TK_VAR TK_ID ':' TK_TYPE ';'
			{
				if(!$2->type.empty()){
						string msg = "Variável '" + $2->name + "' já declarada.";
						report_error(msg);
					}
				$2->type = $4;
				$$.translation = "";
			};

ATRI 		: LVAL OP_AT RVAL ';'
			{
				/* Verificação de expressão com tipo indefinido em RVAL */
				if($3.type == "undefined"){
					string msg = "Atribuição com tipo indefinido de '" + $3.label + "' em '" + $1.label + "'";
					report_error(msg);
				}
				/* Inferência de tipo para LVAL com base em RVAL */
				else if($1.type == "undefined") promote_symbol($1, $3.type);

				/* Coerção de tipo para RVAL com base em LVAL */
				if($1.type != $3.type) $3 = conversion($1.type, $3);
				
				materialize($1);
				$$.translation = $3.translation;
				$$.translation += "\t" + $1.label + " = " + $3.label + ";\n";
			};

			/* TODO: Expansão para atribuição em sequência */
LVAL 		: TK_ID 
			{
				if($1->type.empty()){
					string msg = "Identificador '" + $1->name + "' não declarado.";
					report_error(msg);
				}
				$$.type  = $1->type;
				$$.label = $1->name;
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
			| OP_CAST EXPR {$$ = casting($1,$2);}
			
			| '(' EXPR ')' {$$ = $2;}

			| TK_INT   	{gen_literal($$,"int",$1);}
			| TK_FLOAT 	{gen_literal($$,"float",$1);}
			| TK_CHAR	{gen_literal($$,"char",$1);}
			| TK_BOOL	{gen_literal($$,"int", $1);}
			| TK_ID 
			{
				if ($1->type.empty()){
					string msg = "Identificador '" + $1->name + "' não declarado.";
					report_error(msg);
				}
				$$.label = $1->name;
				$$.type  = $1->type;
				$$.translation = "";
			};
%%

void gen_literal(node& n, const string& type, const string& literal){
	n.label = literal;
	n.type = type;
	n.translation = "";
}


void materialize(node& n){
	/* Caso o nó não possua um temporário */
    if(!n.is_materialized){
		/* Verifica se é um identificador pela tabela de símbolos */
		auto sym = lookup_symbols(n.label);

		if(sym){
			/* Cria temporário para um identificador */
			if(sym->label.empty()){
				sym->label = gen_tmp_variable();
			}

			variables[sym->label] = n.type;
			sym->type = n.type;
			n.label = sym->label;
		}
		/* Verifica se é um literal pela ausência de tradução */
		else if(n.translation.empty()){
			string label = gen_tmp_variable();
			n.translation += "\t" + label + " = " + n.label + ";\n";

			n.label = label;
			variables[n.label] = n.type;
		}
		/* Para qualquer outro nó não-terminal */
		else{
			string label = gen_tmp_variable();
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
node gen_expr(node& l, const string& op, node& r){

	/* Criação de temporários para os nós */
	materialize(l);
    materialize(r);

	/* Tentativa de inferência pelo contexto */
	/* Evita a propagação expressões com tipagem indefinida */
	inference(l,r);

	/* Tentativa de conversão implícita */
	/* Evita operações entre tipos incompatíveis */
	coercion(l,r);

    node n;
	n.type = l.type;
    materialize(n);

	/* Tradução da expressão */
    n.translation = l.translation + r.translation;
    n.translation += "\t" + n.label + " = " + l.label + " " + op + " " + r.label + ";\n";

    return n;
}

/* Gerador de expressões unárias */
node gen_unary(const string& side, const string& op, node& t){
	
	/* Criação de temporário para o nó */
	materialize(t);

    node n;
	n.type = t.type;
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

	/*TODO: Substituir por uma matriz de conversão */
	if(!is_numeric(l) || !is_numeric(r)){
		string msg = "Conversão não permitida entre tipos ("+ l +") e ("+ r +")";
		report_error(msg);
	}
}

/* Função de conversão implícita */
void coercion(node& l, node& r){

    check_conversion(l.type, r.type);

	/* Coerção: lado direito */
    if (l.type == "float" && r.type == "int"){
        r = conversion("float", r);
    } 
	/* Coerção: lado esquerdo */
    else if (l.type == "int" && r.type == "float"){
        l = conversion("float", l);
    }
}


/* Função de conversão explícita */
node casting(const string& type, node& t){
	
	materialize(t);
    check_conversion(type, t.type);
   	// if (t.type == type) 
	/* TODO: Aviso de conversão redundante */;
    return conversion(type, t);
}

/* Função auxiliar para conversão */
node conversion(const string& type, node& t){
    
    node n;
	n.type = type;
	materialize(n);
    
	/* Tradução da conversão: implícita e explícita */
    n.translation = t.translation;
    n.translation += "\t" + n.label + " = (" + type + ") " + t.label + ";\n";
    
    return n;
}

/*** INFERÊNCIA DE TIPAGEM ***/

/* Modificação do tipo e atualização do mapa de variáveis */
void promote_symbol(node& n, const string& type){
	/* Verifica se é um identificador pela tabela de símbolos */
	auto sym = lookup_symbols(n.label);

	/* Promove o tipo do indetificador */
	if(sym && !sym->label.empty()){
		sym->type = type;
		variables[sym->label] = type;
	}
	/* Promove o tipo do temporário */
	else if (variables.count(n.label)){
		variables[n.label] = type;
	}
	n.type = type;
}


shared_ptr<symbol> lookup_symbols(const string& name){
	auto it = symbols.find(name);
	
	if (it != symbols.end()) return it->second; 
	else return nullptr;
}

/* Inferência de tipo pelo contexto da expressão */
void inference(node& l, node& r){

    if(l.type == "undefined" && r.type != "undefined"){
        promote_symbol(l, r.type);
    }

    else if(r.type == "undefined" && l.type != "undefined"){
        promote_symbol(r, l.type);
    }

    else if(l.type == "undefined" && r.type == "undefined"){
    	string msg = "Expressão com tipos indefinidos '"+ l.label +"' e '"+ r.label +"'";
		report_error(msg);
    }
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
	//exit(1);
}