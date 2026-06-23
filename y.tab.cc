// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "y.tab.hh"


// Unqualified %code blocks.
#line 15 "sintatico.y"

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
	string gen_tamString();

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

#line 176 "y.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 249 "y.tab.cc"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_TYPE_ANNOTATION: // TYPE_ANNOTATION
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
      case symbol_kind::S_STRUCT_DEF: // STRUCT_DEF
      case symbol_kind::S_CELL_LIST: // CELL_LIST
      case symbol_kind::S_CELL: // CELL
      case symbol_kind::S_FUNCTION_DEF: // FUNCTION_DEF
      case symbol_kind::S_PARAMS_LIST: // PARAMS_LIST
      case symbol_kind::S_PARAM: // PARAM
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_CALL_FUNC: // CALL_FUNC
      case symbol_kind::S_ARGS_LIST: // ARGS_LIST
      case symbol_kind::S_ARG: // ARG
      case symbol_kind::S_BLOCK: // BLOCK
      case symbol_kind::S_CONDITIONAL: // CONDITIONAL
      case symbol_kind::S_OPT_ASSIGNMENT: // OPT_ASSIGNMENT
      case symbol_kind::S_FOR_DECLARATION: // FOR_DECLARATION
      case symbol_kind::S_LOOP: // LOOP
      case symbol_kind::S_LOOPCONTROL: // LOOPCONTROL
      case symbol_kind::S_SWITCHBLOCK: // SWITCHBLOCK
      case symbol_kind::S_CASE_LIST: // CASE_LIST
      case symbol_kind::S_CASE_ITEM: // CASE_ITEM
      case symbol_kind::S_DEFAULT: // DEFAULT
      case symbol_kind::S_IO: // IO
      case symbol_kind::S_PRINT_LIST: // PRINT_LIST
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
      case symbol_kind::S_ARRVAL: // ARRVAL
      case symbol_kind::S_FIELD_LIST: // FIELD_LIST
      case symbol_kind::S_ARRVAL_: // ARRVAL_
      case symbol_kind::S_EXPR: // EXPR
        value.YY_MOVE_OR_COPY< node > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_OP_ADD: // OP_ADD
      case symbol_kind::S_OP_MINUS: // OP_MINUS
      case symbol_kind::S_OP_MULT: // OP_MULT
      case symbol_kind::S_OP_DIV: // OP_DIV
      case symbol_kind::S_OP_MOD: // OP_MOD
      case symbol_kind::S_OP_EQ: // OP_EQ
      case symbol_kind::S_OP_NE: // OP_NE
      case symbol_kind::S_OP_LE: // OP_LE
      case symbol_kind::S_OP_GE: // OP_GE
      case symbol_kind::S_OP_LT: // OP_LT
      case symbol_kind::S_OP_GT: // OP_GT
      case symbol_kind::S_OP_OR: // OP_OR
      case symbol_kind::S_OP_AND: // OP_AND
      case symbol_kind::S_OP_NOT: // OP_NOT
        value.YY_MOVE_OR_COPY< op > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.YY_MOVE_OR_COPY< std::shared_ptr<symbol> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_STRING: // TK_STRING
      case symbol_kind::S_TK_BOOL: // TK_BOOL
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_VAR: // TK_VAR
      case symbol_kind::S_TK_CAST: // TK_CAST
      case symbol_kind::S_TK_VECTOR: // TK_VECTOR
      case symbol_kind::S_TK_SBLOCK: // TK_SBLOCK
      case symbol_kind::S_TK_EBLOCK: // TK_EBLOCK
      case symbol_kind::S_TK_IF: // TK_IF
      case symbol_kind::S_TK_ELSE: // TK_ELSE
      case symbol_kind::S_TK_WHILE: // TK_WHILE
      case symbol_kind::S_TK_DO: // TK_DO
      case symbol_kind::S_TK_BREAK: // TK_BREAK
      case symbol_kind::S_TK_FOR: // TK_FOR
      case symbol_kind::S_TK_IN: // TK_IN
      case symbol_kind::S_TK_RANGE: // TK_RANGE
      case symbol_kind::S_TK_CONTINUE: // TK_CONTINUE
      case symbol_kind::S_TK_CASE: // TK_CASE
      case symbol_kind::S_TK_SWITCH: // TK_SWITCH
      case symbol_kind::S_TK_DEFAULT: // TK_DEFAULT
      case symbol_kind::S_TK_PRINT: // TK_PRINT
      case symbol_kind::S_TK_PRINTL: // TK_PRINTL
      case symbol_kind::S_TK_INPUT: // TK_INPUT
      case symbol_kind::S_TK_FUNCTION: // TK_FUNCTION
      case symbol_kind::S_TK_RETURN: // TK_RETURN
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_TYPE_ANNOTATION: // TYPE_ANNOTATION
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
      case symbol_kind::S_STRUCT_DEF: // STRUCT_DEF
      case symbol_kind::S_CELL_LIST: // CELL_LIST
      case symbol_kind::S_CELL: // CELL
      case symbol_kind::S_FUNCTION_DEF: // FUNCTION_DEF
      case symbol_kind::S_PARAMS_LIST: // PARAMS_LIST
      case symbol_kind::S_PARAM: // PARAM
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_CALL_FUNC: // CALL_FUNC
      case symbol_kind::S_ARGS_LIST: // ARGS_LIST
      case symbol_kind::S_ARG: // ARG
      case symbol_kind::S_BLOCK: // BLOCK
      case symbol_kind::S_CONDITIONAL: // CONDITIONAL
      case symbol_kind::S_OPT_ASSIGNMENT: // OPT_ASSIGNMENT
      case symbol_kind::S_FOR_DECLARATION: // FOR_DECLARATION
      case symbol_kind::S_LOOP: // LOOP
      case symbol_kind::S_LOOPCONTROL: // LOOPCONTROL
      case symbol_kind::S_SWITCHBLOCK: // SWITCHBLOCK
      case symbol_kind::S_CASE_LIST: // CASE_LIST
      case symbol_kind::S_CASE_ITEM: // CASE_ITEM
      case symbol_kind::S_DEFAULT: // DEFAULT
      case symbol_kind::S_IO: // IO
      case symbol_kind::S_PRINT_LIST: // PRINT_LIST
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
      case symbol_kind::S_ARRVAL: // ARRVAL
      case symbol_kind::S_FIELD_LIST: // FIELD_LIST
      case symbol_kind::S_ARRVAL_: // ARRVAL_
      case symbol_kind::S_EXPR: // EXPR
        value.move< node > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_OP_ADD: // OP_ADD
      case symbol_kind::S_OP_MINUS: // OP_MINUS
      case symbol_kind::S_OP_MULT: // OP_MULT
      case symbol_kind::S_OP_DIV: // OP_DIV
      case symbol_kind::S_OP_MOD: // OP_MOD
      case symbol_kind::S_OP_EQ: // OP_EQ
      case symbol_kind::S_OP_NE: // OP_NE
      case symbol_kind::S_OP_LE: // OP_LE
      case symbol_kind::S_OP_GE: // OP_GE
      case symbol_kind::S_OP_LT: // OP_LT
      case symbol_kind::S_OP_GT: // OP_GT
      case symbol_kind::S_OP_OR: // OP_OR
      case symbol_kind::S_OP_AND: // OP_AND
      case symbol_kind::S_OP_NOT: // OP_NOT
        value.move< op > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.move< std::shared_ptr<symbol> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_STRING: // TK_STRING
      case symbol_kind::S_TK_BOOL: // TK_BOOL
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_VAR: // TK_VAR
      case symbol_kind::S_TK_CAST: // TK_CAST
      case symbol_kind::S_TK_VECTOR: // TK_VECTOR
      case symbol_kind::S_TK_SBLOCK: // TK_SBLOCK
      case symbol_kind::S_TK_EBLOCK: // TK_EBLOCK
      case symbol_kind::S_TK_IF: // TK_IF
      case symbol_kind::S_TK_ELSE: // TK_ELSE
      case symbol_kind::S_TK_WHILE: // TK_WHILE
      case symbol_kind::S_TK_DO: // TK_DO
      case symbol_kind::S_TK_BREAK: // TK_BREAK
      case symbol_kind::S_TK_FOR: // TK_FOR
      case symbol_kind::S_TK_IN: // TK_IN
      case symbol_kind::S_TK_RANGE: // TK_RANGE
      case symbol_kind::S_TK_CONTINUE: // TK_CONTINUE
      case symbol_kind::S_TK_CASE: // TK_CASE
      case symbol_kind::S_TK_SWITCH: // TK_SWITCH
      case symbol_kind::S_TK_DEFAULT: // TK_DEFAULT
      case symbol_kind::S_TK_PRINT: // TK_PRINT
      case symbol_kind::S_TK_PRINTL: // TK_PRINTL
      case symbol_kind::S_TK_INPUT: // TK_INPUT
      case symbol_kind::S_TK_FUNCTION: // TK_FUNCTION
      case symbol_kind::S_TK_RETURN: // TK_RETURN
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_TYPE_ANNOTATION: // TYPE_ANNOTATION
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
      case symbol_kind::S_STRUCT_DEF: // STRUCT_DEF
      case symbol_kind::S_CELL_LIST: // CELL_LIST
      case symbol_kind::S_CELL: // CELL
      case symbol_kind::S_FUNCTION_DEF: // FUNCTION_DEF
      case symbol_kind::S_PARAMS_LIST: // PARAMS_LIST
      case symbol_kind::S_PARAM: // PARAM
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_CALL_FUNC: // CALL_FUNC
      case symbol_kind::S_ARGS_LIST: // ARGS_LIST
      case symbol_kind::S_ARG: // ARG
      case symbol_kind::S_BLOCK: // BLOCK
      case symbol_kind::S_CONDITIONAL: // CONDITIONAL
      case symbol_kind::S_OPT_ASSIGNMENT: // OPT_ASSIGNMENT
      case symbol_kind::S_FOR_DECLARATION: // FOR_DECLARATION
      case symbol_kind::S_LOOP: // LOOP
      case symbol_kind::S_LOOPCONTROL: // LOOPCONTROL
      case symbol_kind::S_SWITCHBLOCK: // SWITCHBLOCK
      case symbol_kind::S_CASE_LIST: // CASE_LIST
      case symbol_kind::S_CASE_ITEM: // CASE_ITEM
      case symbol_kind::S_DEFAULT: // DEFAULT
      case symbol_kind::S_IO: // IO
      case symbol_kind::S_PRINT_LIST: // PRINT_LIST
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
      case symbol_kind::S_ARRVAL: // ARRVAL
      case symbol_kind::S_FIELD_LIST: // FIELD_LIST
      case symbol_kind::S_ARRVAL_: // ARRVAL_
      case symbol_kind::S_EXPR: // EXPR
        value.copy< node > (that.value);
        break;

      case symbol_kind::S_OP_ADD: // OP_ADD
      case symbol_kind::S_OP_MINUS: // OP_MINUS
      case symbol_kind::S_OP_MULT: // OP_MULT
      case symbol_kind::S_OP_DIV: // OP_DIV
      case symbol_kind::S_OP_MOD: // OP_MOD
      case symbol_kind::S_OP_EQ: // OP_EQ
      case symbol_kind::S_OP_NE: // OP_NE
      case symbol_kind::S_OP_LE: // OP_LE
      case symbol_kind::S_OP_GE: // OP_GE
      case symbol_kind::S_OP_LT: // OP_LT
      case symbol_kind::S_OP_GT: // OP_GT
      case symbol_kind::S_OP_OR: // OP_OR
      case symbol_kind::S_OP_AND: // OP_AND
      case symbol_kind::S_OP_NOT: // OP_NOT
        value.copy< op > (that.value);
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.copy< std::shared_ptr<symbol> > (that.value);
        break;

      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_STRING: // TK_STRING
      case symbol_kind::S_TK_BOOL: // TK_BOOL
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_VAR: // TK_VAR
      case symbol_kind::S_TK_CAST: // TK_CAST
      case symbol_kind::S_TK_VECTOR: // TK_VECTOR
      case symbol_kind::S_TK_SBLOCK: // TK_SBLOCK
      case symbol_kind::S_TK_EBLOCK: // TK_EBLOCK
      case symbol_kind::S_TK_IF: // TK_IF
      case symbol_kind::S_TK_ELSE: // TK_ELSE
      case symbol_kind::S_TK_WHILE: // TK_WHILE
      case symbol_kind::S_TK_DO: // TK_DO
      case symbol_kind::S_TK_BREAK: // TK_BREAK
      case symbol_kind::S_TK_FOR: // TK_FOR
      case symbol_kind::S_TK_IN: // TK_IN
      case symbol_kind::S_TK_RANGE: // TK_RANGE
      case symbol_kind::S_TK_CONTINUE: // TK_CONTINUE
      case symbol_kind::S_TK_CASE: // TK_CASE
      case symbol_kind::S_TK_SWITCH: // TK_SWITCH
      case symbol_kind::S_TK_DEFAULT: // TK_DEFAULT
      case symbol_kind::S_TK_PRINT: // TK_PRINT
      case symbol_kind::S_TK_PRINTL: // TK_PRINTL
      case symbol_kind::S_TK_INPUT: // TK_INPUT
      case symbol_kind::S_TK_FUNCTION: // TK_FUNCTION
      case symbol_kind::S_TK_RETURN: // TK_RETURN
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_TYPE_ANNOTATION: // TYPE_ANNOTATION
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
      case symbol_kind::S_STRUCT_DEF: // STRUCT_DEF
      case symbol_kind::S_CELL_LIST: // CELL_LIST
      case symbol_kind::S_CELL: // CELL
      case symbol_kind::S_FUNCTION_DEF: // FUNCTION_DEF
      case symbol_kind::S_PARAMS_LIST: // PARAMS_LIST
      case symbol_kind::S_PARAM: // PARAM
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_CALL_FUNC: // CALL_FUNC
      case symbol_kind::S_ARGS_LIST: // ARGS_LIST
      case symbol_kind::S_ARG: // ARG
      case symbol_kind::S_BLOCK: // BLOCK
      case symbol_kind::S_CONDITIONAL: // CONDITIONAL
      case symbol_kind::S_OPT_ASSIGNMENT: // OPT_ASSIGNMENT
      case symbol_kind::S_FOR_DECLARATION: // FOR_DECLARATION
      case symbol_kind::S_LOOP: // LOOP
      case symbol_kind::S_LOOPCONTROL: // LOOPCONTROL
      case symbol_kind::S_SWITCHBLOCK: // SWITCHBLOCK
      case symbol_kind::S_CASE_LIST: // CASE_LIST
      case symbol_kind::S_CASE_ITEM: // CASE_ITEM
      case symbol_kind::S_DEFAULT: // DEFAULT
      case symbol_kind::S_IO: // IO
      case symbol_kind::S_PRINT_LIST: // PRINT_LIST
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
      case symbol_kind::S_ARRVAL: // ARRVAL
      case symbol_kind::S_FIELD_LIST: // FIELD_LIST
      case symbol_kind::S_ARRVAL_: // ARRVAL_
      case symbol_kind::S_EXPR: // EXPR
        value.move< node > (that.value);
        break;

      case symbol_kind::S_OP_ADD: // OP_ADD
      case symbol_kind::S_OP_MINUS: // OP_MINUS
      case symbol_kind::S_OP_MULT: // OP_MULT
      case symbol_kind::S_OP_DIV: // OP_DIV
      case symbol_kind::S_OP_MOD: // OP_MOD
      case symbol_kind::S_OP_EQ: // OP_EQ
      case symbol_kind::S_OP_NE: // OP_NE
      case symbol_kind::S_OP_LE: // OP_LE
      case symbol_kind::S_OP_GE: // OP_GE
      case symbol_kind::S_OP_LT: // OP_LT
      case symbol_kind::S_OP_GT: // OP_GT
      case symbol_kind::S_OP_OR: // OP_OR
      case symbol_kind::S_OP_AND: // OP_AND
      case symbol_kind::S_OP_NOT: // OP_NOT
        value.move< op > (that.value);
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.move< std::shared_ptr<symbol> > (that.value);
        break;

      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_STRING: // TK_STRING
      case symbol_kind::S_TK_BOOL: // TK_BOOL
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_VAR: // TK_VAR
      case symbol_kind::S_TK_CAST: // TK_CAST
      case symbol_kind::S_TK_VECTOR: // TK_VECTOR
      case symbol_kind::S_TK_SBLOCK: // TK_SBLOCK
      case symbol_kind::S_TK_EBLOCK: // TK_EBLOCK
      case symbol_kind::S_TK_IF: // TK_IF
      case symbol_kind::S_TK_ELSE: // TK_ELSE
      case symbol_kind::S_TK_WHILE: // TK_WHILE
      case symbol_kind::S_TK_DO: // TK_DO
      case symbol_kind::S_TK_BREAK: // TK_BREAK
      case symbol_kind::S_TK_FOR: // TK_FOR
      case symbol_kind::S_TK_IN: // TK_IN
      case symbol_kind::S_TK_RANGE: // TK_RANGE
      case symbol_kind::S_TK_CONTINUE: // TK_CONTINUE
      case symbol_kind::S_TK_CASE: // TK_CASE
      case symbol_kind::S_TK_SWITCH: // TK_SWITCH
      case symbol_kind::S_TK_DEFAULT: // TK_DEFAULT
      case symbol_kind::S_TK_PRINT: // TK_PRINT
      case symbol_kind::S_TK_PRINTL: // TK_PRINTL
      case symbol_kind::S_TK_INPUT: // TK_INPUT
      case symbol_kind::S_TK_FUNCTION: // TK_FUNCTION
      case symbol_kind::S_TK_RETURN: // TK_RETURN
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_TYPE_ANNOTATION: // TYPE_ANNOTATION
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
      case symbol_kind::S_STRUCT_DEF: // STRUCT_DEF
      case symbol_kind::S_CELL_LIST: // CELL_LIST
      case symbol_kind::S_CELL: // CELL
      case symbol_kind::S_FUNCTION_DEF: // FUNCTION_DEF
      case symbol_kind::S_PARAMS_LIST: // PARAMS_LIST
      case symbol_kind::S_PARAM: // PARAM
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_CALL_FUNC: // CALL_FUNC
      case symbol_kind::S_ARGS_LIST: // ARGS_LIST
      case symbol_kind::S_ARG: // ARG
      case symbol_kind::S_BLOCK: // BLOCK
      case symbol_kind::S_CONDITIONAL: // CONDITIONAL
      case symbol_kind::S_OPT_ASSIGNMENT: // OPT_ASSIGNMENT
      case symbol_kind::S_FOR_DECLARATION: // FOR_DECLARATION
      case symbol_kind::S_LOOP: // LOOP
      case symbol_kind::S_LOOPCONTROL: // LOOPCONTROL
      case symbol_kind::S_SWITCHBLOCK: // SWITCHBLOCK
      case symbol_kind::S_CASE_LIST: // CASE_LIST
      case symbol_kind::S_CASE_ITEM: // CASE_ITEM
      case symbol_kind::S_DEFAULT: // DEFAULT
      case symbol_kind::S_IO: // IO
      case symbol_kind::S_PRINT_LIST: // PRINT_LIST
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
      case symbol_kind::S_ARRVAL: // ARRVAL
      case symbol_kind::S_FIELD_LIST: // FIELD_LIST
      case symbol_kind::S_ARRVAL_: // ARRVAL_
      case symbol_kind::S_EXPR: // EXPR
        yylhs.value.emplace< node > ();
        break;

      case symbol_kind::S_OP_ADD: // OP_ADD
      case symbol_kind::S_OP_MINUS: // OP_MINUS
      case symbol_kind::S_OP_MULT: // OP_MULT
      case symbol_kind::S_OP_DIV: // OP_DIV
      case symbol_kind::S_OP_MOD: // OP_MOD
      case symbol_kind::S_OP_EQ: // OP_EQ
      case symbol_kind::S_OP_NE: // OP_NE
      case symbol_kind::S_OP_LE: // OP_LE
      case symbol_kind::S_OP_GE: // OP_GE
      case symbol_kind::S_OP_LT: // OP_LT
      case symbol_kind::S_OP_GT: // OP_GT
      case symbol_kind::S_OP_OR: // OP_OR
      case symbol_kind::S_OP_AND: // OP_AND
      case symbol_kind::S_OP_NOT: // OP_NOT
        yylhs.value.emplace< op > ();
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        yylhs.value.emplace< std::shared_ptr<symbol> > ();
        break;

      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_STRING: // TK_STRING
      case symbol_kind::S_TK_BOOL: // TK_BOOL
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_VAR: // TK_VAR
      case symbol_kind::S_TK_CAST: // TK_CAST
      case symbol_kind::S_TK_VECTOR: // TK_VECTOR
      case symbol_kind::S_TK_SBLOCK: // TK_SBLOCK
      case symbol_kind::S_TK_EBLOCK: // TK_EBLOCK
      case symbol_kind::S_TK_IF: // TK_IF
      case symbol_kind::S_TK_ELSE: // TK_ELSE
      case symbol_kind::S_TK_WHILE: // TK_WHILE
      case symbol_kind::S_TK_DO: // TK_DO
      case symbol_kind::S_TK_BREAK: // TK_BREAK
      case symbol_kind::S_TK_FOR: // TK_FOR
      case symbol_kind::S_TK_IN: // TK_IN
      case symbol_kind::S_TK_RANGE: // TK_RANGE
      case symbol_kind::S_TK_CONTINUE: // TK_CONTINUE
      case symbol_kind::S_TK_CASE: // TK_CASE
      case symbol_kind::S_TK_SWITCH: // TK_SWITCH
      case symbol_kind::S_TK_DEFAULT: // TK_DEFAULT
      case symbol_kind::S_TK_PRINT: // TK_PRINT
      case symbol_kind::S_TK_PRINTL: // TK_PRINTL
      case symbol_kind::S_TK_INPUT: // TK_INPUT
      case symbol_kind::S_TK_FUNCTION: // TK_FUNCTION
      case symbol_kind::S_TK_RETURN: // TK_RETURN
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // S: COMMANDS
#line 175 "sintatico.y"
                        {
				code = 
				"#include <stdio.h>\n"
				"#include <string.h>\n"
				"#include <stdlib.h>\n\n";
				code += structs_code;
				code += functions_code;
				code += "int main(void) {\n";
				code += gen_declarations();
				code += "\n" + yystack_[0].value.as < node > ().translation;
				for(const auto& label : allocated_stack.front()){
        			code += "\tfree(" + label + ");\n";
    			}
				code += "\treturn 0;\n}\n";
			}
