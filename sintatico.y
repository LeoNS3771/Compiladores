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
	#include "loops.hh"
	using namespace std;

	yy::parser::symbol_type yylex();
	
	////*** Variáveis globais  ***////
	int tmp_var_count = 0;
	string code;
	
	vector<pair<string,string>> variables;
	vector<map<string,shared_ptr<symbol>>> scope_stack;
	vector<loopInfo> loop_stack;

	int cur_depth = 0;

	////*** Variáveis externas ***////
	extern int yylineno;

	////*** Geradores de código  ***////
	string gen_tmp_variable();
	string gen_declarations(); 
	string gen_functions();
	int label_loop_number = 0;
	string gen_label_loop(){
		return "L"+ to_string(label_loop_number++) ;
	} 
	vector<Context> context_stack;
	vector<node> switch_stack;
	vector<string> switch_end_stack;

	void gen_literal(node& n, const string& type, const string& literal);
	void materialize(node& n);
	
	node gen_unary(const string& side, const op& op, node& t);
	node gen_expr(node& l, const op& op, node& r);

	////*** Funções auxiliares: temporários***////
	shared_ptr<symbol> lookup_symbol(const string& name);
	
	// Funções responsaveis pelo escopo //
	void open_block();
	void close_block();
	void open_loop();
	void open_switch(node & expr);

	Context *get_back_loop();
	Context *get_back_switch();


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
%token <std::string> TK_INT TK_FLOAT TK_CHAR TK_STRING TK_BOOL TK_TYPE TK_VAR TK_CAST 
%token <std::string> TK_SBLOCK TK_EBLOCK TK_IF TK_ELSE TK_WHILE TK_DO TK_BREAK TK_FOR TK_IN TK_RANGE
%token <std::string> TK_CONTINUE TK_CASE TK_SWITCH TK_DEFAULT TK_PRINT TK_INPUT 

%token <std::shared_ptr<symbol>> TK_ID
%token <op> OP_ADD OP_MINUS OP_MULT OP_DIV OP_MOD
%token <op> OP_EQ OP_NE OP_LE OP_GE OP_LT OP_GT
%token <op> OP_OR OP_AND OP_NOT

/*** Declaração de nódulos ***/
%type <node> COMMANDS STATEMENT DECLARATION ASSIGNMENT LVAL RVAL EXPR BLOCK CONDITIONAL LOOPCONTROL SWITCHBLOCK CASE_ITEM DEFAULT CASE_LIST LOOP OPT_ASSIGNMENT IO
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
				code = "/*Compilador*/\n"
				"#include <stdio.h>\n"
				"#include <string.h>\n"
				"#include <stdlib.h>\n\n";

				code += "int main(void) {\n";
				code += gen_declarations();
				code += "\n" + $1.translation;
				code += "\treturn 0;\n}\n";
			};

COMMANDS 	: COMMANDS STATEMENT {$$.translation = $1.translation + $2.translation;}
			| STATEMENT 		 {$$.translation = $1.translation;};
			

STATEMENT 	: DECLARATION 	 {$$.translation = $1.translation;}
			| ASSIGNMENT ';' {$$.translation = $1.translation;}  // Coloquei o ; aqui pq tava atrapalhando no for (melhor que criar novas regras so pro for)
			| BLOCK			 {$$.translation = $1.translation;}  // da pra fazer pros outros se quiser padronizar (ou tirar a necessidade de um ';')
			| CONDITIONAL	 {$$.translation = $1.translation;}
			| LOOP 			 {$$.translation = $1.translation;}
			| LOOPCONTROL    {$$.translation = $1.translation;}
			| IO		     {$$.translation = $1.translation;};
	
DECLARATION : TK_VAR TK_ID ';'
			{

				$2->type = "undefined";
				$2->is_static = false;
				$$.translation = "";

				register_symbol($2->name, $2);
			}
			| TK_VAR TK_ID ':' TK_TYPE ';'
			{
				string type = $4 == "string" ? "char*" : $4;
				$2->type = type;
				$2->is_static = true;
				$$.translation = "";
				register_symbol($2->name, $2);
			};

