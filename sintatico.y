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
	#include <filesystem>
	#include "tokens.hh"
	#include "loops.hh"
	#include <unordered_set>
	using namespace std;


	yy::parser::symbol_type yylex();

	////*** Variáveis externas ***////
	extern FILE* yyin;
	extern int yylineno;

	////*** Variáveis globais  ***////
	int tmp_var_count = 0;
	int cur_depth = 0;
	
	unordered_set<string> imported_files;

	string code;
	string functions_code;
	string structs_code;
	string include_code;

	vector<pair<string,string>> variables;
	
	////***  Funções***////
	struct func_data 
	{
		string name;
		string return_type; 
		string ir_return_type; 
		vector<pair<string,string>> variables;  // Não uso
		int saved_tmp_count = 0; // Queria que as variaveis locais usagem t1, t2, t2, ..., tn
		vector<pair<string,string>> params;
		string translation; // corpo da função
	};
	
	void open_function(const string& name);
	string close_function(); // Tira função da pilha e retornar function_code da função no topo
	map<string, func_data> functions; // "Tabela" das funções

	/////*** Struct ***/////
	struct cell_attr // Nome e tipo da cada campo da struct
	{
		string name;
		string type;
	};

	struct body_attr // nome e todos os atributos
	{
		string name;
		vector<cell_attr> cells;
	};
	vector<cell_attr> current_cells;
	map<string, body_attr> structs;



	struct include_unit // Basicamente vai guardar as funções e structs do arquivos importados
	{
		string functions_code;
		string structs_code;
	};
	string pre_process(string file);
	
	////*** Pilhas ***////
	vector<map<string,shared_ptr<symbol>>> scope_stack;
	vector<loopInfo> loop_stack;
	vector<Context> context_stack;
	vector<node> switch_stack;
	vector<string> switch_end_stack;
	vector<func_data> function_stack; // Pilha para saber a função atual
	vector<unordered_set<string>> allocated_stack; // Para dar free nas variaveis alocadas


	////*** Geradores de código  ***////
	string gen_tmp_variable();
	string gen_declarations(); 
	string gen_functions();
	string gen_assignment(node &l, node& r);
	int label_loop_number = 0;
	string gen_label_loop(){
		return "L"+ to_string(label_loop_number++) ;
	} 
	
	void materialize(node& n); // Separar?

	void gen_literal(node& n, const string& type, const string& literal);
	node gen_unary(const string& side, const op& op, node& t);
	node gen_expr(node& l, const op& op, node& r);

	////*** Funções auxiliares: temporários***////
	shared_ptr<symbol> lookup_symbol(const string& name);
	
	// Funções responsaveis pelo escopo //
	void open_block();
	void close_block();
	void open_loop();
	void open_switch(node & expr);
	void push_variables(const string& label, const string& ir_type);

	void register_allocated_label(const string& name);

	Context *get_back_loop();
	Context *get_back_switch();

	void register_symbol(const string& name, shared_ptr<symbol> sym);
	
	
	string to_ir_type(const Type& type);
	
	////*** Funções auxiliares: conversão ***////
	bool is_numeric(const Type& t);
	void check_conversion(const Type& l, const Type& r);
	node conversion(node& t, const Type& type);
	void coercion(node& l, node& r);
	node casting(node& t, const string& type);

	////*** Funções auxiliares: inferência ***////
	void promote_symbol(node& n, const Type& type);

	////*** Funções auxiliares: debug ***////
	void report_error(const string& msg);
}

/*** Declaração de tokens ***/
%token <std::string> TK_INT TK_FLOAT TK_CHAR TK_STRING TK_BOOL TK_TYPE TK_VAR TK_CAST TK_VECTOR
%token <std::string> TK_SBLOCK TK_EBLOCK TK_IF TK_ELSE TK_WHILE TK_DO TK_BREAK TK_FOR TK_IN TK_RANGE
%token <std::string> TK_CONTINUE TK_CASE TK_SWITCH TK_DEFAULT TK_PRINT TK_PRINTL TK_INPUT
%token <std::string> TK_FUNCTION TK_RETURN 

%token <std::shared_ptr<symbol>> TK_ID

%token <op> OP_ADD OP_MINUS OP_MULT OP_DIV OP_MOD
%token <op> OP_EQ OP_NE OP_LE OP_GE OP_LT OP_GT
%token <op> OP_OR OP_AND OP_NOT

/*** Declaração de nódulos ***/
%type <node> COMMANDS STATEMENT DECLARATION ASSIGNMENT LVAL RVAL EXPR BLOCK ARRVAL ARRVAL_
%type <node> CONDITIONAL LOOPCONTROL SWITCHBLOCK CASE_ITEM DEFAULT CASE_LIST LOOP OPT_ASSIGNMENT
%type <node> IO FOR_DECLARATION PRINT_LIST FUNCTION_DEF PARAMS_LIST PARAM CALL_FUNC RETURN ARGS_LIST ARG
%type <node> STRUCT_DEF CELL_LIST CELL TYPE_ANNOTATION FIELD_LIST 

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
				code = 
				"#include <stdio.h>\n"
				"#include <string.h>\n"
				"#include <stdlib.h>\n\n";
				code += structs_code;
				code += functions_code;
				code += "int main(void) {\n";
				code += gen_declarations();
				code += "\n" + $1.translation;
				for(const auto& label : allocated_stack.front()){
        			code += "\tfree(" + label + ");\n";
    			}
				code += "\treturn 0;\n}\n";
			};