#line 1084 "y.tab.cc"
    break;

  case 3: // COMMANDS: COMMANDS STATEMENT
#line 191 "sintatico.y"
                                     {yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation + yystack_[0].value.as < node > ().translation;}
#line 1090 "y.tab.cc"
    break;

  case 4: // COMMANDS: STATEMENT
#line 192 "sintatico.y"
                                                 {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1096 "y.tab.cc"
    break;

  case 5: // STATEMENT: DECLARATION ';'
#line 195 "sintatico.y"
                                  {yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation;}
#line 1102 "y.tab.cc"
    break;

  case 6: // STATEMENT: ASSIGNMENT ';'
#line 196 "sintatico.y"
                                          {yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation;}
#line 1108 "y.tab.cc"
    break;

  case 7: // STATEMENT: BLOCK
#line 197 "sintatico.y"
                                                  {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1114 "y.tab.cc"
    break;

  case 8: // STATEMENT: CONDITIONAL
#line 198 "sintatico.y"
                                          {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1120 "y.tab.cc"
    break;

  case 9: // STATEMENT: LOOP
#line 199 "sintatico.y"
                                                  {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1126 "y.tab.cc"
    break;

  case 10: // STATEMENT: LOOPCONTROL
#line 200 "sintatico.y"
                                          {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1132 "y.tab.cc"
    break;

  case 11: // STATEMENT: IO
#line 201 "sintatico.y"
                                              {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1138 "y.tab.cc"
    break;

  case 12: // STATEMENT: FUNCTION_DEF
#line 202 "sintatico.y"
                                          {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1144 "y.tab.cc"
    break;

  case 13: // STATEMENT: RETURN
#line 203 "sintatico.y"
                                                  {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1150 "y.tab.cc"
    break;

  case 14: // STATEMENT: CALL_FUNC
#line 204 "sintatico.y"
                                          {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1156 "y.tab.cc"
    break;

  case 15: // STATEMENT: STRUCT_DEF
#line 205 "sintatico.y"
                                          {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1162 "y.tab.cc"
    break;

  case 16: // TYPE_ANNOTATION: TK_TYPE
#line 212 "sintatico.y"
                          {yylhs.value.as < node > ().type = Type(yystack_[0].value.as < std::string > ()); yylhs.value.as < node > ().translation = "";}
#line 1168 "y.tab.cc"
    break;

  case 17: // TYPE_ANNOTATION: TK_VECTOR OP_LT TK_TYPE OP_GT
#line 215 "sintatico.y"
                                {
					yylhs.value.as < node > ().type = Type(yystack_[1].value.as < std::string > ());
					yylhs.value.as < node > ().type.kind = Type::Kind::ARRAY;
					yylhs.value.as < node > ().translation = "";
				}
#line 1178 "y.tab.cc"
    break;

  case 18: // TYPE_ANNOTATION: TK_ID
#line 223 "sintatico.y"
                                {
					auto it = structs.find(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name);
					if(it == structs.end()){
                    report_error("Tipo '" + yystack_[0].value.as < std::shared_ptr<symbol> > ()->name + "' não é uma struct conhecida."); // Temos que padronizar as mensagens de erros...
               		}
					yylhs.value.as < node > ().type = Type(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name);
					yylhs.value.as < node > ().type.kind = Type::Kind::STRUCT;
					yylhs.value.as < node > ().translation = "";
				}
#line 1192 "y.tab.cc"
    break;

  case 19: // DECLARATION: TK_VAR TK_ID
#line 235 "sintatico.y"
                        {
				yystack_[0].value.as < std::shared_ptr<symbol> > ()->type = Type("undefined");
				yystack_[0].value.as < std::shared_ptr<symbol> > ()->is_static = false;
				yylhs.value.as < node > ().translation = "";
				register_symbol(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name, yystack_[0].value.as < std::shared_ptr<symbol> > ());
			}
#line 1203 "y.tab.cc"
    break;

  case 20: // DECLARATION: TK_VAR TK_ID ':' TYPE_ANNOTATION
#line 243 "sintatico.y"
                        {

				yystack_[2].value.as < std::shared_ptr<symbol> > ()->type = yystack_[0].value.as < node > ().type;
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->is_static = true;
				if(yystack_[0].value.as < node > ().type.kind == Type::Kind::STRUCT){
					yystack_[2].value.as < std::shared_ptr<symbol> > ()->label = gen_tmp_variable();
                	push_variables(yystack_[2].value.as < std::shared_ptr<symbol> > ()->label, "struct " + yystack_[0].value.as < node > ().type.base);   // tipo IR é "struct Nome"
				}
				register_symbol(yystack_[2].value.as < std::shared_ptr<symbol> > ()->name, yystack_[2].value.as < std::shared_ptr<symbol> > ());
				yylhs.value.as < node > ().translation = "";

			}
#line 1220 "y.tab.cc"
    break;

  case 21: // ASSIGNMENT: LVAL OP_AT RVAL
#line 259 "sintatico.y"
                        {	
				if(yystack_[0].value.as < node > ().type.base == "void"){
					  report_error("Procedimento '" + yystack_[0].value.as < node > ().label + "' retorna void e não pode ser atribuído.");
				}

				if(yystack_[2].value.as < node > ().is_static) {
					if(yystack_[0].value.as < node > ().type != yystack_[2].value.as < node > ().type)
						report_error("Variavel '" + yystack_[2].value.as < node > ().label + "' do tipo estatico '" + yystack_[2].value.as < node > ().type.base + "' recebendo outro tipo '" + yystack_[0].value.as < node > ().type.base + "'");
				}

				materialize(yystack_[0].value.as < node > ());
				promote_symbol(yystack_[2].value.as < node > (), yystack_[0].value.as < node > ().type);
				materialize(yystack_[2].value.as < node > ());

				
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += gen_assignment(yystack_[2].value.as < node > (), yystack_[0].value.as < node > ());
			}
#line 1244 "y.tab.cc"
    break;

  case 22: // ASSIGNMENT: TK_VAR TK_ID OP_AT RVAL
#line 280 "sintatico.y"
                        {	
				if(yystack_[0].value.as < node > ().type.base == "void"){
					  report_error("Procedimento '" + yystack_[0].value.as < node > ().label + "' retorna void e não pode ser atribuído.");
				}

				materialize(yystack_[0].value.as < node > ());
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->is_static = false;
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->type = yystack_[0].value.as < node > ().type;
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->type.array_size = yystack_[0].value.as < node > ().elements.size();
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->label = gen_tmp_variable();
				push_variables(yystack_[2].value.as < std::shared_ptr<symbol> > ()->label, to_ir_type(yystack_[2].value.as < std::shared_ptr<symbol> > ()->type));
				register_symbol(yystack_[2].value.as < std::shared_ptr<symbol> > ()->name, yystack_[2].value.as < std::shared_ptr<symbol> > ());

				// TK_ID não é um nó
				node dest;
				dest.label = yystack_[2].value.as < std::shared_ptr<symbol> > ()->label;
				dest.type  = yystack_[2].value.as < std::shared_ptr<symbol> > ()->type;
				dest.is_materialized = true;

				yylhs.value.as < node > ().translation  = yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += gen_assignment(dest, yystack_[0].value.as < node > ());
			}
#line 1271 "y.tab.cc"
    break;

  case 23: // ASSIGNMENT: TK_VAR TK_ID ':' TYPE_ANNOTATION OP_AT RVAL
#line 304 "sintatico.y"
                        {	
				if(yystack_[0].value.as < node > ().type.base == "void"){
					report_error("Procedimento '" + yystack_[0].value.as < node > ().label + "' retorna void e não pode ser atribuído.");
				}

				materialize(yystack_[0].value.as < node > ());

				if(yystack_[2].value.as < node > ().type.kind != yystack_[0].value.as < node > ().type.kind || yystack_[2].value.as < node > ().type.base != yystack_[0].value.as < node > ().type.base)
					if(yystack_[0].value.as < node > ().type.base != "cell_struct") {
						report_error("Variável '" + yystack_[4].value.as < std::shared_ptr<symbol> > ()->name + "' do tipo '" + yystack_[2].value.as < node > ().type.base +
								"' recebendo tipo '" + yystack_[0].value.as < node > ().type.base + "'");
					}
				yystack_[4].value.as < std::shared_ptr<symbol> > ()->type = yystack_[2].value.as < node > ().type;
				yystack_[4].value.as < std::shared_ptr<symbol> > ()->type.array_size = yystack_[0].value.as < node > ().elements.size();
				yystack_[4].value.as < std::shared_ptr<symbol> > ()->is_static = true;
				yystack_[4].value.as < std::shared_ptr<symbol> > ()->label = gen_tmp_variable();
				push_variables(yystack_[4].value.as < std::shared_ptr<symbol> > ()->label, to_ir_type(yystack_[4].value.as < std::shared_ptr<symbol> > ()->type));
				register_symbol(yystack_[4].value.as < std::shared_ptr<symbol> > ()->name, yystack_[4].value.as < std::shared_ptr<symbol> > ());

				node dest;
				dest.label = yystack_[4].value.as < std::shared_ptr<symbol> > ()->label;
				dest.type  = yystack_[4].value.as < std::shared_ptr<symbol> > ()->type;
				dest.is_materialized = true;

				yylhs.value.as < node > ().translation  = yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += gen_assignment(dest, yystack_[0].value.as < node > ());
			}
#line 1303 "y.tab.cc"
    break;

  case 24: // ASSIGNMENT: LVAL OP_ADD OP_ADD
#line 333 "sintatico.y"
                        {
				materialize(yystack_[2].value.as < node > ());
				yylhs.value.as < node > ().translation = "\t" + yystack_[2].value.as < node > ().label + " = " + yystack_[2].value.as < node > ().label + " + 1;\n"; 
			}
#line 1312 "y.tab.cc"
    break;

  case 25: // ASSIGNMENT: LVAL OP_MINUS OP_MINUS
#line 338 "sintatico.y"
                        {
				materialize(yystack_[2].value.as < node > ());
				yylhs.value.as < node > ().translation = "\t" + yystack_[2].value.as < node > ().label + " = " + yystack_[2].value.as < node > ().label + " - 1;\n"; 
			}
#line 1321 "y.tab.cc"
    break;

  case 26: // STRUCT_DEF: TK_ID TK_SBLOCK CELL_LIST TK_EBLOCK ';'
#line 346 "sintatico.y"
                                {
					body_attr obj;
					obj.name = yystack_[4].value.as < std::shared_ptr<symbol> > ()->name;
					obj.cells = current_cells;
					structs[yystack_[4].value.as < std::shared_ptr<symbol> > ()->name] = obj;
					current_cells.clear();

					// Gerar codigo da struct
					structs_code += "struct " + obj.name + "{\n";
						for(auto &c : obj.cells){
							structs_code += "\t" +  to_ir_type(Type(c.type)) + " " + c.name + ";\n";
						}
						structs_code += "};\n\n";

					yylhs.value.as < node > ().translation = "";
				}
#line 1342 "y.tab.cc"
    break;

  case 27: // CELL_LIST: CELL_LIST CELL
#line 364 "sintatico.y"
                                         {yylhs.value.as < node > ().translation = ""; }
#line 1348 "y.tab.cc"
    break;

  case 28: // CELL_LIST: CELL
#line 365 "sintatico.y"
                                                         {yylhs.value.as < node > ().translation = ""; }
#line 1354 "y.tab.cc"
    break;

  case 29: // CELL: TK_ID ':' TK_TYPE ';'
#line 369 "sintatico.y"
                        {
				current_cells.push_back({yystack_[3].value.as < std::shared_ptr<symbol> > ()->name, yystack_[1].value.as < std::string > ()});
				yylhs.value.as < node > ().translation = "";
			}
#line 1363 "y.tab.cc"
    break;

  case 30: // $@1: %empty
#line 377 "sintatico.y"
                        {
				open_function(yystack_[1].value.as < std::shared_ptr<symbol> > ()->name);
			}
#line 1371 "y.tab.cc"
    break;

  case 31: // $@2: %empty
#line 380 "sintatico.y"
                        {
				// Tipo
				function_stack.back().return_type = yystack_[0].value.as < std::string > ();
				function_stack.back().ir_return_type = to_ir_type(yystack_[0].value.as < std::string > ());


				// Adicionando a função na "tabela"
				func_data f;
				f.name = yystack_[6].value.as < std::shared_ptr<symbol> > ()->name; 
				f.params = function_stack.back().params;
				f.return_type = yystack_[0].value.as < std::string > ();
				f.ir_return_type = to_ir_type(yystack_[0].value.as < std::string > ());
				functions[yystack_[6].value.as < std::shared_ptr<symbol> > ()->name] = f;

			}
#line 1391 "y.tab.cc"
    break;

  case 32: // FUNCTION_DEF: TK_FUNCTION TK_ID '(' $@1 PARAMS_LIST ')' ':' TK_TYPE $@2 BLOCK
#line 395 "sintatico.y"
                        {
				function_stack.back().translation = yystack_[0].value.as < node > ().translation;
				functions_code += close_function();
				yylhs.value.as < node > ().translation = "";
			}
#line 1401 "y.tab.cc"
    break;

  case 33: // PARAMS_LIST: PARAMS_LIST ',' PARAM
#line 403 "sintatico.y"
                                    { yylhs.value.as < node > ().translation = ""; }
#line 1407 "y.tab.cc"
    break;

  case 34: // PARAMS_LIST: PARAM
#line 404 "sintatico.y"
                                   { yylhs.value.as < node > ().translation = ""; }
#line 1413 "y.tab.cc"
    break;

  case 35: // PARAMS_LIST: %empty
#line 405 "sintatico.y"
                                    { yylhs.value.as < node > ().translation = ""; }
#line 1419 "y.tab.cc"
    break;

  case 36: // PARAM: TK_ID ':' TK_TYPE
#line 409 "sintatico.y"
                        {
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->type      = yystack_[0].value.as < std::string > ();
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->is_static = true;
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->label     = gen_tmp_variable();       
				register_symbol(yystack_[2].value.as < std::shared_ptr<symbol> > ()->name, yystack_[2].value.as < std::shared_ptr<symbol> > ());
				function_stack.back().params.push_back({yystack_[2].value.as < std::shared_ptr<symbol> > ()->label, yystack_[0].value.as < std::string > ()});
				yylhs.value.as < node > ().translation = "";
			}
#line 1432 "y.tab.cc"
    break;

  case 37: // RETURN: TK_RETURN ';'
#line 420 "sintatico.y"
                        {	
				yylhs.value.as < node > ().translation = "\treturn;\n"; 

			}
#line 1441 "y.tab.cc"
    break;

  case 38: // RETURN: TK_RETURN RVAL ';'
#line 425 "sintatico.y"
                        {
				materialize(yystack_[1].value.as < node > ());
				yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\treturn " + yystack_[1].value.as < node > ().label + ";\n";
			}
#line 1451 "y.tab.cc"
    break;

  case 39: // CALL_FUNC: TK_ID '(' ARGS_LIST ')' ';'
#line 433 "sintatico.y"
                        {
              auto it = functions.find(yystack_[4].value.as < std::shared_ptr<symbol> > ()->name);
              if(it == functions.end()){
                  report_error("Função '" + yystack_[4].value.as < std::shared_ptr<symbol> > ()->name + "' não declarada.");
                  yylhs.value.as < node > ().translation = "";
              }
              else {
                  yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
                  // chama a função mas não guarda o retorno
                  yylhs.value.as < node > ().translation += "\t" + yystack_[4].value.as < std::shared_ptr<symbol> > ()->name + "(" + yystack_[2].value.as < node > ().label + ");\n";
              }
          }
#line 1468 "y.tab.cc"
    break;

  case 40: // ARGS_LIST: ARGS_LIST ',' ARG
#line 448 "sintatico.y"
                        { 
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation + yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().label = yystack_[2].value.as < node > ().label + ", " + yystack_[0].value.as < node > ().label;
			}
#line 1477 "y.tab.cc"
    break;

  case 41: // ARGS_LIST: ARG
#line 453 "sintatico.y"
                                 { yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation; yylhs.value.as < node > ().label = yystack_[0].value.as < node > ().label;}
#line 1483 "y.tab.cc"
    break;

  case 42: // ARGS_LIST: %empty
#line 455 "sintatico.y"
                                 { yylhs.value.as < node > ().translation = ""; }
#line 1489 "y.tab.cc"
    break;

  case 43: // ARG: EXPR
#line 458 "sintatico.y"
                        {materialize(yystack_[0].value.as < node > ()); yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation; yylhs.value.as < node > ().label = yystack_[0].value.as < node > ().label;}
#line 1495 "y.tab.cc"
    break;

  case 44: // $@3: %empty
#line 461 "sintatico.y"
                          { open_block(); }
#line 1501 "y.tab.cc"
    break;

  case 45: // BLOCK: TK_SBLOCK $@3 COMMANDS TK_EBLOCK
#line 462 "sintatico.y"
                        {	
				auto scope_to_free = allocated_stack.back();
				close_block();

				yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation;
				for(const auto& label : scope_to_free){
					yylhs.value.as < node > ().translation += "\tfree(" + label + ");\n";
				}
			}
#line 1515 "y.tab.cc"
    break;

  case 46: // $@4: %empty
#line 472 "sintatico.y"
                                   {open_block();}
#line 1521 "y.tab.cc"
    break;

  case 47: // BLOCK: TK_SBLOCK $@4 TK_EBLOCK
#line 473 "sintatico.y"
                        {
				close_block();
				yylhs.value.as < node > ().translation = "";
			}
#line 1530 "y.tab.cc"
    break;

  case 48: // CONDITIONAL: TK_IF '(' EXPR ')' BLOCK TK_ELSE BLOCK
#line 480 "sintatico.y"
                        {
				string label_if = gen_label_loop();
				string label_else = gen_label_loop();

				materialize(yystack_[4].value.as < node > ());
				yylhs.value.as < node > ().translation = yystack_[4].value.as < node > ().translation;

				yylhs.value.as < node > ().translation += "\tif(!" + yystack_[4].value.as < node > ().label + ") " + "goto " + label_else + ";\n";
				yylhs.value.as < node > ().translation += yystack_[2].value.as < node > ().translation + "\n";
				yylhs.value.as < node > ().translation += "\tgoto " + label_if + ";\n";
				yylhs.value.as < node > ().translation += label_else + ":" + "\n" + yystack_[0].value.as < node > ().translation + "\n";
				yylhs.value.as < node > ().translation += label_if + ":\n";
			}
#line 1548 "y.tab.cc"
    break;

  case 49: // CONDITIONAL: TK_IF '(' EXPR ')' BLOCK
#line 494 "sintatico.y"
                        {
				string label_final = gen_label_loop();
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tif(!" + yystack_[2].value.as < node > ().label + ") " + "goto " + label_final + ";\n";
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += label_final + ":" + "\n";
			}
#line 1560 "y.tab.cc"
    break;

  case 50: // $@5: %empty
#line 503 "sintatico.y"
                        { 
				materialize(yystack_[1].value.as < node > ()); 
				open_switch(yystack_[1].value.as < node > ());
			}
#line 1569 "y.tab.cc"
    break;

  case 51: // CONDITIONAL: TK_SWITCH '(' EXPR ')' $@5 ':' SWITCHBLOCK
#line 507 "sintatico.y"
                        {
				string end_label = get_back_switch()->end_label;
				
				yylhs.value.as < node > ().translation = yystack_[4].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().jumps;
				yylhs.value.as < node > ().translation += "\tgoto " + end_label + ";\n";
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().labels_jumps;
				yylhs.value.as < node > ().translation += end_label + ":\n";
				
				context_stack.pop_back();	
			}
#line 1585 "y.tab.cc"
    break;

  case 52: // OPT_ASSIGNMENT: ASSIGNMENT
#line 520 "sintatico.y"
                             {yylhs.value.as < node > () = yystack_[0].value.as < node > ();}
#line 1591 "y.tab.cc"
    break;

  case 53: // OPT_ASSIGNMENT: %empty
#line 521 "sintatico.y"
                             {yylhs.value.as < node > ().translation = "";}
#line 1597 "y.tab.cc"
    break;

  case 54: // FOR_DECLARATION: TK_ID
#line 525 "sintatico.y"
                        {
				auto ini = lookup_symbol(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name);
				if(ini) {
					if(!ini->label.empty()) {
						yystack_[0].value.as < std::shared_ptr<symbol> > ()->label = ini->label;
					} else {
						ini->label = gen_tmp_variable();
						push_variables(ini->label, "int");
						yystack_[0].value.as < std::shared_ptr<symbol> > ()->label = ini->label;
					}

					if(ini->is_static == true && ini->type.base != "int") {
						report_error("variavel " + ini->name + " é estatica do tipo " + ini->type.base + "\n;");
						return 0;
					}

					ini->type = Type("int");
					yystack_[0].value.as < std::shared_ptr<symbol> > ()->type  = Type("int");
					yystack_[0].value.as < std::shared_ptr<symbol> > ()->is_static = ini->is_static;
				} else {
					yystack_[0].value.as < std::shared_ptr<symbol> > ()->label     = gen_tmp_variable();
					yystack_[0].value.as < std::shared_ptr<symbol> > ()->type      = Type("int");
					yystack_[0].value.as < std::shared_ptr<symbol> > ()->is_static = true;
					push_variables(yystack_[0].value.as < std::shared_ptr<symbol> > ()->label, "int");
					register_symbol(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name, yystack_[0].value.as < std::shared_ptr<symbol> > ());
				}

				yylhs.value.as < node > ().label           = yystack_[0].value.as < std::shared_ptr<symbol> > ()->label;
				yylhs.value.as < node > ().type            = yystack_[0].value.as < std::shared_ptr<symbol> > ()->type;
				yylhs.value.as < node > ().is_static       = yystack_[0].value.as < std::shared_ptr<symbol> > ()->is_static;
				yylhs.value.as < node > ().is_materialized = true;
				yylhs.value.as < node > ().translation     = "";
			}
#line 1635 "y.tab.cc"
    break;

  case 55: // $@6: %empty
#line 559 "sintatico.y"
                                        {open_loop();}
#line 1641 "y.tab.cc"
    break;

  case 56: // LOOP: TK_WHILE '(' EXPR ')' $@6 BLOCK
#line 560 "sintatico.y"
                        {	
				materialize(yystack_[3].value.as < node > ());
				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;
				string label_continue = get_back_loop()->continue_label;

				yylhs.value.as < node > ().translation = label_start + ":\n";
				yylhs.value.as < node > ().translation += yystack_[3].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tif(!" + yystack_[3].value.as < node > ().label + ") goto " + label_end + ";\n";
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().translation;
				if(label_continue != "") yylhs.value.as < node > ().translation += label_continue + ":\n";
				yylhs.value.as < node > ().translation += "\tgoto " + label_start + ";\n";
				yylhs.value.as < node > ().translation += label_end + ":\n";
				context_stack.pop_back();
			}
#line 1661 "y.tab.cc"
    break;

  case 57: // $@7: %empty
#line 576 "sintatico.y"
                                {open_loop();}
#line 1667 "y.tab.cc"
    break;

  case 58: // LOOP: TK_DO $@7 BLOCK TK_WHILE '(' EXPR ')' ';'
#line 577 "sintatico.y"
                        {				
				materialize(yystack_[2].value.as < node > ());
				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;
				string label_continue = get_back_loop()->continue_label;
				string label_jump = gen_label_loop();

				yylhs.value.as < node > ().translation = "\tgoto " + label_jump + ";\n";
				yylhs.value.as < node > ().translation += label_start + ":\n";
				yylhs.value.as < node > ().translation += yystack_[2].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tif(!" + yystack_[2].value.as < node > ().label + ") goto " + label_end + ";\n";
				yylhs.value.as < node > ().translation += label_jump + ":\n";
				yylhs.value.as < node > ().translation += yystack_[5].value.as < node > ().translation;
				if(label_continue != "") yylhs.value.as < node > ().translation += label_continue + ":\n";
				yylhs.value.as < node > ().translation += "\tgoto " + label_start + ";\n";
				yylhs.value.as < node > ().translation += label_end + ":\n";
				context_stack.pop_back();
			}
#line 1690 "y.tab.cc"
    break;

  case 59: // $@8: %empty
#line 596 "sintatico.y"
                                     {open_block();}
#line 1696 "y.tab.cc"
    break;

  case 60: // $@9: %empty
#line 596 "sintatico.y"
                                                                    {open_block();}
#line 1702 "y.tab.cc"
    break;

  case 61: // $@10: %empty
#line 596 "sintatico.y"
                                                                                                                    {open_loop();}
#line 1708 "y.tab.cc"
    break;

  case 62: // LOOP: TK_FOR '(' $@8 OPT_ASSIGNMENT $@9 ';' EXPR ';' OPT_ASSIGNMENT ')' $@10 BLOCK
#line 597 "sintatico.y"
                        {
				materialize(yystack_[5].value.as < node > ());

				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;

				yylhs.value.as < node > ().translation += yystack_[8].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += label_start + ":\n";
				yylhs.value.as < node > ().translation += yystack_[5].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tif(!" + yystack_[5].value.as < node > ().label + ") goto " + label_end + ";\n";
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += yystack_[3].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tgoto " + label_start + ";\n";
				yylhs.value.as < node > ().translation += label_end + ":\n";
				context_stack.pop_back();
			}
#line 1729 "y.tab.cc"
    break;

  case 63: // $@11: %empty
#line 614 "sintatico.y"
                                                                                      {open_loop();}
#line 1735 "y.tab.cc"
    break;

  case 64: // LOOP: TK_FOR FOR_DECLARATION TK_IN TK_RANGE '(' EXPR ',' EXPR ')' $@11 BLOCK
#line 615 "sintatico.y"
                        {
				materialize(yystack_[5].value.as < node > ());
				materialize(yystack_[3].value.as < node > ());

				if(yystack_[5].value.as < node > ().type.base != "int" || yystack_[3].value.as < node > ().type.base != "int") {
					report_error("Valor no intervalo in range() com tipo != int");
					return 0;
				}

				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;
				string label_continue = get_back_loop()->continue_label;

				op op_lt;
				op_lt.label = "<";

				yylhs.value.as < node > ().translation = yystack_[5].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\t" + yystack_[9].value.as < node > ().label + " = " + yystack_[5].value.as < node > ().label + ";\n";
				yylhs.value.as < node > ().translation += label_start + ":\n";
				
				node cond = gen_expr(yystack_[9].value.as < node > (), op_lt, yystack_[3].value.as < node > ());
				yylhs.value.as < node > ().translation += cond.translation;

				yylhs.value.as < node > ().translation += "\tif(!" + cond.label + ") goto " + label_end + ";\n";
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().translation;
				if(label_continue != "") yylhs.value.as < node > ().translation += label_continue + ":\n";
				yylhs.value.as < node > ().translation += "\t" + yystack_[9].value.as < node > ().label + " = " + yystack_[9].value.as < node > ().label + " + 1;\n"; 
				yylhs.value.as < node > ().translation += "\tgoto " + label_start + ";\n";
				yylhs.value.as < node > ().translation += label_end + ":\n";
				context_stack.pop_back();
			}
#line 1771 "y.tab.cc"
    break;

  case 65: // LOOPCONTROL: TK_BREAK ';'
#line 649 "sintatico.y"
                        {
				if(context_stack.empty()) {
					report_error("Break fora de loop");
					return 0;
				}
				yylhs.value.as < node > ().translation = "\tgoto " + context_stack.back().end_label + ";\n";
			}
#line 1783 "y.tab.cc"
    break;

  case 66: // LOOPCONTROL: TK_BREAK TK_INT ';'
#line 657 "sintatico.y"
                        {
				int n = stoi(yystack_[1].value.as < std::string > ());
				if(n < 1) {
					report_error("numero n invalido\n");
					return 0;
				}
				if(context_stack.size() < (size_t)n) {
					report_error("Break n é maior que a quantidade de loops\n");
					return 0;
				}
				auto& l = context_stack[context_stack.size() - n];
				yylhs.value.as < node > ().translation = "\tgoto " + l.end_label + ";\n";
			}
#line 1801 "y.tab.cc"
    break;

  case 67: // LOOPCONTROL: TK_CONTINUE ';'
#line 671 "sintatico.y"
                        {
				if(get_back_loop() == nullptr) {
					report_error("Continue fora de loop");
				}
				get_back_loop()->continue_label = gen_label_loop();
				yylhs.value.as < node > ().translation = "\tgoto " + get_back_loop()->continue_label + ";\n";
			}
#line 1813 "y.tab.cc"
    break;

  case 68: // SWITCHBLOCK: CASE_LIST
#line 681 "sintatico.y"
                        {
				yylhs.value.as < node > ().jumps = yystack_[0].value.as < node > ().jumps;
				yylhs.value.as < node > ().labels_jumps = yystack_[0].value.as < node > ().labels_jumps;
			}
#line 1822 "y.tab.cc"
    break;

  case 69: // SWITCHBLOCK: CASE_LIST DEFAULT
#line 686 "sintatico.y"
                        {
				yylhs.value.as < node > ().jumps = yystack_[1].value.as < node > ().jumps + yystack_[0].value.as < node > ().jumps;
				yylhs.value.as < node > ().labels_jumps = yystack_[1].value.as < node > ().labels_jumps + yystack_[0].value.as < node > ().labels_jumps;
			}
#line 1831 "y.tab.cc"
    break;

  case 70: // CASE_LIST: CASE_LIST CASE_ITEM
#line 693 "sintatico.y"
                        {
				yylhs.value.as < node > ().jumps = yystack_[1].value.as < node > ().jumps + yystack_[0].value.as < node > ().jumps;
				yylhs.value.as < node > ().labels_jumps = yystack_[1].value.as < node > ().labels_jumps + yystack_[0].value.as < node > ().labels_jumps;
			}
#line 1840 "y.tab.cc"
    break;

  case 71: // CASE_LIST: CASE_ITEM
#line 698 "sintatico.y"
                        {
				yylhs.value.as < node > ().jumps = yystack_[0].value.as < node > ().jumps;
				yylhs.value.as < node > ().labels_jumps = yystack_[0].value.as < node > ().labels_jumps;
			}
#line 1849 "y.tab.cc"
    break;

  case 72: // CASE_ITEM: TK_CASE EXPR ':' BLOCK
#line 705 "sintatico.y"
                        {
				string L_case = gen_label_loop();
				string end_label = get_back_switch()->end_label;
				
				materialize(yystack_[2].value.as < node > ());

				op op_eq;
				op_eq.label = "==";
				node current_switch = get_back_switch()->switch_node;
				node cmp_value = gen_expr(current_switch, op_eq, yystack_[2].value.as < node > ());
				
				yylhs.value.as < node > ().jumps = cmp_value.translation;
				yylhs.value.as < node > ().jumps += "\tif(" + cmp_value.label + ") goto " + L_case + ";\n";
				yylhs.value.as < node > ().labels_jumps = L_case + ":\n" + yystack_[0].value.as < node > ().translation + "\tgoto " + end_label + ";\n";
			}
#line 1869 "y.tab.cc"
    break;

  case 73: // DEFAULT: TK_DEFAULT ':' BLOCK
#line 723 "sintatico.y"
                        {
				string L_default = gen_label_loop();
				string end_label = get_back_switch()->end_label;

				yylhs.value.as < node > ().jumps = "\tgoto " + L_default + ";\n";
				yylhs.value.as < node > ().labels_jumps = L_default + ":\n" + yystack_[0].value.as < node > ().translation;
			}
#line 1881 "y.tab.cc"
    break;

  case 74: // IO: TK_PRINT '(' PRINT_LIST ')' ';'
#line 733 "sintatico.y"
                        {	
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
			}
#line 1889 "y.tab.cc"
    break;

  case 75: // IO: TK_PRINTL '(' PRINT_LIST ')' ';'
#line 737 "sintatico.y"
                        {	
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tprintf(\"\\n\");\n";
			}
#line 1898 "y.tab.cc"
    break;

  case 76: // IO: TK_INPUT '(' EXPR ')' ';'
#line 742 "sintatico.y"
                        {	
				string fmt;
				if(yystack_[2].value.as < node > ().type.base == "undefined") {
					promote_symbol(yystack_[2].value.as < node > (), Type("string"));
					yystack_[2].value.as < node > ().type = Type("string");
				}
				materialize(yystack_[2].value.as < node > ());
				if(yystack_[2].value.as < node > ().type.base == "string") fmt = "\"%s\", "  + yystack_[2].value.as < node > ().label;
				if(yystack_[2].value.as < node > ().type.base == "int")    fmt = "\"%d\", &" + yystack_[2].value.as < node > ().label;
				if(yystack_[2].value.as < node > ().type.base == "float")  fmt = "\"%f\", &" + yystack_[2].value.as < node > ().label;
				if(yystack_[2].value.as < node > ().type.base == "char")   fmt = "\"%c\", &" + yystack_[2].value.as < node > ().label;
				if(yystack_[2].value.as < node > ().type.base == "bool")   fmt = "\"%i\", &" + yystack_[2].value.as < node > ().label;
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tscanf(" + fmt + ");\n";
			}
#line 1918 "y.tab.cc"
    break;

  case 77: // PRINT_LIST: EXPR ',' PRINT_LIST
#line 759 "sintatico.y"
                        {
				materialize(yystack_[2].value.as < node > ());
				string type;
				if(yystack_[2].value.as < node > ().type.base == "string") type = "\"%s\"";
				if(yystack_[2].value.as < node > ().type.base == "int")    type = "\"%d\"";
				if(yystack_[2].value.as < node > ().type.base == "float")  type = "\"%f\"";
				if(yystack_[2].value.as < node > ().type.base == "char")   type = "\"%c\"";
				if(yystack_[2].value.as < node > ().type.base == "bool")   type = "\"%i\"";
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tprintf(" + type + ", " + yystack_[2].value.as < node > ().label + ");\n";
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().translation;
			}
#line 1935 "y.tab.cc"
    break;

  case 78: // PRINT_LIST: EXPR
#line 772 "sintatico.y"
                        {
				materialize(yystack_[0].value.as < node > ());
				string type;
				if(yystack_[0].value.as < node > ().type.base == "string") type = "\"%s\"";
				if(yystack_[0].value.as < node > ().type.base == "int")    type = "\"%d\"";
				if(yystack_[0].value.as < node > ().type.base == "float")  type = "\"%f\"";
				if(yystack_[0].value.as < node > ().type.base == "bool")   type = "\"%i\"";
				if(yystack_[0].value.as < node > ().type.base == "char")   type = "\"%c\"";
				yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tprintf(" + type + ", " + yystack_[0].value.as < node > ().label + ");\n";	
			}
#line 1951 "y.tab.cc"
    break;

  case 79: // PRINT_LIST: %empty
#line 785 "sintatico.y"
                                        {yylhs.value.as < node > ().translation += "\tprintf(\" \");\n";}
#line 1957 "y.tab.cc"
    break;

  case 80: // LVAL: TK_ID
#line 789 "sintatico.y"
                        {
				auto sym = lookup_symbol(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name);
				if(!sym) {
					report_error("Variável '" + yystack_[0].value.as < std::shared_ptr<symbol> > ()->name + "' não declarada.");
				}
				yylhs.value.as < node > ().type      = sym->type;
				yylhs.value.as < node > ().label     = sym->name;
				yylhs.value.as < node > ().is_static = sym->is_static;
				yylhs.value.as < node > ().translation = "";
			}
#line 1972 "y.tab.cc"
    break;

  case 81: // LVAL: TK_ID '[' EXPR ']'
#line 801 "sintatico.y"
            {
                auto sym = lookup_symbol(yystack_[3].value.as < std::shared_ptr<symbol> > ()->name);
                if(!sym)
                    report_error("Variável '" + yystack_[3].value.as < std::shared_ptr<symbol> > ()->name + "' não declarada.");
                    
                // Permite indexar se for ARRAY ou STRING
                if(sym->type.kind != Type::Kind::ARRAY && sym->type.base != "string")
                    report_error("Variável '" + yystack_[3].value.as < std::shared_ptr<symbol> > ()->name + "' não é um array nem string.");

                if(sym->label.empty()) {
                    sym->label = gen_tmp_variable();
                    push_variables(sym->label, to_ir_type(sym->type));
                }
                materialize(yystack_[1].value.as < node > ());

                yylhs.value.as < node > ().label     = sym->label + "[" + yystack_[1].value.as < node > ().label + "]";
                
                // Se a variável original for string, o destino da escrita é um 'char'
                if (sym->type.base == "string") {
                    yylhs.value.as < node > ().type = Type("char");
                } else {
                    yylhs.value.as < node > ().type = Type(sym->type.base);
                }
                
                yylhs.value.as < node > ().is_static = sym->is_static;
                yylhs.value.as < node > ().is_materialized = true; 
                yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation;
            }
#line 2005 "y.tab.cc"
    break;

  case 82: // LVAL: TK_ID '.' TK_ID
#line 831 "sintatico.y"
            {
                auto sym = lookup_symbol(yystack_[2].value.as < std::shared_ptr<symbol> > ()->name);
                if(!sym) report_error("Variável '" + yystack_[2].value.as < std::shared_ptr<symbol> > ()->name + "' não declarada.");

                // Buscar a struct pelo tipo base, não pelo nome da variavel
                auto &obj = structs[sym->type.base]; 
                string cell_type = "undefined";
                for(auto &c : obj.cells)
                    if(c.name == yystack_[0].value.as < std::shared_ptr<symbol> > ()->name) cell_type = c.type;

                yylhs.value.as < node > ().label     = sym->label + "." + yystack_[0].value.as < std::shared_ptr<symbol> > ()->name;
                yylhs.value.as < node > ().type      = Type(cell_type);
                
                yylhs.value.as < node > ().is_static = true; 
                yylhs.value.as < node > ().is_materialized = true; 
                
                yylhs.value.as < node > ().translation = "";
            }
#line 2028 "y.tab.cc"
    break;

  case 83: // RVAL: EXPR
#line 851 "sintatico.y"
                       {yylhs.value.as < node > () = yystack_[0].value.as < node > ();}
#line 2034 "y.tab.cc"
    break;

  case 84: // RVAL: TK_SBLOCK FIELD_LIST TK_EBLOCK
#line 852 "sintatico.y"
                                                         { yylhs.value.as < node > () = yystack_[1].value.as < node > (); }
#line 2040 "y.tab.cc"
    break;

  case 85: // RVAL: '[' ARRVAL ']'
#line 853 "sintatico.y"
                                         {yylhs.value.as < node > () = yystack_[1].value.as < node > ();}
#line 2046 "y.tab.cc"
    break;

  case 86: // ARRVAL: ARRVAL_
#line 855 "sintatico.y"
                      {yylhs.value.as < node > () = yystack_[0].value.as < node > ();}
#line 2052 "y.tab.cc"
    break;

  case 87: // ARRVAL: %empty
#line 856 "sintatico.y"
                                      { yylhs.value.as < node > ().type = Type(); yylhs.value.as < node > ().type.kind = Type::Kind::ARRAY; }
#line 2058 "y.tab.cc"
    break;

  case 88: // FIELD_LIST: FIELD_LIST ',' EXPR
#line 859 "sintatico.y"
                        {	
				materialize(yystack_[0].value.as < node > ());
				yylhs.value.as < node > ().type = Type("cell_struct");
				yylhs.value.as < node > ().elements = yystack_[2].value.as < node > ().elements;
				yylhs.value.as < node > ().elements.push_back(yystack_[0].value.as < node > ().label);
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation + yystack_[0].value.as < node > ().translation;				
			}
#line 2070 "y.tab.cc"
    break;

  case 89: // FIELD_LIST: EXPR
#line 867 "sintatico.y"
                        {
				materialize(yystack_[0].value.as < node > ());
				yylhs.value.as < node > ().elements.push_back(yystack_[0].value.as < node > ().label);
				yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().type = Type("cell_struct");
			}
#line 2081 "y.tab.cc"
    break;

  case 90: // ARRVAL_: ARRVAL_ ',' EXPR
#line 875 "sintatico.y"
                        {
				materialize(yystack_[2].value.as < node > ());
				if(yystack_[2].value.as < node > ().type.base != yystack_[0].value.as < node > ().type.base)
                	report_error("Elementos do array com tipos diferentes: " + yystack_[2].value.as < node > ().type.base + " e " + yystack_[0].value.as < node > ().type.base);

				yylhs.value.as < node > ().type = yystack_[2].value.as < node > ().type;
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation + yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().elements = yystack_[2].value.as < node > ().elements;
				yylhs.value.as < node > ().elements.insert(yylhs.value.as < node > ().elements.begin(), yystack_[0].value.as < node > ().label);
			}
#line 2096 "y.tab.cc"
    break;

  case 91: // ARRVAL_: EXPR
#line 886 "sintatico.y"
                        {
				materialize(yystack_[0].value.as < node > ());
				yylhs.value.as < node > ().type = Type(yystack_[0].value.as < node > ().type.base);
				yylhs.value.as < node > ().type.kind = Type::Kind::ARRAY;
				yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().elements.push_back(yystack_[0].value.as < node > ().label);

			}
#line 2109 "y.tab.cc"
    break;

  case 92: // EXPR: EXPR OP_ADD EXPR
#line 896 "sintatico.y"
                                     {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2115 "y.tab.cc"
    break;

  case 93: // EXPR: EXPR OP_MINUS EXPR
#line 897 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2121 "y.tab.cc"
    break;

  case 94: // EXPR: EXPR OP_MULT EXPR
#line 898 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2127 "y.tab.cc"
    break;

  case 95: // EXPR: EXPR OP_DIV EXPR
#line 899 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2133 "y.tab.cc"
    break;

  case 96: // EXPR: EXPR OP_MOD EXPR
#line 900 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2139 "y.tab.cc"
    break;

  case 97: // EXPR: EXPR OP_EQ EXPR
#line 901 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2145 "y.tab.cc"
    break;

  case 98: // EXPR: EXPR OP_NE EXPR
#line 902 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2151 "y.tab.cc"
    break;

  case 99: // EXPR: EXPR OP_LE EXPR
#line 903 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2157 "y.tab.cc"
    break;

  case 100: // EXPR: EXPR OP_GE EXPR
#line 904 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2163 "y.tab.cc"
    break;

  case 101: // EXPR: EXPR OP_LT EXPR
#line 905 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2169 "y.tab.cc"
    break;

  case 102: // EXPR: EXPR OP_GT EXPR
#line 906 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2175 "y.tab.cc"
    break;

  case 103: // EXPR: EXPR OP_OR EXPR
#line 907 "sintatico.y"
                                           {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2181 "y.tab.cc"
    break;

  case 104: // EXPR: EXPR OP_AND EXPR
#line 908 "sintatico.y"
                                           {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2187 "y.tab.cc"
    break;

  case 105: // EXPR: OP_NOT EXPR
#line 909 "sintatico.y"
                                       {yylhs.value.as < node > () = gen_unary("left",yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2193 "y.tab.cc"
    break;

  case 106: // EXPR: TK_CAST EXPR
#line 910 "sintatico.y"
                                       {yylhs.value.as < node > () = casting(yystack_[0].value.as < node > (),yystack_[1].value.as < std::string > ());}
#line 2199 "y.tab.cc"
    break;

  case 107: // EXPR: '(' EXPR ')'
#line 911 "sintatico.y"
                                       {yylhs.value.as < node > () = yystack_[1].value.as < node > ();}
#line 2205 "y.tab.cc"
    break;

  case 108: // EXPR: TK_INT
#line 912 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"int",yystack_[0].value.as < std::string > ());}
#line 2211 "y.tab.cc"
    break;

  case 109: // EXPR: TK_FLOAT
#line 913 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"float",yystack_[0].value.as < std::string > ());}
#line 2217 "y.tab.cc"
    break;

  case 110: // EXPR: TK_CHAR
#line 914 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"char",yystack_[0].value.as < std::string > ());}
#line 2223 "y.tab.cc"
    break;

  case 111: // EXPR: TK_BOOL
#line 915 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"bool", yystack_[0].value.as < std::string > ());}
#line 2229 "y.tab.cc"
    break;

  case 112: // EXPR: TK_STRING
#line 916 "sintatico.y"
                                    {gen_literal(yylhs.value.as < node > (), "string", yystack_[0].value.as < std::string > ());}
#line 2235 "y.tab.cc"
    break;

  case 113: // EXPR: TK_ID
#line 918 "sintatico.y"
                        {
				auto sym = lookup_symbol(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name);
				if(!sym) {
					report_error("Variável '" + yystack_[0].value.as < std::shared_ptr<symbol> > ()->name + "' não declarada.");
				}
				yylhs.value.as < node > ().label     = sym->name;
				yylhs.value.as < node > ().type      = sym->type;
				yylhs.value.as < node > ().is_static = sym->is_static;
				yylhs.value.as < node > ().translation = "";
			}
#line 2250 "y.tab.cc"
    break;

  case 114: // EXPR: TK_ID '[' EXPR ']'
#line 930 "sintatico.y"
            {
                auto sym = lookup_symbol(yystack_[3].value.as < std::shared_ptr<symbol> > ()->name);
                if(!sym) {
                    report_error("Variável '" + yystack_[3].value.as < std::shared_ptr<symbol> > ()->name + "' não declarada.");
                }
                
                // Permite indexar se for ARRAY ou STRING
                if(sym->type.kind != Type::Kind::ARRAY && sym->type.base != "string"){
                    report_error("Variável '" + yystack_[3].value.as < std::shared_ptr<symbol> > ()->name + "' não é um array nem string.");
                }
                materialize(yystack_[1].value.as < node > ());

                yylhs.value.as < node > ().label       = gen_tmp_variable();
                
                // Se a variável original for string, cada índice lido é um 'char'
                if (sym->type.base == "string") {
                    yylhs.value.as < node > ().type = Type("char");
                } else {
                    yylhs.value.as < node > ().type = Type(sym->type.base);
                }
                
                yylhs.value.as < node > ().is_static   = sym->is_static;
                yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation;
                
                push_variables(yylhs.value.as < node > ().label, to_ir_type(yylhs.value.as < node > ().type));
                yylhs.value.as < node > ().translation += "\t" + yylhs.value.as < node > ().label + " = " + sym->label + "[" + yystack_[1].value.as < node > ().label + "];\n"; 
            }
#line 2282 "y.tab.cc"
    break;

  case 115: // EXPR: TK_ID '(' ARGS_LIST ')'
#line 959 "sintatico.y"
                                {
					auto it = functions.find(yystack_[3].value.as < std::shared_ptr<symbol> > ()->name);
					if(it == functions.end()){
						report_error("Função '" + yystack_[3].value.as < std::shared_ptr<symbol> > ()->name + "' não declarada.");
					}

					else {
						yylhs.value.as < node > ().type  = Type(it->second.return_type);
						yylhs.value.as < node > ().label = gen_tmp_variable();
						push_variables(yylhs.value.as < node > ().label, it->second.ir_return_type);

						yylhs.value.as < node > ().translation  = yystack_[1].value.as < node > ().translation;
						yylhs.value.as < node > ().translation += "\t" + yylhs.value.as < node > ().label + " = " + it->second.name + "(" + yystack_[1].value.as < node > ().label + ");\n";
					}
				}
#line 2302 "y.tab.cc"
    break;

  case 116: // EXPR: TK_ID '.' TK_ID
#line 975 "sintatico.y"
                {
				auto sym = lookup_symbol(yystack_[2].value.as < std::shared_ptr<symbol> > ()->name);
				if(!sym) report_error("Variável '" + yystack_[2].value.as < std::shared_ptr<symbol> > ()->name + "' não declarada.");

				auto& obj = structs[sym->type.base];
				string cell_type = "undefined";
				for(auto& c :  obj.cells)
					if(c.name == yystack_[0].value.as < std::shared_ptr<symbol> > ()->name) cell_type = c.type;

				yylhs.value.as < node > ().label     = sym->label + "." + yystack_[0].value.as < std::shared_ptr<symbol> > ()->name;
				yylhs.value.as < node > ().type      = Type(cell_type);
				yylhs.value.as < node > ().translation = "";
		    }
#line 2320 "y.tab.cc"
    break;


#line 2324 "y.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -79;

  const signed char parser::yytable_ninf_ = -47;

  const short
  parser::yypact_[] =
  {
     149,   -13,    15,   -20,    17,   -79,     5,   -22,     4,    37,
      49,    60,    72,    92,    36,    35,   141,   149,   -79,    95,
      97,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
       3,    16,   149,   134,    87,    87,   152,   123,   -79,   -79,
     -79,   154,   -79,    87,    87,    87,    87,   150,   -79,   -79,
     -79,   -79,   -79,    87,    87,   -30,    87,   -79,    87,    87,
     125,   403,   170,    87,    87,   172,   -79,   -79,   -79,   -79,
     186,   187,    51,    51,     6,    98,   -79,   237,   256,   203,
     -79,     7,   200,   275,   174,   151,   175,   294,   -79,   -79,
       2,   403,    87,    87,   191,   -79,   313,   188,   189,   403,
     -79,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,   194,    19,   -79,   -17,   -79,   403,
     173,   -79,   -79,   -79,   -79,   -79,   -79,   182,   -79,   197,
     -79,   152,   -79,   196,   213,    47,   -79,   -79,   198,   -79,
     199,    87,   215,   216,   233,   -79,    87,    -6,   195,   -79,
     -79,   -79,    87,    99,    99,   229,   229,   -79,   116,   116,
     116,   116,   116,   116,   416,   121,   258,   220,   -79,   235,
      87,   -79,   276,    51,   268,   152,    87,    58,   238,    87,
     253,   -79,   -79,   -79,   -79,   254,    80,   -79,   403,   -79,
     -79,   403,   239,   -79,   -79,   -79,   261,   -79,   152,   -79,
     332,     6,    87,   217,   281,   297,   272,   233,   -79,   -79,
     -79,   274,   197,   387,    87,    87,   -79,   115,   -79,   -79,
     314,   -79,   -79,     7,   351,   370,   291,   -79,   -79,   -79,
     273,   -79,   152,   152,   152,   -79,   152,   -79,   -79,   -79,
     152,   -79,   -79
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,    44,     0,     0,    57,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    80,     0,     2,     4,     0,
       0,    15,    12,    13,    14,     7,     8,     9,    10,    11,
       0,    19,     0,     0,     0,     0,     0,     0,    65,    54,
      59,     0,    67,     0,    79,    79,     0,     0,   108,   109,
     110,   112,   111,     0,     0,   113,     0,    37,     0,    87,
       0,    83,     0,    42,     0,     0,     1,     3,     5,     6,
       0,     0,     0,     0,     0,     0,    47,     0,     0,     0,
      66,    53,     0,     0,     0,    78,     0,     0,    30,   106,
       0,    89,    42,     0,     0,   105,     0,     0,    86,    91,
      38,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,    41,    43,
       0,    82,    24,    25,    21,    22,    16,     0,    18,    20,
      45,     0,    55,     0,     0,    80,    52,    60,     0,    50,
       0,    79,     0,     0,    35,    84,     0,     0,     0,   116,
     107,    85,     0,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,     0,     0,    27,     0,
       0,    81,     0,     0,    49,     0,     0,     0,     0,     0,
       0,    74,    77,    75,    76,     0,     0,    34,    88,   115,
     114,    90,     0,    26,    39,    40,     0,    23,     0,    56,
       0,     0,     0,     0,     0,     0,     0,     0,    29,    17,
      48,     0,     0,     0,     0,     0,    51,    68,    71,    36,
       0,    33,    58,    53,     0,     0,     0,    70,    69,    31,
       0,    63,     0,     0,     0,    61,     0,    72,    73,    32,
       0,    64,    62
  };

  const short
  parser::yypgoto_[] =
  {
     -79,   -79,   292,   -10,   139,   -79,   -78,   -79,   -79,   226,
     -79,   -79,   -79,   -79,   135,   -79,   -79,   251,   190,   -36,
     -79,   -79,   -79,   -79,   136,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   144,   -79,   -79,   -39,
     -79,   -68,   -79,   -79,   -79,   -33
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,    16,    17,    18,   129,    19,    20,    21,   115,   116,
      22,   144,   234,   186,   187,    23,    24,   117,   118,    25,
      32,    33,    26,   180,   137,    41,    27,   175,    36,    81,
     178,   240,   236,    28,   216,   217,   218,   228,    29,    84,
      30,    60,    97,    90,    98,    61
  };

  const short
  parser::yytable_[] =
  {
      79,    77,    78,   136,   124,   125,    86,    67,    37,    39,
      83,    85,    85,    87,   126,   145,   134,   127,    31,    92,
      89,    91,    93,    95,    94,    96,    99,    40,   -46,    34,
     119,   120,   167,   169,   170,    70,    71,   128,   135,    48,
      49,    50,    51,    52,   189,   170,    53,    62,    54,    72,
     114,    42,    38,   146,    48,    49,    50,    51,    52,   119,
     148,    53,    73,    54,    74,    67,    35,    55,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,    56,    55,    57,    63,    58,    43,    64,    59,    65,
      48,    49,    50,    51,    52,   174,    56,    53,    44,    64,
      58,    65,   182,    59,    73,   197,   201,     1,    85,    45,
       2,   130,     3,   188,     4,     5,     6,     7,    55,   191,
       8,    46,     9,    47,    10,    11,    12,    13,    14,    15,
     206,   207,    56,   103,   104,   105,    58,   119,   215,   199,
     226,    66,    68,   200,    69,   136,   203,    76,   101,   102,
     103,   104,   105,   101,   102,   103,   104,   105,     1,   112,
     113,     2,   210,     3,     2,     4,     5,     6,     7,   213,
      80,     8,   100,     9,    82,    10,    11,    12,    13,    14,
      15,   224,   225,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   237,   238,   239,    88,
     241,   114,   141,   121,   242,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   122,   133,
     123,   138,   149,   172,   140,   142,   171,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     152,   151,   166,   173,   177,   176,   181,   179,   190,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   183,   184,   185,   105,   192,   193,   214,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   194,   198,   196,   202,   208,   131,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   204,   205,   209,   215,   219,   132,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     220,   222,   229,   235,    75,   139,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   233,
     212,   168,   221,   147,   143,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,     0,   230,
     195,   227,     0,   150,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     0,     0,     0,
       0,     0,   211,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,     0,     0,     0,     0,
       0,   231,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,     0,     0,     0,   232,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     0,     0,   223,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   101,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,     0,
     113
  };

  const short
  parser::yycheck_[] =
  {
      36,    34,    35,    81,    72,    73,    45,    17,     3,    31,
      43,    44,    45,    46,     8,    13,     9,    11,    31,    49,
      53,    54,    52,    56,    54,    58,    59,    49,    13,    49,
      63,    64,    13,    50,    51,    32,    33,    31,    31,     3,
       4,     5,     6,     7,    50,    51,    10,    12,    12,    46,
      31,    47,    47,    51,     3,     4,     5,     6,     7,    92,
      93,    10,    46,    12,    48,    75,    49,    31,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,    45,    31,    47,    49,    49,    49,    52,    52,    54,
       3,     4,     5,     6,     7,   131,    45,    10,    49,    52,
      49,    54,   141,    52,    46,   173,    48,     9,   141,    49,
      12,    13,    14,   146,    16,    17,    18,    19,    31,   152,
      22,    49,    24,    31,    26,    27,    28,    29,    30,    31,
      50,    51,    45,    34,    35,    36,    49,   170,    23,   175,
      25,     0,    47,   176,    47,   223,   179,    13,    32,    33,
      34,    35,    36,    32,    33,    34,    35,    36,     9,    43,
      44,    12,   198,    14,    12,    16,    17,    18,    19,   202,
      47,    22,    47,    24,    20,    26,    27,    28,    29,    30,
      31,   214,   215,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,   232,   233,   234,    49,
     236,    31,    51,    31,   240,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    32,    16,
      33,    21,    31,    41,    50,    50,    53,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      51,    53,    48,    46,    31,    49,    47,    49,    53,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    47,    47,    31,    36,     8,    47,    51,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    47,    15,     8,    47,    47,    50,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    48,    48,    42,    23,     8,    50,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      48,    47,     8,    50,    32,    50,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    48,
     201,   115,   207,    92,    50,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,   223,
     170,   217,    -1,    50,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    50,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    50,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    48,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    47,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44
  };

  const signed char
  parser::yystos_[] =
  {
       0,     9,    12,    14,    16,    17,    18,    19,    22,    24,
      26,    27,    28,    29,    30,    31,    56,    57,    58,    60,
      61,    62,    65,    70,    71,    74,    77,    81,    88,    93,
      95,    31,    75,    76,    49,    49,    83,     3,    47,    31,
      49,    80,    47,    49,    49,    49,    49,    31,     3,     4,
       5,     6,     7,    10,    12,    31,    45,    47,    49,    52,
      96,   100,    12,    49,    52,    54,     0,    58,    47,    47,
      32,    33,    46,    46,    48,    57,    13,   100,   100,    74,
      47,    84,    20,   100,    94,   100,    94,   100,    49,   100,
      98,   100,    49,    52,    54,   100,   100,    97,    99,   100,
      47,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    31,    63,    64,    72,    73,   100,
     100,    31,    32,    33,    96,    96,     8,    11,    31,    59,
      13,    50,    50,    16,     9,    31,    61,    79,    21,    50,
      50,    51,    50,    50,    66,    13,    51,    72,   100,    31,
      50,    53,    51,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,    48,    13,    64,    50,
      51,    53,    41,    46,    74,    82,    49,    31,    85,    49,
      78,    47,    94,    47,    47,    31,    68,    69,   100,    50,
      53,   100,     8,    47,    47,    73,     8,    96,    15,    74,
     100,    48,    47,   100,    48,    48,    50,    51,    47,    42,
      74,    50,    59,   100,    51,    23,    89,    90,    91,     8,
      48,    69,    47,    47,   100,   100,    25,    91,    92,     8,
      79,    50,    48,    48,    67,    50,    87,    74,    74,    74,
      86,    74,    74
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    55,    56,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    59,    59,    59,    60,
      60,    61,    61,    61,    61,    61,    62,    63,    63,    64,
      66,    67,    65,    68,    68,    68,    69,    70,    70,    71,
      72,    72,    72,    73,    75,    74,    76,    74,    77,    77,
      78,    77,    79,    79,    80,    82,    81,    83,    81,    84,
      85,    86,    81,    87,    81,    88,    88,    88,    89,    89,
      90,    90,    91,    92,    93,    93,    93,    94,    94,    94,
      95,    95,    95,    96,    96,    96,    97,    97,    98,    98,
      99,    99,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     1,     2,
       4,     3,     4,     6,     3,     3,     5,     2,     1,     4,
       0,     0,    10,     3,     1,     0,     3,     2,     3,     5,
       3,     1,     0,     1,     0,     4,     0,     3,     7,     5,
       0,     7,     1,     0,     1,     0,     6,     0,     8,     0,
       0,     0,    12,     0,    11,     2,     3,     2,     1,     2,
       2,     1,     4,     3,     5,     5,     5,     3,     1,     0,
       1,     4,     3,     1,     3,     3,     1,     0,     3,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     3,     1,     1,
       1,     1,     1,     1,     4,     4,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TK_INT", "TK_FLOAT",
  "TK_CHAR", "TK_STRING", "TK_BOOL", "TK_TYPE", "TK_VAR", "TK_CAST",
  "TK_VECTOR", "TK_SBLOCK", "TK_EBLOCK", "TK_IF", "TK_ELSE", "TK_WHILE",
  "TK_DO", "TK_BREAK", "TK_FOR", "TK_IN", "TK_RANGE", "TK_CONTINUE",
  "TK_CASE", "TK_SWITCH", "TK_DEFAULT", "TK_PRINT", "TK_PRINTL",
  "TK_INPUT", "TK_FUNCTION", "TK_RETURN", "TK_ID", "OP_ADD", "OP_MINUS",
  "OP_MULT", "OP_DIV", "OP_MOD", "OP_EQ", "OP_NE", "OP_LE", "OP_GE",
  "OP_LT", "OP_GT", "OP_OR", "OP_AND", "OP_NOT", "OP_AT", "';'", "':'",
  "'('", "')'", "','", "'['", "']'", "'.'", "$accept", "S", "COMMANDS",
  "STATEMENT", "TYPE_ANNOTATION", "DECLARATION", "ASSIGNMENT",
  "STRUCT_DEF", "CELL_LIST", "CELL", "FUNCTION_DEF", "$@1", "$@2",
  "PARAMS_LIST", "PARAM", "RETURN", "CALL_FUNC", "ARGS_LIST", "ARG",
  "BLOCK", "$@3", "$@4", "CONDITIONAL", "$@5", "OPT_ASSIGNMENT",
  "FOR_DECLARATION", "LOOP", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11",
  "LOOPCONTROL", "SWITCHBLOCK", "CASE_LIST", "CASE_ITEM", "DEFAULT", "IO",
  "PRINT_LIST", "LVAL", "RVAL", "ARRVAL", "FIELD_LIST", "ARRVAL_", "EXPR", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   174,   174,   191,   192,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   212,   214,   222,   234,
     242,   258,   279,   303,   332,   337,   345,   364,   365,   368,
     377,   380,   376,   403,   404,   405,   408,   419,   424,   432,
     447,   453,   455,   458,   461,   461,   472,   472,   479,   493,
     503,   502,   520,   521,   524,   559,   559,   576,   576,   596,
     596,   596,   596,   614,   614,   648,   656,   670,   680,   685,
     692,   697,   704,   722,   732,   736,   741,   758,   771,   785,
     788,   800,   830,   851,   852,   853,   855,   856,   858,   866,
     874,   885,   896,   897,   898,   899,   900,   901,   902,   903,
     904,   905,   906,   907,   908,   909,   910,   911,   912,   913,
     914,   915,   916,   917,   929,   958,   974
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2998 "y.tab.cc"

#line 991 "sintatico.y"


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

string gen_tamString() {
    string def  = "// Função auxiliar\nint __tamString(char* t1)";
    
    string body = "{\n"
                  "\tint t2;\n"
                  "\tint t3;\n"
                  "\tchar t4;\n"
                  "\tchar t5;\n"
                  "\tchar t6;\n"
                  "\tt2 = 0;\n"
                  "\tt3 = t2;\n"
                  "L0:\n"
                  "\tt4 = t1[t3];\n"
                  "\tt5 = '\\0\';\n" 
                  "\tt6 = t4 != t5;\n"
                  "\tif(!t6) goto L1;\n"
                  "\tt3 = t3 + 1;\n"
                  "\tgoto L0;\n"
                  "L1:\n"
                  "\treturn t3;\n"
                  "}\n";

    return def + "\n" + body + "\n";
}

string gen_assignment(node &l, node& r){
	string node_translation;
	// ARRAY
	if(r.type.kind == Type::Kind::ARRAY) {
		l.type.array_size = r.elements.size();
		node_translation += "\t" + l.label + " = (" + l.type.base + "*)";
		node_translation += " malloc(" + to_string(l.type.array_size) + " * sizeof(" + r.type.base + " ));\n";
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
		
		auto it = functions.find("tamString");
        if(it == functions.end())
		{
			functions_code += gen_tamString();
			func_data tamString;
			functions["tamString"] = tamString;
		}

		node_translation += "\t" + l.label + " = (char*) malloc(__tamString(" + r.label + " + 1));\n";
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

			// temp para os tamanhos
			string tlen_l = gen_tmp_variable();
			string tlen_r = gen_tmp_variable();
			string tsum   = gen_tmp_variable();
			string tsize  = gen_tmp_variable();
			push_variables(tlen_l, "int");
			push_variables(tlen_r, "int");
			push_variables(tsum,   "int");
			push_variables(tsize,  "int");

			n.translation  = l.translation + r.translation;
			n.translation += "\t" + tlen_l + " = __tamString(" + l.label + ");\n";
			n.translation += "\t" + tlen_r + " = __tamString(" + r.label + ");\n";
			n.translation += "\t" + tsum   + " = " + tlen_l + " + " + tlen_r + ";\n";
			n.translation += "\t" + tsize  + " = " + tsum + " + 1;\n";
			n.translation += "\t" + n.label + " = (char*) malloc(" + tsize + ");\n";
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