ASSIGNMENT : LVAL OP_AT RVAL
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

				// Se for string, atribuição é usando strcpy
				if($3.type == "char*"){
					$$.translation = $3.translation + $1.translation;
					$$.translation += "\tstrcpy(" + $1.label + ", " + $3.label + ");\n";
				}
				else{
					//coercion($1,$3); 
					$$.translation = $3.translation + $1.translation;
					$$.translation += "\t" + $1.label + " = " + $3.label + ";\n";
				}
			}
			
			| TK_VAR TK_ID OP_AT RVAL
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

			| TK_VAR TK_ID ':' TK_TYPE OP_AT  RVAL
			{
				
				materialize($6);
				if($4 != $6.type)
				 	report_error("Variável '" + $2->name + "' do tipo '" + $4 + "' recebendo " + "tipo '" + $6.type + "'");

				$2->is_static = true;

				string type = $4 == "string" ? "char*" : $4;
				$2->type = type;

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


// CONDICIONAIS AUAU
CONDITIONAL : TK_IF '(' EXPR ')' BLOCK TK_ELSE BLOCK
			{
				string label_if = gen_label_loop();
				string label_else = gen_label_loop();

				materialize($3);
				$$.translation = $3.translation;

				$$.translation += "\tif(!" + $3.label + ") " + "goto " + label_else + ";\n";
				
				$$.translation += $5.translation + "\n"; // Bloco do if

				$$.translation += "\tgoto " + label_if + ";\n";// Se entrou no if, vá para fora depois de terminar
				
				// Labels
				$$.translation += label_else + ":" + "\n" + $7.translation + "\n"; // Label do else
				
				$$.translation += label_if + ":\n"; // Label de saida
				
			}
			| TK_IF '(' EXPR ')' BLOCK 
			{
				string label_final = gen_label_loop();
				$$.translation = $3.translation;
				$$.translation += "\tif(!" + $3.label + ") " + "goto " + label_final + ";\n";
				$$.translation += $5.translation ; // Bloco do if

				// Labels
				$$.translation += label_final + ":" + "\n";
				
			}		

			| TK_SWITCH '(' EXPR ')' 
			{ 
				materialize($3); 
				open_switch($3);
			} ':' SWITCHBLOCK 
			{
				string end_label = get_back_switch()->end_label;
				
				$$.translation = $3.translation;
				$$.translation += $7.jumps; // adiciona todos os if's primeiro
				$$.translation += "\tgoto " + end_label + ";\n"; // Depois de todos os ifs vai para a label de saida
				$$.translation += $7.labels_jumps; // Labels + blocos
				$$.translation += end_label + ":\n"; // sempre vai para a label de saida
				
				context_stack.pop_back();	
			}
			;

OPT_ASSIGNMENT : ASSIGNMENT  {$$ = $1;}
               | /* vazio */ {$$.translation = "";}
               ;

			/******* LOOPS ********/
LOOP		: TK_WHILE '(' EXPR ')' {open_loop();} BLOCK
			{
				materialize($3);
				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;

				$$.translation = label_start + ":\n";
				$$.translation += $3.translation;

				$$.translation += "\tif(!" + $3.label + ") goto " + label_end + ";\n";
				$$.translation += $6.translation; // bloco
				$$.translation += "\tgoto " + label_start + ";\n";

				$$.translation += label_end + ":\n";

				context_stack.pop_back();
			}

			| TK_DO {open_loop();} BLOCK TK_WHILE '(' EXPR ')' ';'
			{				
				materialize($6);
				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;
				string label_jump = gen_label_loop();

				// pula a primeria verificação
				$$.translation = "\tgoto " + label_jump + ";\n";

				$$.translation += label_start + ":\n";
				$$.translation += $6.translation;

				$$.translation += "\tif(!" + $6.label + ") goto " + label_end + ";\n";

				$$.translation += label_jump + ":\n";
				$$.translation += $3.translation; // bloco

				$$.translation += "\tgoto " + label_start + ";\n";

				$$.translation += label_end + ":\n";

				context_stack.pop_back();
			}
			// unico obrigatorio é a condição
			| TK_FOR '(' OPT_ASSIGNMENT ';' EXPR ';' OPT_ASSIGNMENT ')' {open_loop();} BLOCK
			{
				materialize($5);

				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;

				// Primeiro assignment (declaração)
				$$.translation += $3.translation;

				$$.translation += label_start + ":\n";
				$$.translation += $5.translation;

				$$.translation += "\tif(!" + $5.label + ") goto " + label_end + ";\n";
				$$.translation += $10.translation; // bloco

				// segundo assignment (incremento)
				$$.translation += $7.translation;

				$$.translation += "\tgoto " + label_start + ";\n";
				$$.translation += label_end + ":\n";

				context_stack.pop_back();
			}
			// da pra fazer um range(maior, menor) tbm, mas provavelmente vai ser feito no codigo intermediario (mt resenha por agr)
			| TK_FOR TK_ID TK_IN TK_RANGE '(' EXPR ',' EXPR ')' {open_loop();} BLOCK
			{
				// fiz manualmente toda a inicialização do ID, talvez dê pra fazer de outra forma (reutilizar)
				$2->label = gen_tmp_variable(); 
				$2->type = $6.type;
				$2->is_static = true;
				$$.translation = "";
				variables.push_back({$2->label, $2->type}); 
				register_symbol($2->name, $2);

				node sym;
				sym.label = $2->name;
				sym.type = $2->type;
				sym.is_static = $2->is_static;
				sym.translation = ""; 

				materialize($6);
				materialize($8);

				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;

				op op_lt;
				op_lt.label = "<";
		
				$$.translation = "\t" + $2->label + " = " + $6.label + ";\n";
				$$.translation += label_start + ":\n";
				
				// cria a temporaria que recebe a verificação
				node cond = gen_expr(sym , op_lt, $8);
				$$.translation += cond.translation;

				$$.translation += "\tif(!" + cond.label + ") goto " + label_end + ";\n";
				$$.translation += $11.translation;

				// brute force, da pra fazer melhor (basicamente a minha vida)
				$$.translation += "\t" + $2->label + " = " + $2->label + " + 1;\n"; 

				$$.translation += "\tgoto " + label_start + ";\n";
				$$.translation += label_end + ":\n";

				context_stack.pop_back();
			}
			;
			

LOOPCONTROL : TK_BREAK ';'
			{
				if(context_stack.empty()){
					report_error("Break fora de loop");
					return 0;
				}

				$$.translation = "\tgoto " + context_stack.back().end_label + ";\n";
			}
			| TK_BREAK TK_INT ';'
			{
				int n = stoi($2);
				 
				if(n < 1){
					report_error("numero n invalido\n");
					return 0;
				}

				if(context_stack.size() < n){
					report_error("Break n é maior que a quantidade de loops\n");
					return 0;
				}
				
				auto& l = context_stack[context_stack.size() - n];
				
				$$.translation = "\tgoto " + l.end_label + ";\n";
				
			}
			
			| TK_CONTINUE ';'
			{
				if(context_stack.empty()){
					report_error("Continue fora de loop");
					return 0;
				}

				$$.translation = "\tgoto " + context_stack.back().start_label + ";\n";
			}
			;
	



SWITCHBLOCK		: CASE_LIST
				{
					$$.jumps = $1.jumps;
					$$.labels_jumps = $1.labels_jumps;

				}
				| CASE_LIST DEFAULT 
				{
					$$.jumps = $1.jumps + $2.jumps;
					$$.labels_jumps = $1.labels_jumps + $2.labels_jumps;

				}
				;

CASE_LIST 		: CASE_LIST CASE_ITEM 
				{
					$$.jumps = $1.jumps + $2.jumps;
					$$.labels_jumps = $1.labels_jumps + $2.labels_jumps;
				}

				| CASE_ITEM 
				{
					$$.jumps = $1.jumps;
					$$.labels_jumps = $1.labels_jumps;
				}
				;

// Unidade minima do case
CASE_ITEM 		: TK_CASE EXPR ':' BLOCK
				{
					string L_case = gen_label_loop();
					string end_label = get_back_switch()->end_label; // Pega o label de saida da switch
					
					materialize($2);

					op op_eq;
					op_eq.label = "==";
					node current_switch = get_back_switch()->switch_node; // Pega o switch atual da pilha
					node cmp_value = gen_expr(current_switch, op_eq, $2);
					
					// criando os ifs individuais
					$$.jumps = cmp_value.translation;
					$$.jumps += "\tif(" + cmp_value.label + ") goto " + L_case + ";\n";
					
					// bloco desse if
					$$.labels_jumps = L_case + ":\n" + $4.translation + "\tgoto " + end_label + ";\n";
					
					// O break deve vir aqui
				}
				;

DEFAULT			: TK_DEFAULT ':' BLOCK
				{
					string L_default = gen_label_loop();
					string end_label =  get_back_switch()->end_label;

					$$.jumps = "\tgoto " + L_default + ";\n";
					
					$$.labels_jumps = L_default + ":\n" + $3.translation;
				}
				;

// Bem facinho
IO			: TK_PRINT '(' EXPR ')' ';'
			{	
				materialize($3);
				string type;
				
				if($3.type == "char*")	type = "\"%s\\n\"";
				if($3.type == "int")	type = "\"%d\\n\"";
				if($3.type == "float")	type = "\"%f\\n\"";
				if($3.type == "char")	type = "\"%c\\n\"";
				if($3.type == "bool")	type = "\"%i\\n\"";
				  
				$$.translation = $3.translation;
				$$.translation += "\tprintf(" + type + ", " + $3.label + ");\n";
			}

			| TK_INPUT '(' EXPR ')' ';'
			{
				materialize($3);
				string type;
				
				if($3.type == "char*")	type = "\"%s\\n\"";
				if($3.type == "int")	type = "\"%d\\n\"";
				if($3.type == "float")	type = "\"%f\\n\"";
				if($3.type == "char")	type = "\"%c\\n\"";
				if($3.type == "bool")	type = "\"%i\\n\"";
				  
				$$.translation = $3.translation;
				$$.translation = "\tscanf(" + type + "," + $3.label + ");\n";

			}

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
			| TK_STRING 
			{
				gen_literal($$, "char*", $1);
			}
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
	if(type == "string"){

	}
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

// Função responsavel pela impressão das implementações das funções no codigo intermediario
string gen_functions(){
    string result;

    result =
        "int len(char *a){\n"
        "\tint res = 0;\n"
        "\tfor(int i = 0; a[i] != '\\0'; i++){\n"
        "\t\tres++;\n"
        "\t}\n"
        "\treturn res;\n"
        "}\n\n";

    return result;
}

/* Gerador de expressões binárias */
node gen_expr(node& l, const op& op, node& r){
    materialize(l);
    materialize(r);

  	node n;

	// Concatenação de string
	if(op.label == "+" && l.type == "char*" && r.type == "char*"){
		n.type = "char*";
		n.label = gen_tmp_variable();

		variables.push_back({n.label, n.type});
		n.translation = l.translation + r.translation;
		
		n.translation += "\t" + n.label + " = (char *) malloc(256);\n\t";
		n.translation += "strcpy(" + n.label + "," + l.label + ");\n"; 
		n.translation += "\tstrcat(" + n.label + "," + r.label + ");\n";
	}
	else{
	coercion(l,r); 
	
    n.type = l.type;
    materialize(n);
    n.translation = l.translation + r.translation;
    n.translation += "\t" + n.label + " = " + l.label + " " + op.label + " " + r.label + ";\n";

	}

	
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
	cur_depth++;
	scope_stack.push_back({});
}

// Fechar escopo
void close_block(){
	scope_stack.pop_back();
	cur_depth--;
}

// Adiciona na em context_stack o controle do fluxo do loop
void open_loop(){
	string label_start = gen_label_loop();
	string label_end = gen_label_loop();
	context_stack.push_back({ContextType::LOOP, cur_depth, label_start, label_end, {}});
}

void open_switch(node & expr){
	string label_start = gen_label_loop();
	string label_end = gen_label_loop();
	context_stack.push_back({ContextType::SWITCH, cur_depth, "", label_end, expr});
}

Context *get_back_loop(){
	for(auto it = context_stack.rbegin(); it != context_stack.rend(); ++it)
	{
		if (it->type == ContextType::LOOP){
			return &(*it);
		}
	}
	return nullptr;
}

Context *get_back_switch(){
	for(auto it = context_stack.rbegin(); it != context_stack.rend(); ++it)
	{
		if (it->type == ContextType::SWITCH){
			return &(*it);
		}
	
	}
	return nullptr;
}
/*
void close_loop(){
	cur_depth--;
	context_stack.pop_back();
}
*/

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