COMMANDS 	: COMMANDS STATEMENT {$$.translation = $1.translation + $2.translation;}
			| STATEMENT 		 {$$.translation = $1.translation;};
			

STATEMENT 	: DECLARATION ';' {$$.translation = $1.translation;}
			| ASSIGNMENT  ';' {$$.translation = $1.translation;}
			| BLOCK			  {$$.translation = $1.translation;}
			| CONDITIONAL	  {$$.translation = $1.translation;}
			| LOOP 			  {$$.translation = $1.translation;}
			| LOOPCONTROL     {$$.translation = $1.translation;}
			| IO		      {$$.translation = $1.translation;}
			| FUNCTION_DEF	  {$$.translation = $1.translation;}
			| RETURN		  {$$.translation = $1.translation;}
			| CALL_FUNC       {$$.translation = $1.translation;}
			| STRUCT_DEF 	  {$$.translation = $1.translation;}
			
			;

/*
	
*/
TYPE_ANNOTATION	: TK_TYPE {$$.type = Type($1); $$.translation = "";}
			
				| TK_VECTOR OP_LT TK_TYPE OP_GT
				{
					$$.type = Type($3);
					$$.type.kind = Type::Kind::ARRAY;
					$$.translation = "";
				}

				// TIPO STRUCT
				| TK_ID 
				{
					auto it = structs.find($1->name);
					if(it == structs.end()){
                    report_error("Tipo '" + $1->name + "' não é uma struct conhecida."); // Temos que padronizar as mensagens de erros...
               		}
					$$.type = Type($1->name);
					$$.type.kind = Type::Kind::STRUCT;
					$$.translation = "";
				}
				;

DECLARATION : TK_VAR TK_ID
			{
				$2->type = Type("undefined");
				$2->is_static = false;
				$$.translation = "";
				register_symbol($2->name, $2);
			}

			| TK_VAR TK_ID ':' TYPE_ANNOTATION
			{

				$2->type = $4.type;
				$2->is_static = true;
				if($4.type.kind == Type::Kind::STRUCT){
					$2->label = gen_tmp_variable();
                	push_variables($2->label, "struct " + $4.type.base);   // tipo IR é "struct Nome"
				}
				register_symbol($2->name, $2);
				$$.translation = "";

			}
			
			;

