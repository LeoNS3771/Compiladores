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
	#include "tokens.hh"
	#include "loops.hh"
	#include <unordered_set>
	using namespace std;

	yy::parser::symbol_type yylex();
	
	////*** Variáveis globais  ***////
	int tmp_var_count = 0;
	int cur_depth = 0;
	
	string code;
	string functions_code;
	string structs_code;

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

	////*** Pilhas ***////
	vector<map<string,shared_ptr<symbol>>> scope_stack;
	vector<loopInfo> loop_stack;
	vector<Context> context_stack;
	vector<node> switch_stack;
	vector<string> switch_end_stack;
	vector<func_data> function_stack; // Pilha para saber a função atual
	vector<unordered_set<string>> allocated_stack; // Para dar free nas variaveis alocadas


	////*** Variáveis externas ***////
	extern int yylineno;

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

#line 160 "y.tab.cc"


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
#line 233 "y.tab.cc"

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
#line 159 "sintatico.y"
                        {
				code = "/*Compilador*/\n"
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
#line 1063 "y.tab.cc"
    break;

  case 3: // COMMANDS: COMMANDS STATEMENT
#line 175 "sintatico.y"
                                     {yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation + yystack_[0].value.as < node > ().translation;}
#line 1069 "y.tab.cc"
    break;

  case 4: // COMMANDS: STATEMENT
#line 176 "sintatico.y"
                                                 {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1075 "y.tab.cc"
    break;

  case 5: // STATEMENT: DECLARATION ';'
#line 179 "sintatico.y"
                                  {yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation;}
#line 1081 "y.tab.cc"
    break;

  case 6: // STATEMENT: ASSIGNMENT ';'
#line 180 "sintatico.y"
                                          {yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation;}
#line 1087 "y.tab.cc"
    break;

  case 7: // STATEMENT: BLOCK
#line 181 "sintatico.y"
                                                  {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1093 "y.tab.cc"
    break;

  case 8: // STATEMENT: CONDITIONAL
#line 182 "sintatico.y"
                                          {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1099 "y.tab.cc"
    break;

  case 9: // STATEMENT: LOOP
#line 183 "sintatico.y"
                                                  {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1105 "y.tab.cc"
    break;

  case 10: // STATEMENT: LOOPCONTROL
#line 184 "sintatico.y"
                                          {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1111 "y.tab.cc"
    break;

  case 11: // STATEMENT: IO
#line 185 "sintatico.y"
                                              {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1117 "y.tab.cc"
    break;

  case 12: // STATEMENT: FUNCTION_DEF
#line 186 "sintatico.y"
                                          {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1123 "y.tab.cc"
    break;

  case 13: // STATEMENT: RETURN
#line 187 "sintatico.y"
                                                  {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1129 "y.tab.cc"
    break;

  case 14: // STATEMENT: CALL_FUNC
#line 188 "sintatico.y"
                                          {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1135 "y.tab.cc"
    break;

  case 15: // STATEMENT: STRUCT_DEF
#line 189 "sintatico.y"
                                          {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 1141 "y.tab.cc"
    break;

  case 16: // TYPE_ANNOTATION: TK_TYPE
#line 196 "sintatico.y"
                          {yylhs.value.as < node > ().type = Type(yystack_[0].value.as < std::string > ()); yylhs.value.as < node > ().translation = "";}
#line 1147 "y.tab.cc"
    break;

  case 17: // TYPE_ANNOTATION: TK_VECTOR OP_LT TK_TYPE OP_GT
#line 199 "sintatico.y"
                                {
					yylhs.value.as < node > ().type = Type(yystack_[1].value.as < std::string > ());
					yylhs.value.as < node > ().type.kind = Type::Kind::ARRAY;
					yylhs.value.as < node > ().translation = "";
				}
#line 1157 "y.tab.cc"
    break;

  case 18: // TYPE_ANNOTATION: TK_ID
#line 207 "sintatico.y"
                                {
					auto it = structs.find(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name);
					if(it == structs.end()){
                    report_error("Tipo '" + yystack_[0].value.as < std::shared_ptr<symbol> > ()->name + "' não é uma struct conhecida."); // Temos que padronizar as mensagens de erros...
               		}
					yylhs.value.as < node > ().type = Type(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name);
					yylhs.value.as < node > ().type.kind = Type::Kind::STRUCT;
					yylhs.value.as < node > ().translation = "";
				}
#line 1171 "y.tab.cc"
    break;

  case 19: // DECLARATION: TK_VAR TK_ID
#line 219 "sintatico.y"
                        {
				yystack_[0].value.as < std::shared_ptr<symbol> > ()->type = Type("undefined");
				yystack_[0].value.as < std::shared_ptr<symbol> > ()->is_static = false;
				yylhs.value.as < node > ().translation = "";
				register_symbol(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name, yystack_[0].value.as < std::shared_ptr<symbol> > ());
			}
#line 1182 "y.tab.cc"
    break;

  case 20: // DECLARATION: TK_VAR TK_ID ':' TYPE_ANNOTATION
#line 227 "sintatico.y"
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
#line 1199 "y.tab.cc"
    break;

  case 21: // ASSIGNMENT: LVAL OP_AT RVAL
#line 243 "sintatico.y"
                        {
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
#line 1218 "y.tab.cc"
    break;

  case 22: // ASSIGNMENT: TK_VAR TK_ID OP_AT RVAL
#line 259 "sintatico.y"
                        {
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
#line 1241 "y.tab.cc"
    break;

  case 23: // ASSIGNMENT: TK_VAR TK_ID ':' TYPE_ANNOTATION OP_AT RVAL
#line 279 "sintatico.y"
                        {
				materialize(yystack_[0].value.as < node > ());

				if(yystack_[2].value.as < node > ().type.kind != yystack_[0].value.as < node > ().type.kind || yystack_[2].value.as < node > ().type.base != yystack_[0].value.as < node > ().type.base)
					report_error("Variável '" + yystack_[4].value.as < std::shared_ptr<symbol> > ()->name + "' do tipo '" + yystack_[2].value.as < node > ().type.base +
								"' recebendo tipo '" + yystack_[0].value.as < node > ().type.base + "'");

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
#line 1268 "y.tab.cc"
    break;

  case 24: // ASSIGNMENT: LVAL OP_ADD OP_ADD
#line 303 "sintatico.y"
                        {
				materialize(yystack_[2].value.as < node > ());
				yylhs.value.as < node > ().translation = "\t" + yystack_[2].value.as < node > ().label + " = " + yystack_[2].value.as < node > ().label + " + 1;\n"; 
			}
#line 1277 "y.tab.cc"
    break;

  case 25: // ASSIGNMENT: LVAL OP_MINUS OP_MINUS
#line 308 "sintatico.y"
                        {
				materialize(yystack_[2].value.as < node > ());
				yylhs.value.as < node > ().translation = "\t" + yystack_[2].value.as < node > ().label + " = " + yystack_[2].value.as < node > ().label + " - 1;\n"; 
			}
#line 1286 "y.tab.cc"
    break;

  case 26: // STRUCT_DEF: TK_ID TK_SBLOCK CELL_LIST TK_EBLOCK ';'
#line 316 "sintatico.y"
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
#line 1307 "y.tab.cc"
    break;

  case 27: // CELL_LIST: CELL_LIST CELL
#line 334 "sintatico.y"
                                         {yylhs.value.as < node > ().translation = ""; }
#line 1313 "y.tab.cc"
    break;

  case 28: // CELL_LIST: CELL
#line 335 "sintatico.y"
                                                         {yylhs.value.as < node > ().translation = ""; }
#line 1319 "y.tab.cc"
    break;

  case 29: // CELL: TK_ID ':' TK_TYPE ';'
#line 339 "sintatico.y"
                        {
				current_cells.push_back({yystack_[3].value.as < std::shared_ptr<symbol> > ()->name, yystack_[1].value.as < std::string > ()});
				yylhs.value.as < node > ().translation = "";
			}
#line 1328 "y.tab.cc"
    break;

  case 30: // $@1: %empty
#line 347 "sintatico.y"
                        {
				open_function(yystack_[1].value.as < std::shared_ptr<symbol> > ()->name);
			}
#line 1336 "y.tab.cc"
    break;

  case 31: // $@2: %empty
#line 350 "sintatico.y"
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
#line 1356 "y.tab.cc"
    break;

  case 32: // FUNCTION_DEF: TK_FUNCTION TK_ID '(' $@1 PARAMS_LIST ')' ':' TK_TYPE $@2 BLOCK
#line 365 "sintatico.y"
                        {
				function_stack.back().translation = yystack_[0].value.as < node > ().translation;
				functions_code += close_function();
				yylhs.value.as < node > ().translation = "";
			}
#line 1366 "y.tab.cc"
    break;

  case 33: // PARAMS_LIST: PARAMS_LIST ',' PARAM
#line 373 "sintatico.y"
                                    { yylhs.value.as < node > ().translation = ""; }
#line 1372 "y.tab.cc"
    break;

  case 34: // PARAMS_LIST: PARAM
#line 374 "sintatico.y"
                                   { yylhs.value.as < node > ().translation = ""; }
#line 1378 "y.tab.cc"
    break;

  case 35: // PARAMS_LIST: %empty
#line 375 "sintatico.y"
                                    { yylhs.value.as < node > ().translation = ""; }
#line 1384 "y.tab.cc"
    break;

  case 36: // PARAM: TK_ID ':' TK_TYPE
#line 379 "sintatico.y"
                        {
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->type      = yystack_[0].value.as < std::string > ();
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->is_static = true;
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->label     = gen_tmp_variable();       
				register_symbol(yystack_[2].value.as < std::shared_ptr<symbol> > ()->name, yystack_[2].value.as < std::shared_ptr<symbol> > ());
				function_stack.back().params.push_back({yystack_[2].value.as < std::shared_ptr<symbol> > ()->label, yystack_[0].value.as < std::string > ()});
				yylhs.value.as < node > ().translation = "";
			}
#line 1397 "y.tab.cc"
    break;

  case 37: // RETURN: TK_RETURN ';'
#line 390 "sintatico.y"
                        {	
				yylhs.value.as < node > ().translation = "\treturn;\n"; 

			}
#line 1406 "y.tab.cc"
    break;

  case 38: // RETURN: TK_RETURN RVAL ';'
#line 395 "sintatico.y"
                        {
				materialize(yystack_[1].value.as < node > ());
				yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\treturn " + yystack_[1].value.as < node > ().label + ";\n";
			}
#line 1416 "y.tab.cc"
    break;

  case 39: // CALL_FUNC: TK_ID '(' ARGS_LIST ')' ';'
#line 403 "sintatico.y"
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
#line 1433 "y.tab.cc"
    break;

  case 40: // ARGS_LIST: ARGS_LIST ',' ARG
#line 418 "sintatico.y"
                        { 
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation + yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().label = yystack_[2].value.as < node > ().label + ", " + yystack_[0].value.as < node > ().label;
			}
#line 1442 "y.tab.cc"
    break;

  case 41: // ARGS_LIST: ARG
#line 423 "sintatico.y"
                                 { yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation; yylhs.value.as < node > ().label = yystack_[0].value.as < node > ().label;}
#line 1448 "y.tab.cc"
    break;

  case 42: // ARGS_LIST: %empty
#line 425 "sintatico.y"
                                 { yylhs.value.as < node > ().translation = ""; }
#line 1454 "y.tab.cc"
    break;

  case 43: // ARG: EXPR
#line 428 "sintatico.y"
                        {materialize(yystack_[0].value.as < node > ()); yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation; yylhs.value.as < node > ().label = yystack_[0].value.as < node > ().label;}
#line 1460 "y.tab.cc"
    break;

  case 44: // $@3: %empty
#line 431 "sintatico.y"
                          { open_block(); }
#line 1466 "y.tab.cc"
    break;

  case 45: // BLOCK: TK_SBLOCK $@3 COMMANDS TK_EBLOCK
#line 432 "sintatico.y"
                        {	
				auto scope_to_free = allocated_stack.back();
				close_block();

				yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation;
				for(const auto& label : scope_to_free){
					yylhs.value.as < node > ().translation += "\tfree(" + label + ");\n";
				}
			}
#line 1480 "y.tab.cc"
    break;

  case 46: // $@4: %empty
#line 442 "sintatico.y"
                                   {open_block();}
#line 1486 "y.tab.cc"
    break;

  case 47: // BLOCK: TK_SBLOCK $@4 TK_EBLOCK
#line 443 "sintatico.y"
                        {
				close_block();
				yylhs.value.as < node > ().translation = "";
			}
#line 1495 "y.tab.cc"
    break;

  case 48: // CONDITIONAL: TK_IF '(' EXPR ')' BLOCK TK_ELSE BLOCK
#line 450 "sintatico.y"
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
#line 1513 "y.tab.cc"
    break;

  case 49: // CONDITIONAL: TK_IF '(' EXPR ')' BLOCK
#line 464 "sintatico.y"
                        {
				string label_final = gen_label_loop();
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tif(!" + yystack_[2].value.as < node > ().label + ") " + "goto " + label_final + ";\n";
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += label_final + ":" + "\n";
			}
#line 1525 "y.tab.cc"
    break;

  case 50: // $@5: %empty
#line 473 "sintatico.y"
                        { 
				materialize(yystack_[1].value.as < node > ()); 
				open_switch(yystack_[1].value.as < node > ());
			}
#line 1534 "y.tab.cc"
    break;

  case 51: // CONDITIONAL: TK_SWITCH '(' EXPR ')' $@5 ':' SWITCHBLOCK
#line 477 "sintatico.y"
                        {
				string end_label = get_back_switch()->end_label;
				
				yylhs.value.as < node > ().translation = yystack_[4].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().jumps;
				yylhs.value.as < node > ().translation += "\tgoto " + end_label + ";\n";
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().labels_jumps;
				yylhs.value.as < node > ().translation += end_label + ":\n";
				
				context_stack.pop_back();	
			}
#line 1550 "y.tab.cc"
    break;

  case 52: // OPT_ASSIGNMENT: ASSIGNMENT
#line 490 "sintatico.y"
                             {yylhs.value.as < node > () = yystack_[0].value.as < node > ();}
#line 1556 "y.tab.cc"
    break;

  case 53: // OPT_ASSIGNMENT: %empty
#line 491 "sintatico.y"
                             {yylhs.value.as < node > ().translation = "";}
#line 1562 "y.tab.cc"
    break;

  case 54: // FOR_DECLARATION: TK_ID
#line 495 "sintatico.y"
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
#line 1600 "y.tab.cc"
    break;

  case 55: // $@6: %empty
#line 529 "sintatico.y"
                                        {open_loop();}
#line 1606 "y.tab.cc"
    break;

  case 56: // LOOP: TK_WHILE '(' EXPR ')' $@6 BLOCK
#line 530 "sintatico.y"
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
#line 1626 "y.tab.cc"
    break;

  case 57: // $@7: %empty
#line 546 "sintatico.y"
                                {open_loop();}
#line 1632 "y.tab.cc"
    break;

  case 58: // LOOP: TK_DO $@7 BLOCK TK_WHILE '(' EXPR ')' ';'
#line 547 "sintatico.y"
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
#line 1655 "y.tab.cc"
    break;

  case 59: // $@8: %empty
#line 566 "sintatico.y"
                                     {open_block();}
#line 1661 "y.tab.cc"
    break;

  case 60: // $@9: %empty
#line 566 "sintatico.y"
                                                                    {open_block();}
#line 1667 "y.tab.cc"
    break;

  case 61: // $@10: %empty
#line 566 "sintatico.y"
                                                                                                                    {open_loop();}
#line 1673 "y.tab.cc"
    break;

  case 62: // LOOP: TK_FOR '(' $@8 OPT_ASSIGNMENT $@9 ';' EXPR ';' OPT_ASSIGNMENT ')' $@10 BLOCK
#line 567 "sintatico.y"
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
#line 1694 "y.tab.cc"
    break;

  case 63: // $@11: %empty
#line 584 "sintatico.y"
                                                                                      {open_loop();}
#line 1700 "y.tab.cc"
    break;

  case 64: // LOOP: TK_FOR FOR_DECLARATION TK_IN TK_RANGE '(' EXPR ',' EXPR ')' $@11 BLOCK
#line 585 "sintatico.y"
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
#line 1736 "y.tab.cc"
    break;

  case 65: // LOOPCONTROL: TK_BREAK ';'
#line 619 "sintatico.y"
                        {
				if(context_stack.empty()) {
					report_error("Break fora de loop");
					return 0;
				}
				yylhs.value.as < node > ().translation = "\tgoto " + context_stack.back().end_label + ";\n";
			}
#line 1748 "y.tab.cc"
    break;

  case 66: // LOOPCONTROL: TK_BREAK TK_INT ';'
#line 627 "sintatico.y"
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
#line 1766 "y.tab.cc"
    break;

  case 67: // LOOPCONTROL: TK_CONTINUE ';'
#line 641 "sintatico.y"
                        {
				if(get_back_loop() == nullptr) {
					report_error("Continue fora de loop");
				}
				get_back_loop()->continue_label = gen_label_loop();
				yylhs.value.as < node > ().translation = "\tgoto " + get_back_loop()->continue_label + ";\n";
			}
#line 1778 "y.tab.cc"
    break;

  case 68: // SWITCHBLOCK: CASE_LIST
#line 651 "sintatico.y"
                        {
				yylhs.value.as < node > ().jumps = yystack_[0].value.as < node > ().jumps;
				yylhs.value.as < node > ().labels_jumps = yystack_[0].value.as < node > ().labels_jumps;
			}
#line 1787 "y.tab.cc"
    break;

  case 69: // SWITCHBLOCK: CASE_LIST DEFAULT
#line 656 "sintatico.y"
                        {
				yylhs.value.as < node > ().jumps = yystack_[1].value.as < node > ().jumps + yystack_[0].value.as < node > ().jumps;
				yylhs.value.as < node > ().labels_jumps = yystack_[1].value.as < node > ().labels_jumps + yystack_[0].value.as < node > ().labels_jumps;
			}
#line 1796 "y.tab.cc"
    break;

  case 70: // CASE_LIST: CASE_LIST CASE_ITEM
#line 663 "sintatico.y"
                        {
				yylhs.value.as < node > ().jumps = yystack_[1].value.as < node > ().jumps + yystack_[0].value.as < node > ().jumps;
				yylhs.value.as < node > ().labels_jumps = yystack_[1].value.as < node > ().labels_jumps + yystack_[0].value.as < node > ().labels_jumps;
			}
#line 1805 "y.tab.cc"
    break;

  case 71: // CASE_LIST: CASE_ITEM
#line 668 "sintatico.y"
                        {
				yylhs.value.as < node > ().jumps = yystack_[0].value.as < node > ().jumps;
				yylhs.value.as < node > ().labels_jumps = yystack_[0].value.as < node > ().labels_jumps;
			}
#line 1814 "y.tab.cc"
    break;

  case 72: // CASE_ITEM: TK_CASE EXPR ':' BLOCK
#line 675 "sintatico.y"
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
#line 1834 "y.tab.cc"
    break;

  case 73: // DEFAULT: TK_DEFAULT ':' BLOCK
#line 693 "sintatico.y"
                        {
				string L_default = gen_label_loop();
				string end_label = get_back_switch()->end_label;

				yylhs.value.as < node > ().jumps = "\tgoto " + L_default + ";\n";
				yylhs.value.as < node > ().labels_jumps = L_default + ":\n" + yystack_[0].value.as < node > ().translation;
			}
#line 1846 "y.tab.cc"
    break;

  case 74: // IO: TK_PRINT '(' PRINT_LIST ')' ';'
#line 703 "sintatico.y"
                        {	
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
			}
#line 1854 "y.tab.cc"
    break;

  case 75: // IO: TK_PRINTL '(' PRINT_LIST ')' ';'
#line 707 "sintatico.y"
                        {	
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tprintf(\"\\n\");\n";
			}
#line 1863 "y.tab.cc"
    break;

  case 76: // IO: TK_INPUT '(' EXPR ')' ';'
#line 712 "sintatico.y"
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
#line 1883 "y.tab.cc"
    break;

  case 77: // PRINT_LIST: EXPR ',' PRINT_LIST
#line 729 "sintatico.y"
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
#line 1900 "y.tab.cc"
    break;

  case 78: // PRINT_LIST: EXPR
#line 742 "sintatico.y"
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
#line 1916 "y.tab.cc"
    break;

  case 79: // LVAL: TK_ID
#line 756 "sintatico.y"
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
#line 1931 "y.tab.cc"
    break;

  case 80: // LVAL: TK_ID '[' EXPR ']'
#line 768 "sintatico.y"
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
#line 1964 "y.tab.cc"
    break;

  case 81: // LVAL: TK_ID '.' TK_ID
#line 798 "sintatico.y"
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
#line 1987 "y.tab.cc"
    break;

  case 82: // RVAL: EXPR
#line 818 "sintatico.y"
                       {yylhs.value.as < node > () = yystack_[0].value.as < node > ();}
#line 1993 "y.tab.cc"
    break;

  case 83: // RVAL: '[' ARRVAL ']'
#line 820 "sintatico.y"
                                         {yylhs.value.as < node > () = yystack_[1].value.as < node > ();}
#line 1999 "y.tab.cc"
    break;

  case 84: // ARRVAL: ARRVAL_
#line 822 "sintatico.y"
                      {yylhs.value.as < node > () = yystack_[0].value.as < node > ();}
#line 2005 "y.tab.cc"
    break;

  case 85: // ARRVAL: %empty
#line 823 "sintatico.y"
                                      { yylhs.value.as < node > ().type = Type(); yylhs.value.as < node > ().type.kind = Type::Kind::ARRAY; }
#line 2011 "y.tab.cc"
    break;

  case 86: // ARRVAL_: EXPR
#line 826 "sintatico.y"
                        {
				materialize(yystack_[0].value.as < node > ());
				yylhs.value.as < node > ().type = Type(yystack_[0].value.as < node > ().type.base);
				yylhs.value.as < node > ().type.kind = Type::Kind::ARRAY;
				yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().elements.push_back(yystack_[0].value.as < node > ().label);

			}
#line 2024 "y.tab.cc"
    break;

  case 87: // ARRVAL_: EXPR ',' ARRVAL_
#line 835 "sintatico.y"
                        {
				materialize(yystack_[2].value.as < node > ());
				if(yystack_[2].value.as < node > ().type.base != yystack_[0].value.as < node > ().type.base)
                	report_error("Elementos do array com tipos diferentes: " + yystack_[2].value.as < node > ().type.base + " e " + yystack_[0].value.as < node > ().type.base);

				yylhs.value.as < node > ().type = yystack_[0].value.as < node > ().type;
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation + yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().elements = yystack_[0].value.as < node > ().elements;
				yylhs.value.as < node > ().elements.insert(yylhs.value.as < node > ().elements.begin(), yystack_[2].value.as < node > ().label);
			}
#line 2039 "y.tab.cc"
    break;

  case 88: // EXPR: EXPR OP_ADD EXPR
#line 846 "sintatico.y"
                                     {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2045 "y.tab.cc"
    break;

  case 89: // EXPR: EXPR OP_MINUS EXPR
#line 847 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2051 "y.tab.cc"
    break;

  case 90: // EXPR: EXPR OP_MULT EXPR
#line 848 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2057 "y.tab.cc"
    break;

  case 91: // EXPR: EXPR OP_DIV EXPR
#line 849 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2063 "y.tab.cc"
    break;

  case 92: // EXPR: EXPR OP_MOD EXPR
#line 850 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2069 "y.tab.cc"
    break;

  case 93: // EXPR: EXPR OP_EQ EXPR
#line 851 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2075 "y.tab.cc"
    break;

  case 94: // EXPR: EXPR OP_NE EXPR
#line 852 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2081 "y.tab.cc"
    break;

  case 95: // EXPR: EXPR OP_LE EXPR
#line 853 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2087 "y.tab.cc"
    break;

  case 96: // EXPR: EXPR OP_GE EXPR
#line 854 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2093 "y.tab.cc"
    break;

  case 97: // EXPR: EXPR OP_LT EXPR
#line 855 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2099 "y.tab.cc"
    break;

  case 98: // EXPR: EXPR OP_GT EXPR
#line 856 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2105 "y.tab.cc"
    break;

  case 99: // EXPR: EXPR OP_OR EXPR
#line 857 "sintatico.y"
                                           {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2111 "y.tab.cc"
    break;

  case 100: // EXPR: EXPR OP_AND EXPR
#line 858 "sintatico.y"
                                           {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2117 "y.tab.cc"
    break;

  case 101: // EXPR: OP_NOT EXPR
#line 859 "sintatico.y"
                                       {yylhs.value.as < node > () = gen_unary("left",yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 2123 "y.tab.cc"
    break;

  case 102: // EXPR: TK_CAST EXPR
#line 860 "sintatico.y"
                                       {yylhs.value.as < node > () = casting(yystack_[0].value.as < node > (),yystack_[1].value.as < std::string > ());}
#line 2129 "y.tab.cc"
    break;

  case 103: // EXPR: '(' EXPR ')'
#line 861 "sintatico.y"
                                       {yylhs.value.as < node > () = yystack_[1].value.as < node > ();}
#line 2135 "y.tab.cc"
    break;

  case 104: // EXPR: TK_INT
#line 862 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"int",yystack_[0].value.as < std::string > ());}
#line 2141 "y.tab.cc"
    break;

  case 105: // EXPR: TK_FLOAT
#line 863 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"float",yystack_[0].value.as < std::string > ());}
#line 2147 "y.tab.cc"
    break;

  case 106: // EXPR: TK_CHAR
#line 864 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"char",yystack_[0].value.as < std::string > ());}
#line 2153 "y.tab.cc"
    break;

  case 107: // EXPR: TK_BOOL
#line 865 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"bool", yystack_[0].value.as < std::string > ());}
#line 2159 "y.tab.cc"
    break;

  case 108: // EXPR: TK_STRING
#line 866 "sintatico.y"
                                    {gen_literal(yylhs.value.as < node > (), "string", yystack_[0].value.as < std::string > ());}
#line 2165 "y.tab.cc"
    break;

  case 109: // EXPR: TK_ID
#line 868 "sintatico.y"
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
#line 2180 "y.tab.cc"
    break;

  case 110: // EXPR: TK_ID '[' EXPR ']'
#line 880 "sintatico.y"
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
#line 2212 "y.tab.cc"
    break;

  case 111: // EXPR: TK_ID '(' ARGS_LIST ')'
#line 909 "sintatico.y"
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
#line 2232 "y.tab.cc"
    break;

  case 112: // EXPR: TK_ID '.' TK_ID
#line 925 "sintatico.y"
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
#line 2250 "y.tab.cc"
    break;


#line 2254 "y.tab.cc"

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


  const signed char parser::yypact_ninf_ = -78;

  const signed char parser::yytable_ninf_ = -47;

  const short
  parser::yypact_[] =
  {
     187,    -8,    15,   -17,    -7,   -78,    12,   -15,    16,    29,
      45,    47,    49,     8,    48,    -4,   102,   187,   -78,    56,
      57,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
      -6,   -27,   187,    93,   106,   106,    95,    68,   -78,   -78,
     -78,   103,   -78,   106,   106,   106,   106,    75,   -78,   -78,
     -78,   -78,   -78,   106,   -11,   106,   -78,   106,   106,    78,
     458,    96,   106,   106,    97,   -78,   -78,   -78,   -78,    98,
     100,    77,    77,     6,   155,   -78,   292,   311,   115,   -78,
       0,   114,   330,    86,   232,    89,   349,   -78,   -78,   106,
     106,   116,   -78,   368,    99,   -78,   252,   -78,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   101,     5,   -78,    35,   -78,   458,   188,   -78,   -78,
     -78,   -78,   -78,   -78,   107,   -78,   104,   -78,    95,   -78,
     108,   134,   -19,   -78,   -78,   117,   -78,   131,   106,   133,
     140,   157,    38,   210,   -78,   -78,   -78,   106,    26,    26,
     153,   153,   -78,   110,   110,   110,   110,   110,   110,   126,
      85,   185,   148,   -78,   150,   106,   -78,   192,    77,   193,
      95,   106,    -2,   160,   106,   154,   -78,   -78,   -78,   -78,
     162,    40,   -78,   -78,   -78,   -78,   165,   -78,   -78,   -78,
     177,   -78,    95,   -78,   387,     6,   106,   272,   211,   225,
     189,   157,   -78,   -78,   -78,   191,   104,   442,   106,   106,
     -78,    24,   -78,   -78,   227,   -78,   -78,     0,   406,   425,
     207,   -78,   -78,   -78,   186,   -78,    95,    95,    95,   -78,
      95,   -78,   -78,   -78,    95,   -78,   -78
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,    44,     0,     0,    57,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    79,     0,     2,     4,     0,
       0,    15,    12,    13,    14,     7,     8,     9,    10,    11,
       0,    19,     0,     0,     0,     0,     0,     0,    65,    54,
      59,     0,    67,     0,     0,     0,     0,     0,   104,   105,
     106,   108,   107,     0,   109,     0,    37,     0,    85,     0,
      82,     0,    42,     0,     0,     1,     3,     5,     6,     0,
       0,     0,     0,     0,     0,    47,     0,     0,     0,    66,
      53,     0,     0,     0,    78,     0,     0,    30,   102,    42,
       0,     0,   101,     0,     0,    84,    86,    38,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    28,     0,    41,    43,     0,    81,    24,
      25,    21,    22,    16,     0,    18,    20,    45,     0,    55,
       0,     0,    79,    52,    60,     0,    50,     0,     0,     0,
       0,    35,     0,     0,   112,   103,    83,     0,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,     0,     0,    27,     0,     0,    80,     0,     0,    49,
       0,     0,     0,     0,     0,     0,    74,    77,    75,    76,
       0,     0,    34,   111,   110,    87,     0,    26,    39,    40,
       0,    23,     0,    56,     0,     0,     0,     0,     0,     0,
       0,     0,    29,    17,    48,     0,     0,     0,     0,     0,
      51,    68,    71,    36,     0,    33,    58,    53,     0,     0,
       0,    70,    69,    31,     0,    63,     0,     0,     0,    61,
       0,    72,    73,    32,     0,    64,    62
  };

  const short
  parser::yypgoto_[] =
  {
     -78,   -78,   208,   -10,    44,   -78,   -77,   -78,   -78,   144,
     -78,   -78,   -78,   -78,    58,   -78,   -78,   168,   112,   -36,
     -78,   -78,   -78,   -78,    41,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,    50,   -78,   -78,   -39,
     -78,   -67,   -78,   113,   -33
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,    16,    17,    18,   126,    19,    20,    21,   112,   113,
      22,   141,   228,   181,   182,    23,    24,   114,   115,    25,
      32,    33,    26,   175,   134,    41,    27,   170,    36,    80,
     173,   234,   230,    28,   210,   211,   212,   222,    29,    83,
      30,    59,    94,    95,    60
  };

  const short
  parser::yytable_[] =
  {
      78,    76,    77,   133,   121,   122,    85,    66,    61,   131,
      82,    84,    84,    86,   123,    37,    39,   124,   162,    72,
      88,    73,    92,    31,    93,    96,    69,    70,   -46,   116,
     117,   132,    34,    63,    40,    64,   111,   125,    89,    47,
      71,    90,    35,    91,    72,    62,   195,   209,    63,   220,
      64,    48,    49,    50,    51,    52,   116,   143,    53,    38,
     100,   101,   102,    42,    66,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,    43,    54,
      48,    49,    50,    51,    52,   164,   165,    53,   183,   165,
     200,   201,   169,    55,    44,    56,    45,    57,    46,   177,
      58,   191,    65,    67,    68,    84,    75,     2,    54,    48,
      49,    50,    51,    52,    96,    79,    53,    98,    99,   100,
     101,   102,    55,    81,    87,    97,    57,   111,   118,    58,
     119,   130,   116,   120,   193,   135,   137,    54,   194,   139,
     133,   197,    98,    99,   100,   101,   102,   144,   167,   161,
     168,    55,   146,   109,   110,    57,   204,   171,    98,    99,
     100,   101,   102,   207,     1,   172,   174,     2,   127,     3,
     110,     4,     5,     6,     7,   218,   219,     8,   176,     9,
     178,    10,    11,    12,    13,    14,    15,   179,   180,   102,
     231,   232,   233,   186,   235,   187,     1,   188,   236,     2,
     190,     3,   198,     4,     5,     6,     7,   196,   192,     8,
     199,     9,   202,    10,    11,    12,    13,    14,    15,   203,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   213,   209,   223,   229,   214,   216,   206,
      74,   166,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   227,   163,   142,   224,   215,
     185,   221,     0,   184,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   189,     0,     0,
       0,     0,     0,   138,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,     0,     0,     0,
       0,     0,     0,   147,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,     0,     0,     0,
       0,     0,     0,   208,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,     0,     0,     0,
       0,     0,   128,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,     0,     0,     0,     0,
       0,   129,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,     0,     0,     0,     0,     0,
     136,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,     0,     0,     0,     0,     0,   140,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,     0,     0,     0,     0,     0,   145,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     0,     0,     0,     0,     0,   205,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,     0,     0,     0,     0,     0,   225,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
       0,     0,     0,   226,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,     0,     0,   217,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110
  };

  const short
  parser::yycheck_[] =
  {
      36,    34,    35,    80,    71,    72,    45,    17,    12,     9,
      43,    44,    45,    46,     8,     3,    31,    11,    13,    46,
      53,    48,    55,    31,    57,    58,    32,    33,    13,    62,
      63,    31,    49,    52,    49,    54,    31,    31,    49,    31,
      46,    52,    49,    54,    46,    49,    48,    23,    52,    25,
      54,     3,     4,     5,     6,     7,    89,    90,    10,    47,
      34,    35,    36,    47,    74,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,    49,    31,
       3,     4,     5,     6,     7,    50,    51,    10,    50,    51,
      50,    51,   128,    45,    49,    47,    49,    49,    49,   138,
      52,   168,     0,    47,    47,   138,    13,    12,    31,     3,
       4,     5,     6,     7,   147,    47,    10,    32,    33,    34,
      35,    36,    45,    20,    49,    47,    49,    31,    31,    52,
      32,    16,   165,    33,   170,    21,    50,    31,   171,    50,
     217,   174,    32,    33,    34,    35,    36,    31,    41,    48,
      46,    45,    53,    43,    44,    49,   192,    49,    32,    33,
      34,    35,    36,   196,     9,    31,    49,    12,    13,    14,
      44,    16,    17,    18,    19,   208,   209,    22,    47,    24,
      47,    26,    27,    28,    29,    30,    31,    47,    31,    36,
     226,   227,   228,     8,   230,    47,     9,    47,   234,    12,
       8,    14,    48,    16,    17,    18,    19,    47,    15,    22,
      48,    24,    47,    26,    27,    28,    29,    30,    31,    42,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,     8,    23,     8,    50,    48,    47,   195,
      32,    53,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    48,   112,    89,   217,   201,
     147,   211,    -1,    53,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,   165,    -1,    -1,
      -1,    -1,    -1,    51,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    50,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    50,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      50,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    50,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    50,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    50,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    50,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    48,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    47,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44
  };

  const signed char
  parser::yystos_[] =
  {
       0,     9,    12,    14,    16,    17,    18,    19,    22,    24,
      26,    27,    28,    29,    30,    31,    56,    57,    58,    60,
      61,    62,    65,    70,    71,    74,    77,    81,    88,    93,
      95,    31,    75,    76,    49,    49,    83,     3,    47,    31,
      49,    80,    47,    49,    49,    49,    49,    31,     3,     4,
       5,     6,     7,    10,    31,    45,    47,    49,    52,    96,
      99,    12,    49,    52,    54,     0,    58,    47,    47,    32,
      33,    46,    46,    48,    57,    13,    99,    99,    74,    47,
      84,    20,    99,    94,    99,    94,    99,    49,    99,    49,
      52,    54,    99,    99,    97,    98,    99,    47,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    31,    63,    64,    72,    73,    99,    99,    31,    32,
      33,    96,    96,     8,    11,    31,    59,    13,    50,    50,
      16,     9,    31,    61,    79,    21,    50,    50,    51,    50,
      50,    66,    72,    99,    31,    50,    53,    51,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    48,    13,    64,    50,    51,    53,    41,    46,    74,
      82,    49,    31,    85,    49,    78,    47,    94,    47,    47,
      31,    68,    69,    50,    53,    98,     8,    47,    47,    73,
       8,    96,    15,    74,    99,    48,    47,    99,    48,    48,
      50,    51,    47,    42,    74,    50,    59,    99,    51,    23,
      89,    90,    91,     8,    48,    69,    47,    47,    99,    99,
      25,    91,    92,     8,    79,    50,    48,    48,    67,    50,
      87,    74,    74,    74,    86,    74,    74
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
      90,    90,    91,    92,    93,    93,    93,    94,    94,    95,
      95,    95,    96,    96,    97,    97,    98,    98,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99
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
       2,     1,     4,     3,     5,     5,     5,     3,     1,     1,
       4,     3,     1,     3,     1,     0,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     3,     1,     1,     1,     1,     1,     1,
       4,     4,     3
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
  "PRINT_LIST", "LVAL", "RVAL", "ARRVAL", "ARRVAL_", "EXPR", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   158,   158,   175,   176,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   196,   198,   206,   218,
     226,   242,   258,   278,   302,   307,   315,   334,   335,   338,
     347,   350,   346,   373,   374,   375,   378,   389,   394,   402,
     417,   423,   425,   428,   431,   431,   442,   442,   449,   463,
     473,   472,   490,   491,   494,   529,   529,   546,   546,   566,
     566,   566,   566,   584,   584,   618,   626,   640,   650,   655,
     662,   667,   674,   692,   702,   706,   711,   728,   741,   755,
     767,   797,   818,   820,   822,   823,   825,   834,   846,   847,
     848,   849,   850,   851,   852,   853,   854,   855,   856,   857,
     858,   859,   860,   861,   862,   863,   864,   865,   866,   867,
     879,   908,   924
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
#line 2933 "y.tab.cc"

#line 940 "sintatico.y"


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
	function_stack.push_back(f);
	f.saved_tmp_count = tmp_var_count;
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

int main(int argc, char* argv[]) {
	tmp_var_count = 0;
	yy::parser p;
	open_block();
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
