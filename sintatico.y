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
	string to_ir_type(const string& type); 

	////*** Funções auxiliares: inferência ***////
	void promote_symbol(node& n, const string& type);

	////*** Funções auxiliares: debug ***////
	void report_error(const string& msg);
	////*TODO: Lançar exceção para main capturar *////
}

/*** Declaração de tokens ***/
%token <std::string> TK_INT TK_FLOAT TK_CHAR TK_STRING TK_BOOL TK_TYPE TK_VAR TK_CAST 
%token <std::string> TK_SBLOCK TK_EBLOCK TK_IF TK_ELSE TK_WHILE TK_DO TK_BREAK TK_FOR TK_IN TK_RANGE
%token <std::string> TK_CONTINUE TK_CASE TK_SWITCH TK_DEFAULT TK_PRINT TK_PRINTL TK_INPUT

%token <std::shared_ptr<symbol>> TK_ID
%token <op> OP_ADD OP_MINUS OP_MULT OP_DIV OP_MOD
%token <op> OP_EQ OP_NE OP_LE OP_GE OP_LT OP_GT
%token <op> OP_OR OP_AND OP_NOT

/*** Declaração de nódulos ***/
%type <node> COMMANDS STATEMENT DECLARATION ASSIGNMENT LVAL RVAL EXPR BLOCK 
%type <node> CONDITIONAL LOOPCONTROL SWITCHBLOCK CASE_ITEM DEFAULT CASE_LIST LOOP OPT_ASSIGNMENT IO FOR_DECLARATION PRINT_LIST
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
				$2->type = $4;
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
				if($3.type == "string"){
					$$.translation = $3.translation + $1.translation;
					$$.translation += "\t" + $1.label + " = (char*) malloc(4096);\n";
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
				variables.push_back({$2->label, to_ir_type($2->type)});

				register_symbol($2->name, $2);
				$$.translation = $$.translation + $4.translation;
				$$.translation += '\t' + $2->label + " = " + $4.label + ";\n";

			}

			| TK_VAR TK_ID ':' TK_TYPE OP_AT  RVAL
			{
				
				materialize($6);
				if($4 != $6.type)
				 	report_error("Variável '" + $2->name + "' do tipo '" + $4 + "' recebendo " + "tipo '" + $6.type + "'");
				
				$2->type = $4;
				$2->is_static = true;

				
				$2->label = gen_tmp_variable();
				variables.push_back({$2->label, to_ir_type($2->type)});
				
				if($2->type == "string"){
					$$.translation += "\t" + $2->label + " = (char*) malloc(4096);\n";
					$$.translation += "\t" + $2->label + "[0] = '\\0';\n";
				}

				register_symbol($2->name, $2);
				$$.translation = $$.translation + $6.translation;
				$$.translation += '\t' + $2->label + " = " + $6.label + ";\n";

			}
			| LVAL OP_ADD OP_ADD
			{
				materialize($1);
				$$.translation = "\t" + $1.label + " = " + $1.label + " + 1;\n"; 
			}
			| LVAL OP_MINUS OP_MINUS
			{
				materialize($1);
				$$.translation = "\t" + $1.label + " = " + $1.label + " - 1;\n"; 
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

FOR_DECLARATION : TK_ID
			{
				auto ini = lookup_symbol($1->name);
				// ja foi declarado
				if(ini){
					// cria label se n existe (tava bugando)
					if(!ini->label.empty()){
						$1->label = ini->label;
					} else {
						ini->label = gen_tmp_variable();
						variables.push_back({ini->label, "int"});
						$1->label = ini->label;
					}

					if(ini->is_static == true && ini->type != "int"){
						report_error("variavel " + ini->name + " é estatica do tipo " + ini->type + "\n;");
						return 0;
					}

					ini->type  = "int"; // tem que atualizar o tipo na tabela (sempre int)
					$1->type      = "int";
					$1->is_static = ini->is_static;
				}
				else{
					$1->label     = gen_tmp_variable();
					$1->type      = "int";
					$1->is_static = true;
					variables.push_back({$1->label, "int"});
					register_symbol($1->name, $1);
				}

				$$.label           = $1->label;
				$$.type            = $1->type;
				$$.is_static       = $1->is_static;
				$$.is_materialized = true;
				$$.translation     = "";
			}

			/******* LOOPS ********/
LOOP		: TK_WHILE '(' EXPR ')' {open_loop();} BLOCK
			{	
				materialize($3);
				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;
				string label_continue = get_back_loop()->continue_label;

				$$.translation = label_start + ":\n";
				$$.translation += $3.translation;

				$$.translation += "\tif(!" + $3.label + ") goto " + label_end + ";\n";
				$$.translation += $6.translation; // bloco

				if(label_continue != "") $$.translation += label_continue + ":\n";
				$$.translation += "\tgoto " + label_start + ";\n";

				$$.translation += label_end + ":\n";
				context_stack.pop_back();
			}

			| TK_DO {open_loop();} BLOCK TK_WHILE '(' EXPR ')' ';'
			{				
				materialize($6);
				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;
				string label_continue = get_back_loop()->continue_label;
				string label_jump = gen_label_loop();

				// pula a primeria verificação
				$$.translation = "\tgoto " + label_jump + ";\n";

				$$.translation += label_start + ":\n";
				$$.translation += $6.translation;

				$$.translation += "\tif(!" + $6.label + ") goto " + label_end + ";\n";

				$$.translation += label_jump + ":\n";
				$$.translation += $3.translation; // bloco
				
				if(label_continue != "") $$.translation += label_continue + ":\n";
				$$.translation += "\tgoto " + label_start + ";\n";

				$$.translation += label_end + ":\n";

				context_stack.pop_back();
			}
			// unico obrigatorio é a condição
			| TK_FOR '(' {open_block();} OPT_ASSIGNMENT {open_block();} ';' EXPR ';' OPT_ASSIGNMENT ')' {open_loop();} BLOCK
			{
				materialize($7);

				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;

				// Primeiro assignment (declaração)
				$$.translation += $4.translation;

				$$.translation += label_start + ":\n";
				$$.translation += $7.translation;

				$$.translation += "\tif(!" + $7.label + ") goto " + label_end + ";\n";
				$$.translation += $12.translation; // bloco

				// segundo assignment (incremento)
				$$.translation += $9.translation;

				$$.translation += "\tgoto " + label_start + ";\n";
				$$.translation += label_end + ":\n";

				context_stack.pop_back();
			}
			// da pra fazer um range(maior, menor) tbm, mas provavelmente vai ser feito no codigo intermediario (mt resenha por agr)
			| TK_FOR FOR_DECLARATION TK_IN TK_RANGE '(' EXPR ',' EXPR ')' {open_loop();} BLOCK
			{
				// nao materializa o $2, n sei pq mas da erro
				materialize($6);
				materialize($8);

				if($6.type != "int" || $8.type != "int"){
					report_error("Valor no intervalo in range() com tipo != int");
					return 0;
				}

				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;
				string label_continue = get_back_loop()->continue_label;

				op op_lt;
				op_lt.label = "<";

				$$.translation = $6.translation;
				$$.translation += "\t" + $2.label + " = " + $6.label + ";\n";
				$$.translation += label_start + ":\n";
				
				// cria a temporaria que recebe a verificação
				node cond = gen_expr($2 , op_lt, $8);
				$$.translation += cond.translation;	materialize($8);

				if($6.type != "int" || $8.type != "int"){
					report_error("Valor no intervalo in range() com tipo != int");
					return 0;
				}

				$$.translation += "\tif(!" + cond.label + ") goto " + label_end + ";\n";
				$$.translation += $11.translation;

				// brute force, da pra fazer melhor (basicamente a minha vida)
				if(label_continue != "") $$.translation += label_continue + ":\n";
				$$.translation += "\t" + $2.label + " = " + $2.label + " + 1;\n"; 

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
				if(get_back_loop() == nullptr){
					report_error("Continue fora de loop");
				}
				get_back_loop()->continue_label = gen_label_loop();
				$$.translation = "\tgoto " + get_back_loop()->continue_label + ";\n";
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

IO			: TK_PRINT '(' PRINT_LIST ')' ';'
			{	
				$$.translation = $3.translation;
			}
			|	TK_PRINTL '(' EXPR ')' ';'
			{	
				materialize($3);
				string type;
				
				if($3.type == "string")	type = "\"%s\\n\"";
				if($3.type == "int")	type = "\"%d\\n\"";
				if($3.type == "float")	type = "\"%f\\n\"";
				if($3.type == "char")	type = "\"%c\\n\"";
				if($3.type == "bool")	type = "\"%i\\n\"";
				  
				$$.translation = $3.translation;
				$$.translation += "\tprintf(" + type + ", " + $3.label + ");\n";
			}
			| TK_INPUT '(' EXPR ')' ';'
			{	
				string fmt;
				
				if($3.type == "undefined"){
					promote_symbol($3, "string");
					$3.type    = "string";
					$3.ir_type = "char*";
				}
				materialize($3);
				
				if($3.type == "string")	fmt = "\"%s\", "  + $3.label;
				if($3.type == "int")	fmt = "\"%d\", &" + $3.label;
				if($3.type == "float")	fmt = "\"%f\", &" +  $3.label;
				if($3.type == "char")	fmt = "\"%c\", &" +  $3.label;
				if($3.type == "bool")	fmt = "\"%i\", &" +  $3.label;
				
				
				$$.translation = $3.translation;
				$$.translation += "\tscanf(" + fmt + ");\n";
			}


PRINT_LIST 	:  EXPR ',' PRINT_LIST 
				{
					materialize($1);

					string type;
					
					if($1.type == "string")	type = "\"%s\"";
					if($1.type == "int")	type = "\"%d\"";
					if($1.type == "float")	type = "\"%f\"";
					if($1.type == "char")	type = "\"%c\"";
					if($1.type == "bool")	type = "\"%i\"";
					
					$$.translation = $1.translation;
					$$.translation += "\tprintf(" + type + ", " + $1.label + ");\n";
					$$.translation += $3.translation;

				}
				
				| EXPR 
				{
					materialize($1);
					string type;
					
					if($1.type == "string")	type = "\"%s\"";
					if($1.type == "int")	type = "\"%d\"";
					if($1.type == "float")	type = "\"%f\"";
					if($1.type == "bool")	type = "\"%i\"";
					if($1.type == "char")	type = "\"%c\"";
					
					$$.translation = $1.translation;
					$$.translation += "\tprintf(" + type + ", " + $1.label + ");\n";	
				}
			
			;

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
					gen_literal($$, "string", $1);
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
	n.label = literal;
	n.type = type;
	n.ir_type = to_ir_type(type);
	
	
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
				variables.push_back({label,to_ir_type(n.type)});
				if(sym->type == "string"){
     	   			n.translation += "\t" + label + " = (char*) malloc(4096);\n";
        			n.translation += "\t" + label + "[0] = '\\0';\n";
    			}
			}
		}
		/* Verifica se é um literal pela ausência de tradução */
		else if(n.translation.empty()){
			string label = gen_tmp_variable();
			n.translation += "\t" + label + " = " + n.label + ";\n";

			n.label = label;
			variables.push_back({label,to_ir_type(n.type)});
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

node gen_expr(node& l, const op& op, node& r){
    materialize(l);
    materialize(r);

    node n;

    // string + string = concatenação
    // Futuramente abstrair tudo tipo de operação daqui
	if(l.type == "string" && r.type == "string"){
		if(op.label == "+")
		{	n.type    = "string";
			n.ir_type = "char*";
			n.label   = gen_tmp_variable();
			variables.push_back({n.label, n.ir_type});
			n.translation  = l.translation + r.translation;
			n.translation += "\t" + n.label + " = (char*) malloc(4096);\n";
			n.translation += "\tstrcpy(" + n.label + ", " + l.label + ");\n";
			n.translation += "\tstrcat(" + n.label + ", " + r.label + ");\n";
			n.is_materialized = true;
			return n;
		}
		else{
			report_error("Não existe operação " + op.label + " entre tipos " + l.type + ", " + r.type);
			exit(1);
		}
    }

    // operação lógica só com bool
    if((op.label == "&&" || op.label == "||") && 
       (l.type != "bool" && r.type != "bool")){
        report_error("Operação lógica precisa de operandos do tipo boolean -> (" + l.type + "," + r.type + ")");
    }

    // resto normal
    coercion(l, r);
    n.type    = l.type;
    n.ir_type = l.ir_type;
    materialize(n);
    n.translation  = l.translation + r.translation;
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
	if((!is_numeric(l) || !is_numeric(r)) ){
		if(l == "bool" && r == "bool") return;
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

string to_ir_type(const string& type){
	if(type == "bool") return "int";
	if(type == "string") return "char*";
	return type;

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

		variables.push_back({label,to_ir_type(type)});
        
		n.ir_type = to_ir_type(type);
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
	context_stack.push_back({ContextType::LOOP, cur_depth, label_start, label_end, "", {}});
}

void open_switch(node & expr){
	string label_start = gen_label_loop();
	string label_end = gen_label_loop();
	context_stack.push_back({ContextType::SWITCH, cur_depth, "", label_end, "",expr});
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