ASSIGNMENT : LVAL OP_AT RVAL
			{
				if($1.is_static) {
					if($3.type != $1.type)
						report_error("Variavel '" + $1.label + "' do tipo estatico '" + $1.type.base + "' recebendo outro tipo '" + $3.type.base + "'");
				}

				materialize($3);
				promote_symbol($1, $3.type);
				materialize($1);

				$$.translation = $1.translation;
				$$.translation += $3.translation;
				$$.translation += gen_assignment($1, $3);
			}
			
			| TK_VAR TK_ID OP_AT RVAL
			{
				materialize($4);
				$2->is_static = false;
				$2->type = $4.type;
				$2->type.array_size = $4.elements.size();
				$2->label = gen_tmp_variable();
				push_variables($2->label, to_ir_type($2->type));
				register_symbol($2->name, $2);

				// TK_ID não é um nó
				node dest;
				dest.label = $2->label;
				dest.type  = $2->type;
				dest.is_materialized = true;

				$$.translation  = $4.translation;
				$$.translation += gen_assignment(dest, $4);
			}

			| TK_VAR TK_ID ':' TYPE_ANNOTATION OP_AT RVAL
			{
				materialize($6);

				if($4.type.kind != $6.type.kind || $4.type.base != $6.type.base)
					if($6.type.base != "cell_struct") {
						report_error("Variável '" + $2->name + "' do tipo '" + $4.type.base +
								"' recebendo tipo '" + $6.type.base + "'");
					}
				$2->type = $4.type;
				$2->type.array_size = $6.elements.size();
				$2->is_static = true;
				$2->label = gen_tmp_variable();
				push_variables($2->label, to_ir_type($2->type));
				register_symbol($2->name, $2);

				node dest;
				dest.label = $2->label;
				dest.type  = $2->type;
				dest.is_materialized = true;

				$$.translation  = $6.translation;
				$$.translation += gen_assignment(dest, $6);
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


STRUCT_DEF 		: TK_ID TK_SBLOCK CELL_LIST TK_EBLOCK ';'
				{
					body_attr obj;
					obj.name = $1->name;
					obj.cells = current_cells;
					structs[$1->name] = obj;
					current_cells.clear();

					// Gerar codigo da struct
					structs_code += "struct " + obj.name + "{\n";
						for(auto &c : obj.cells){
							structs_code += "\t" +  to_ir_type(Type(c.type)) + " " + c.name + ";\n";
						}
						structs_code += "};\n\n";

					$$.translation = "";
				}
			;

CELL_LIST		: CELL_LIST CELL {$$.translation = ""; }
				| CELL			 {$$.translation = ""; }
			;

CELL 		: TK_ID ':' TK_TYPE ';'
			{
				current_cells.push_back({$1->name, $3});
				$$.translation = "";
			}
			;


FUNCTION_DEF	: TK_FUNCTION TK_ID '(' 
			{
				open_function($2->name);
			} PARAMS_LIST ')' ':' TK_TYPE
			{
				// Tipo
				function_stack.back().return_type = $8;
				function_stack.back().ir_return_type = to_ir_type($8);


				// Adicionando a função na "tabela"
				func_data f;
				f.name = $2->name; 
				f.params = function_stack.back().params;
				f.return_type = $8;
				f.ir_return_type = to_ir_type($8);
				functions[$2->name] = f;

			} BLOCK
			{
				function_stack.back().translation = $10.translation;
				functions_code += close_function();
				$$.translation = "";
			}

	;

PARAMS_LIST : PARAMS_LIST ',' PARAM { $$.translation = ""; }
           | PARAM                 { $$.translation = ""; }
           | /* vazio */            { $$.translation = ""; }
           ;

PARAM 		: TK_ID ':' TK_TYPE
			{
				$1->type      = $3;
				$1->is_static = true;
				$1->label     = gen_tmp_variable();       
				register_symbol($1->name, $1);
				function_stack.back().params.push_back({$1->label, $3});
				$$.translation = "";
			}
			;	

RETURN		: TK_RETURN ';'
			{	
				$$.translation = "\treturn;\n"; 

			}
			| TK_RETURN RVAL ';' 
			{
				materialize($2);
				$$.translation = $2.translation;
				$$.translation += "\treturn " + $2.label + ";\n";
			}

// USADO QUANDO CHAMA A FUNÇÃO SEM ATRIBUIR À UMA VARIAVEL!!!
CALL_FUNC	: TK_ID '(' ARGS_LIST ')' ';'
			{
              auto it = functions.find($1->name);
              if(it == functions.end()){
                  report_error("Função '" + $1->name + "' não declarada.");
                  $$.translation = "";
              }
              else {
                  $$.translation = $3.translation;
                  // chama a função mas não guarda o retorno
                  $$.translation += "\t" + $1->name + "(" + $3.label + ");\n";
              }
          }
		  ;

ARGS_LIST	: ARGS_LIST ',' ARG 
			{ 
				$$.translation = $1.translation + $3.translation;
				$$.label = $1.label + ", " + $3.label;
			}

           | ARG                 { $$.translation = $1.translation; $$.label = $1.label;}

           | /* vazio */         { $$.translation = ""; }
           ;

ARG 		: EXPR	{materialize($1); $$.translation = $1.translation; $$.label = $1.label;}
			;

BLOCK : 	TK_SBLOCK { open_block(); } COMMANDS TK_EBLOCK
			{	
				auto scope_to_free = allocated_stack.back();
				close_block();

				$$.translation = $3.translation;
				for(const auto& label : scope_to_free){
					$$.translation += "\tfree(" + label + ");\n";
				}
			}

			| TK_SBLOCK{open_block();} TK_EBLOCK
			{
				close_block();
				$$.translation = "";
			}
			;

CONDITIONAL : TK_IF '(' EXPR ')' BLOCK TK_ELSE BLOCK
			{
				string label_if = gen_label_loop();
				string label_else = gen_label_loop();

				materialize($3);
				$$.translation = $3.translation;

				$$.translation += "\tif(!" + $3.label + ") " + "goto " + label_else + ";\n";
				$$.translation += $5.translation + "\n";
				$$.translation += "\tgoto " + label_if + ";\n";
				$$.translation += label_else + ":" + "\n" + $7.translation + "\n";
				$$.translation += label_if + ":\n";
			}
			| TK_IF '(' EXPR ')' BLOCK 
			{
				string label_final = gen_label_loop();
				$$.translation = $3.translation;
				$$.translation += "\tif(!" + $3.label + ") " + "goto " + label_final + ";\n";
				$$.translation += $5.translation;
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
				$$.translation += $7.jumps;
				$$.translation += "\tgoto " + end_label + ";\n";
				$$.translation += $7.labels_jumps;
				$$.translation += end_label + ":\n";
				
				context_stack.pop_back();	
			}
			;

OPT_ASSIGNMENT : ASSIGNMENT  {$$ = $1;}
               | /* vazio */ {$$.translation = "";}
               ;

FOR_DECLARATION : TK_ID
			{
				auto ini = lookup_symbol($1->name);
				if(ini) {
					if(!ini->label.empty()) {
						$1->label = ini->label;
					} else {
						ini->label = gen_tmp_variable();
						push_variables(ini->label, "int");
						$1->label = ini->label;
					}

					if(ini->is_static == true && ini->type.base != "int") {
						report_error("variavel " + ini->name + " é estatica do tipo " + ini->type.base + "\n;");
						return 0;
					}

					ini->type = Type("int");
					$1->type  = Type("int");
					$1->is_static = ini->is_static;
				} else {
					$1->label     = gen_tmp_variable();
					$1->type      = Type("int");
					$1->is_static = true;
					push_variables($1->label, "int");
					register_symbol($1->name, $1);
				}

				$$.label           = $1->label;
				$$.type            = $1->type;
				$$.is_static       = $1->is_static;
				$$.is_materialized = true;
				$$.translation     = "";
			}

LOOP		: TK_WHILE '(' EXPR ')' {open_loop();} BLOCK
			{	
				materialize($3);
				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;
				string label_continue = get_back_loop()->continue_label;

				$$.translation = label_start + ":\n";
				$$.translation += $3.translation;
				$$.translation += "\tif(!" + $3.label + ") goto " + label_end + ";\n";
				$$.translation += $6.translation;
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

				$$.translation = "\tgoto " + label_jump + ";\n";
				$$.translation += label_start + ":\n";
				$$.translation += $6.translation;
				$$.translation += "\tif(!" + $6.label + ") goto " + label_end + ";\n";
				$$.translation += label_jump + ":\n";
				$$.translation += $3.translation;
				if(label_continue != "") $$.translation += label_continue + ":\n";
				$$.translation += "\tgoto " + label_start + ";\n";
				$$.translation += label_end + ":\n";
				context_stack.pop_back();
			}

			| TK_FOR '(' {open_block();} OPT_ASSIGNMENT {open_block();} ';' EXPR ';' OPT_ASSIGNMENT ')' {open_loop();} BLOCK
			{
				materialize($7);

				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;

				$$.translation += $4.translation;
				$$.translation += label_start + ":\n";
				$$.translation += $7.translation;
				$$.translation += "\tif(!" + $7.label + ") goto " + label_end + ";\n";
				$$.translation += $12.translation;
				$$.translation += $9.translation;
				$$.translation += "\tgoto " + label_start + ";\n";
				$$.translation += label_end + ":\n";
				context_stack.pop_back();
			}

			| TK_FOR FOR_DECLARATION TK_IN TK_RANGE '(' EXPR ',' EXPR ')' {open_loop();} BLOCK
			{
				materialize($6);
				materialize($8);

				if($6.type.base != "int" || $8.type.base != "int") {
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
				
				node cond = gen_expr($2, op_lt, $8);
				$$.translation += cond.translation;

				$$.translation += "\tif(!" + cond.label + ") goto " + label_end + ";\n";
				$$.translation += $11.translation;
				if(label_continue != "") $$.translation += label_continue + ":\n";
				$$.translation += "\t" + $2.label + " = " + $2.label + " + 1;\n"; 
				$$.translation += "\tgoto " + label_start + ";\n";
				$$.translation += label_end + ":\n";
				context_stack.pop_back();
			}
			;

LOOPCONTROL : TK_BREAK ';'
			{
				if(context_stack.empty()) {
					report_error("Break fora de loop");
					return 0;
				}
				$$.translation = "\tgoto " + context_stack.back().end_label + ";\n";
			}
			| TK_BREAK TK_INT ';'
			{
				int n = stoi($2);
				if(n < 1) {
					report_error("numero n invalido\n");
					return 0;
				}
				if(context_stack.size() < (size_t)n) {
					report_error("Break n é maior que a quantidade de loops\n");
					return 0;
				}
				auto& l = context_stack[context_stack.size() - n];
				$$.translation = "\tgoto " + l.end_label + ";\n";
			}
			| TK_CONTINUE ';'
			{
				if(get_back_loop() == nullptr) {
					report_error("Continue fora de loop");
				}
				get_back_loop()->continue_label = gen_label_loop();
				$$.translation = "\tgoto " + get_back_loop()->continue_label + ";\n";
			}
			;

SWITCHBLOCK	: CASE_LIST
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

CASE_LIST 	: CASE_LIST CASE_ITEM 
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

CASE_ITEM 	: TK_CASE EXPR ':' BLOCK
			{
				string L_case = gen_label_loop();
				string end_label = get_back_switch()->end_label;
				
				materialize($2);

				op op_eq;
				op_eq.label = "==";
				node current_switch = get_back_switch()->switch_node;
				node cmp_value = gen_expr(current_switch, op_eq, $2);
				
				$$.jumps = cmp_value.translation;
				$$.jumps += "\tif(" + cmp_value.label + ") goto " + L_case + ";\n";
				$$.labels_jumps = L_case + ":\n" + $4.translation + "\tgoto " + end_label + ";\n";
			}
			;

DEFAULT		: TK_DEFAULT ':' BLOCK
			{
				string L_default = gen_label_loop();
				string end_label = get_back_switch()->end_label;

				$$.jumps = "\tgoto " + L_default + ";\n";
				$$.labels_jumps = L_default + ":\n" + $3.translation;
			}
			;

IO			: TK_PRINT '(' PRINT_LIST ')' ';'
			{	
				$$.translation = $3.translation;
			}
			| TK_PRINTL '(' PRINT_LIST ')' ';'
			{	
				$$.translation = $3.translation;
				$$.translation += "\tprintf(\"\\n\");\n";
			}
			| TK_INPUT '(' EXPR ')' ';'
			{	
				string fmt;
				if($3.type.base == "undefined") {
					promote_symbol($3, Type("string"));
					$3.type = Type("string");
				}
				materialize($3);
				if($3.type.base == "string") fmt = "\"%s\", "  + $3.label;
				if($3.type.base == "int")    fmt = "\"%d\", &" + $3.label;
				if($3.type.base == "float")  fmt = "\"%f\", &" + $3.label;
				if($3.type.base == "char")   fmt = "\"%c\", &" + $3.label;
				if($3.type.base == "bool")   fmt = "\"%i\", &" + $3.label;
				$$.translation = $3.translation;
				$$.translation += "\tscanf(" + fmt + ");\n";
			}

PRINT_LIST 	: EXPR ',' PRINT_LIST 
			{
				materialize($1);
				string type;
				if($1.type.base == "string") type = "\"%s\"";
				if($1.type.base == "int")    type = "\"%d\"";
				if($1.type.base == "float")  type = "\"%f\"";
				if($1.type.base == "char")   type = "\"%c\"";
				if($1.type.base == "bool")   type = "\"%i\"";
				$$.translation = $1.translation;
				$$.translation += "\tprintf(" + type + ", " + $1.label + ");\n";
				$$.translation += $3.translation;
			}
			| EXPR 
			{
				materialize($1);
				string type;
				if($1.type.base == "string") type = "\"%s\"";
				if($1.type.base == "int")    type = "\"%d\"";
				if($1.type.base == "float")  type = "\"%f\"";
				if($1.type.base == "bool")   type = "\"%i\"";
				if($1.type.base == "char")   type = "\"%c\"";
				$$.translation = $1.translation;
				$$.translation += "\tprintf(" + type + ", " + $1.label + ");\n";	
			}
			;

LVAL 		: TK_ID 
			{
				auto sym = lookup_symbol($1->name);
				if(!sym) {
					report_error("Variável '" + $1->name + "' não declarada.");
				}
				$$.type      = sym->type;
				$$.label     = sym->name;
				$$.is_static = sym->is_static;
				$$.translation = "";
			}
			// MEU AMIGO ME AJUDOU
			| TK_ID '[' EXPR ']'
            {
                auto sym = lookup_symbol($1->name);
                if(!sym)
                    report_error("Variável '" + $1->name + "' não declarada.");
                    
                // Permite indexar se for ARRAY ou STRING
                if(sym->type.kind != Type::Kind::ARRAY && sym->type.base != "string")
                    report_error("Variável '" + $1->name + "' não é um array nem string.");

                if(sym->label.empty()) {
                    sym->label = gen_tmp_variable();
                    push_variables(sym->label, to_ir_type(sym->type));
                }
                materialize($3);

                $$.label     = sym->label + "[" + $3.label + "]";
                
                // Se a variável original for string, o destino da escrita é um 'char'
                if (sym->type.base == "string") {
                    $$.type = Type("char");
                } else {
                    $$.type = Type(sym->type.base);
                }
                
                $$.is_static = sym->is_static;
                $$.is_materialized = true; 
                $$.translation = $3.translation;
            }

			| TK_ID '.' TK_ID
            {
                auto sym = lookup_symbol($1->name);
                if(!sym) report_error("Variável '" + $1->name + "' não declarada.");

                // Buscar a struct pelo tipo base, não pelo nome da variavel
                auto &obj = structs[sym->type.base]; 
                string cell_type = "undefined";
                for(auto &c : obj.cells)
                    if(c.name == $3->name) cell_type = c.type;

                $$.label     = sym->label + "." + $3->name;
                $$.type      = Type(cell_type);
                
                $$.is_static = true; 
                $$.is_materialized = true; 
                
                $$.translation = "";
            }
			;

RVAL 		: EXPR {$$ = $1;}
			| TK_SBLOCK FIELD_LIST TK_EBLOCK { $$ = $2; }
			| '[' ARRVAL ']' {$$ = $2;};
			;
ARRVAL      : ARRVAL_ {$$ = $1;}
			| /* vazio */ { $$.type = Type(); $$.type.kind = Type::Kind::ARRAY; } // tem que ver isso ai

FIELD_LIST	: FIELD_LIST ',' EXPR
			{	
				materialize($3);
				$$.type = Type("cell_struct");
				$$.elements = $1.elements;
				$$.elements.push_back($3.label);
				$$.translation = $1.translation + $3.translation;				
			}
			| EXPR 
			{
				materialize($1);
				$$.elements.push_back($1.label);
				$$.translation = $1.translation;
				$$.type = Type("cell_struct");
			}
			;
ARRVAL_     : ARRVAL_  ',' EXPR
			{
				materialize($1);
				if($1.type.base != $3.type.base)
                	report_error("Elementos do array com tipos diferentes: " + $1.type.base + " e " + $3.type.base);

				$$.type = $1.type;
				$$.translation = $1.translation + $3.translation;
				$$.elements = $1.elements;
				$$.elements.insert($$.elements.begin(), $3.label);
			}
			| EXPR 
			{
				materialize($1);
				$$.type = Type($1.type.base);
				$$.type.kind = Type::Kind::ARRAY;
				$$.translation = $1.translation;
				$$.elements.push_back($1.label);

			}
			;

EXPR 		: EXPR OP_ADD  	EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_MINUS EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_MULT 	EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_DIV 	EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_MOD 	EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_EQ EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_NE EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_LE EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_GE EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_LT EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_GT EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_OR  EXPR {$$ = gen_expr($1,$2,$3);}
			| EXPR OP_AND EXPR {$$ = gen_expr($1,$2,$3);}
			| OP_NOT EXPR  {$$ = gen_unary("left",$1,$2);}
			| TK_CAST EXPR {$$ = casting($2,$1);}
			| '(' EXPR ')' {$$ = $2;}
			| TK_INT   	{gen_literal($$,"int",$1);}
			| TK_FLOAT 	{gen_literal($$,"float",$1);}
			| TK_CHAR	{gen_literal($$,"char",$1);}
			| TK_BOOL	{gen_literal($$,"bool", $1);}
			| TK_STRING {gen_literal($$, "string", $1);}
			| TK_ID 
			{
				auto sym = lookup_symbol($1->name);
				if(!sym) {
					report_error("Variável '" + $1->name + "' não declarada.");
				}
				$$.label     = sym->name;
				$$.type      = sym->type;
				$$.is_static = sym->is_static;
				$$.translation = "";
			}
			// AMIGO
			| TK_ID '[' EXPR ']'
            {
                auto sym = lookup_symbol($1->name);
                if(!sym) {
                    report_error("Variável '" + $1->name + "' não declarada.");
                }
                
                // Permite indexar se for ARRAY ou STRING
                if(sym->type.kind != Type::Kind::ARRAY && sym->type.base != "string"){
                    report_error("Variável '" + $1->name + "' não é um array nem string.");
                }
                materialize($3);

                $$.label       = gen_tmp_variable();
                
                // Se a variável original for string, cada índice lido é um 'char'
                if (sym->type.base == "string") {
                    $$.type = Type("char");
                } else {
                    $$.type = Type(sym->type.base);
                }
                
                $$.is_static   = sym->is_static;
                $$.translation = $3.translation;
                
                push_variables($$.label, to_ir_type($$.type));
                $$.translation += "\t" + $$.label + " = " + sym->label + "[" + $3.label + "];\n"; 
            }

			| TK_ID '(' ARGS_LIST ')'
				{
					auto it = functions.find($1->name);
					if(it == functions.end()){
						report_error("Função '" + $1->name + "' não declarada.");
					}

					else {
						$$.type  = Type(it->second.return_type);
						$$.label = gen_tmp_variable();
						push_variables($$.label, it->second.ir_return_type);

						$$.translation  = $3.translation;
						$$.translation += "\t" + $$.label + " = " + it->second.name + "(" + $3.label + ");\n";
					}
				}
     		| TK_ID '.' TK_ID
       		{
				auto sym = lookup_symbol($1->name);
				if(!sym) report_error("Variável '" + $1->name + "' não declarada.");

				auto& obj = structs[sym->type.base];
				string cell_type = "undefined";
				for(auto& c :  obj.cells)
					if(c.name == $3->name) cell_type = c.type;

				$$.label     = sym->label + "." + $3->name;
				$$.type      = Type(cell_type);
				$$.translation = "";
		    }
			
		;

%%

void gen_literal(node& n, const string& type, const string& literal) {
	n.label = literal;
	n.type  = Type(type);
	n.translation = "";
}

void materialize(node& n) {
	if(!n.is_materialized) {
		auto sym = lookup_symbol(n.label);
		if(sym) {
			if(sym->type.base == "undefined")
				report_error("Variável '" + sym->name + "' usada sem ser inicializada.");
			if(!sym->label.empty()) n.label = sym->label;
			else {
				string label = gen_tmp_variable();
				sym->label = label;
				n.label = label;
				push_variables(label, to_ir_type(n.type));
				if(sym->type.base == "string") {
					n.translation += "\t" + label + " = (char*) malloc(4096);\n";
					n.translation += "\t" + label + "[0] = '\\0';\n";
				}
			}
		} else if(n.translation.empty()) {
			string label = gen_tmp_variable();
			n.translation += "\t" + label + " = " + n.label + ";\n";
			n.label = label;
			push_variables(label, to_ir_type(n.type));
		}
		n.is_materialized = true;
	}
}

string gen_tmp_variable() {
	tmp_var_count++;
	return "t" + to_string(tmp_var_count);
}

string gen_declarations() {
	string decl;
	for(const auto& var : variables)
		decl += "\t" + var.second + " " + var.first + ";\n";
	return decl;
}

string gen_functions() {
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

string gen_assignment(node &l, node& r){
	string node_translation;
	// ARRAY
	if(r.type.kind == Type::Kind::ARRAY) {
		l.type.array_size = r.elements.size();
		node_translation += "\t" + l.label + " = (" + l.type.base + "*)";
		node_translation += " malloc(" + to_string(l.type.array_size) + " * sizeof(" + r.type.base + "));\n";
		register_allocated_label(l.label);
		for(int i = 0; i < l.type.array_size; i++){
			node_translation += "\t" + l.label + "[" + to_string(i) + "] = " + r.elements[i] + ";\n";
		}
	}

	// Struct
	if(r.type.base == "cell_struct"){
		auto it = structs.find(l.type.base);
		if(it == structs.end()){
			report_error("Tipo '" +  l.type.base + "' não é uma struct conhecida."); // Temos que padronizar as mensagens de erros...
			return "";
		}
		auto &obj = it->second;
		if(r.elements.size() != obj.cells.size()){
            report_error("Struct '" + l.type.base + "' tem " +
                    to_string(obj.cells.size()) + " campos, mas recebeu " +
                    to_string(r.elements.size()) + ".");
            return "";
		}
			/// é aqui mesmo!!!
			/// é aqui mesmo!!!
			/// é aqui!!!!!!!! mesmo!!!
			/// é aqui mesmo!!!
		for(int i = 0; i < obj.cells.size(); i++)
            node_translation += "\t" + l.label + "." + obj.cells[i].name + " = " + r.elements[i] + ";\n";
    	return node_translation;

	}
	else if(r.type.base == "string") {
		node_translation += "\t" + l.label + " = (char*) malloc(4096);\n";
		register_allocated_label(l.label);
		node_translation += "\tstrcpy(" + l.label + ", " + r.label + ");\n";
	}

	else {
		node_translation = "\t" + l.label + " = " + r.label + ";\n";
	}

	return node_translation;
}

node gen_expr(node& l, const op& op, node& r) {
	materialize(l);
	materialize(r);

	node n;

	if(l.type.base == "string" && r.type.base == "string") {
		if(op.label == "+") {
			n.type  = Type("string");
			n.label = gen_tmp_variable();
			push_variables(n.label, "char*");
			n.translation  = l.translation + r.translation;
			n.translation += "\t" + n.label + " = (char*) malloc(4096);\n";
			n.translation += "\tstrcpy(" + n.label + ", " + l.label + ");\n";
			n.translation += "\tstrcat(" + n.label + ", " + r.label + ");\n";
			n.is_materialized = true;
			return n;
		} else {
			report_error("Não existe operação " + op.label + " entre tipos " + l.type.base + ", " + r.type.base);
			exit(1);
		}
	}

	if((op.label == "&&" || op.label == "||") &&
	   (l.type.base != "bool" && r.type.base != "bool"))
		report_error("Operação lógica precisa de operandos do tipo boolean -> (" + l.type.base + "," + r.type.base + ")");

	coercion(l, r);
	n.type = l.type;
	materialize(n);
	n.translation  = l.translation + r.translation;
	n.translation += "\t" + n.label + " = " + l.label + " " + op.label + " " + r.label + ";\n";
	return n;
}

node gen_unary(const string& side, const op& op, node& t) {
	materialize(t);
	node n;
	n.type = t.type;
	materialize(n);
	n.translation = t.translation;
	if(side == "left")
		n.translation += "\t" + n.label + " = " + op.label + t.label + ";\n";
	else
		n.translation += "\t" + n.label + " = " + t.label + op.label + ";\n";
	return n;
}

bool is_numeric(const Type& t) { return t.base == "int" || t.base == "float"; }

void check_conversion(const Type& l, const Type& r) {
	if (l == r) {
        return;
    }
	if(!is_numeric(l) || !is_numeric(r)) {
		if(l.base == "bool" && r.base == "bool") return;
		report_error("Conversão não permitida entre tipos (" + l.base + ") e (" + r.base + ")");
	}
}

node conversion(node& t, const Type& type) {
	node n;
	n.type = type;
	materialize(n);
	n.translation  = t.translation;
	n.translation += "\t" + n.label + " = (" + type.base + ") " + t.label + ";\n";
	return n;
}

void coercion(node& l, node& r) {
	check_conversion(l.type, r.type);
	if(l.type.base == "float" && r.type.base == "int")
		r = conversion(r, Type("float"));
	else if(l.type.base == "int" && r.type.base == "float")
		l = conversion(l, Type("float"));
}

node casting(node& t, const string& type) {
	materialize(t);
	if(t.type.base == type) return t;
	check_conversion(t.type, Type(type));
	return conversion(t, Type(type));
}

void promote_symbol(node& n, const Type& type) {
	auto sym = lookup_symbol(n.label);
	if(!n.is_static && sym->type != type) {
		string label = gen_tmp_variable();
		sym->label = label;
		sym->type  = type;
		push_variables(label, to_ir_type(type));
		n.label = label;
		n.type  = type;
		n.is_materialized = true;
	}
}

void register_allocated_label(const string& name) {
	if(allocated_stack.back().count(name))
		return;
	else
		allocated_stack.back().insert(name);
}

void open_block() {
	cur_depth++;
	scope_stack.push_back({});
	allocated_stack.push_back({});
}

void close_block() {
	scope_stack.pop_back();
	allocated_stack.pop_back();
	cur_depth--;
}

void open_loop() {
	string label_start = gen_label_loop();
	string label_end = gen_label_loop();
	context_stack.push_back({ContextType::LOOP, cur_depth, label_start, label_end, "", {}});
}

void open_switch(node& expr) {
	string label_start = gen_label_loop();
	string label_end = gen_label_loop();
	context_stack.push_back({ContextType::SWITCH, cur_depth, "", label_end, "", expr});
}

Context* get_back_loop() {
	for(auto it = context_stack.rbegin(); it != context_stack.rend(); ++it)
		if(it->type == ContextType::LOOP) return &(*it);
	return nullptr;
}

Context* get_back_switch() {
	for(auto it = context_stack.rbegin(); it != context_stack.rend(); ++it)
		if(it->type == ContextType::SWITCH) return &(*it);
	return nullptr;
}

// Agora a gente verifica se a label é de um função(topo) ou main
void push_variables(const string& label, const string& ir_type){
    if(!function_stack.empty())
        function_stack.back().variables.push_back({label, ir_type});
    else
        variables.push_back({label, ir_type});
}

void open_function(const string& name){
	func_data f;
	f.name = name;
	f.saved_tmp_count = tmp_var_count;
	function_stack.push_back(f);
	
	tmp_var_count = 0;
	open_block();
}

// Tira a função da pilha e retornar o codigo da string
string close_function(){
	func_data f = function_stack.back();
	function_stack.pop_back();
	close_block();

	// Assinatura func id(a, b, ...,)
	string def = f.ir_return_type + " " +  f.name + "(";
	for(int i = 0; i < f.params.size(); i++){
		if(i > 0) def += ", ";
		def += to_ir_type(f.params[i].second) + " " + f.params[i].first;
	}
	def += "){\n";

	// declaração das variaveis usadas
	string decl;
	for( auto &v : f.variables){
		// Vou materializar aqui pois achei mais simples a primeiro momento
		
		decl += "\t" + v.second + " " + v.first + ";\n";
	}

	tmp_var_count = f.saved_tmp_count;
	return def + decl + f.translation + "}\n\n";
}




shared_ptr<symbol> lookup_symbol(const string& name) {
	for(auto it = scope_stack.rbegin(); it != scope_stack.rend(); ++it) {
		auto found = it->find(name);
		if(found != it->end()) return found->second;
	}
	return nullptr;
}

void register_symbol(const string& name, shared_ptr<symbol> sym) {
	if(scope_stack.back().count(name))
		report_error("Variavel '" + name + "' já declarada nesse escopo.");
	else
		scope_stack.back().try_emplace(name, sym);
}


/* 	
	Basicamente pega o programa.sk e le todo
	Onde tiver import ele pega e processa esse arquivo também.
	No final temos a junção do programa.sk + todos os importes no topo.
*/
string preprocess(const string& file)
{
    if(imported_files.count(file))
        return "";

    imported_files.insert(file);

    ifstream in(file);

    if(!in)
    {
        report_error("Arquivo '" + file + "' não encontrado.");
        return "";
    }

    string result;
    string line;

    while(getline(in, line))
    {
        if(line.rfind("import <", 0) == 0)
        {
            size_t ini = line.find('<');
            size_t fim = line.find('>');

            string imported =
                line.substr(ini + 1, fim - ini - 1);

            result += preprocess(imported);
            result += "\n";
        }
        else
        {
            result += line + "\n";
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
	tmp_var_count = 0;
	
	// Pega o programa.sk e gera um temp preprocessado com as junções dos imports e sem import<*.sk>
	string source = preprocess("programa.sk");

    ofstream tmp("/tmp/preprocessed.sk");
    tmp << source;
    tmp.close();

	// O parser agora analisa o preprocessed ao inves do programa.sk
    yyin = fopen("/tmp/preprocessed.sk", "r");

    if(!yyin)
    {
        cerr << "Erro ao abrir arquivo temporário\n";
        return 1;
    }
	open_block();

	yy::parser p;
	
	if(p.parse() == 0) {
		cout << code;

		ofstream outFile("code.c");
		if(outFile.is_open()) outFile << code << endl;

		ofstream ofile("symbol_table.txt");
		if(ofile.is_open()) {
			for(const auto& scope : scope_stack) {
				for(const auto& [name, sym] : scope) {
					ofile << sym->type.base << " | " << sym->name << " | " << sym->label << endl;
				}
			}
		}
	}
	return 0;
}

void yy::parser::error(const std::string& s) {
	std::cerr << "ERRO: linha (" << yylineno << "): " << s << std::endl;
}

void report_error(const string& msg) {
	std::cerr << "ERRO: Linha [" << yylineno << "]: " << msg << std::endl;
}