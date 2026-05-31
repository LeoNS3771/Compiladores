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

#line 117 "y.tab.cc"


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
#line 190 "y.tab.cc"

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
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
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
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
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
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
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
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
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
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
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
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
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
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
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
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
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
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
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
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
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
#line 113 "sintatico.y"
                        {
				code = "/*Compilador*/\n"
				"#include <stdio.h>\n"
				"#include <string.h>\n"
				"#include <stdlib.h>\n\n";

				code += "int main(void) {\n";
				code += gen_declarations();
				code += "\n" + yystack_[0].value.as < node > ().translation;
				code += "\treturn 0;\n}\n";
			}
#line 931 "y.tab.cc"
    break;

  case 3: // COMMANDS: COMMANDS STATEMENT
#line 125 "sintatico.y"
                                     {yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation + yystack_[0].value.as < node > ().translation;}
#line 937 "y.tab.cc"
    break;

  case 4: // COMMANDS: STATEMENT
#line 126 "sintatico.y"
                                                 {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 943 "y.tab.cc"
    break;

  case 5: // STATEMENT: DECLARATION
#line 129 "sintatico.y"
                                 {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 949 "y.tab.cc"
    break;

  case 6: // STATEMENT: ASSIGNMENT ';'
#line 130 "sintatico.y"
                                         {yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation;}
#line 955 "y.tab.cc"
    break;

  case 7: // STATEMENT: BLOCK
#line 131 "sintatico.y"
                                                 {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 961 "y.tab.cc"
    break;

  case 8: // STATEMENT: CONDITIONAL
#line 132 "sintatico.y"
                                         {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 967 "y.tab.cc"
    break;

  case 9: // STATEMENT: LOOP
#line 133 "sintatico.y"
                                                 {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 973 "y.tab.cc"
    break;

  case 10: // STATEMENT: LOOPCONTROL
#line 134 "sintatico.y"
                                         {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 979 "y.tab.cc"
    break;

  case 11: // STATEMENT: IO
#line 135 "sintatico.y"
                                             {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 985 "y.tab.cc"
    break;

  case 12: // DECLARATION: TK_VAR TK_ID ';'
#line 138 "sintatico.y"
                        {

				yystack_[1].value.as < std::shared_ptr<symbol> > ()->type = "undefined";
				yystack_[1].value.as < std::shared_ptr<symbol> > ()->is_static = false;
				yylhs.value.as < node > ().translation = "";

				register_symbol(yystack_[1].value.as < std::shared_ptr<symbol> > ()->name, yystack_[1].value.as < std::shared_ptr<symbol> > ());
			}
#line 998 "y.tab.cc"
    break;

  case 13: // DECLARATION: TK_VAR TK_ID ':' TK_TYPE ';'
#line 148 "sintatico.y"
                        {
				yystack_[3].value.as < std::shared_ptr<symbol> > ()->type = yystack_[1].value.as < std::string > ();
				yystack_[3].value.as < std::shared_ptr<symbol> > ()->is_static = true;
				yylhs.value.as < node > ().translation = "";
				register_symbol(yystack_[3].value.as < std::shared_ptr<symbol> > ()->name, yystack_[3].value.as < std::shared_ptr<symbol> > ());
			}
#line 1009 "y.tab.cc"
    break;

  case 14: // ASSIGNMENT: LVAL OP_AT RVAL
#line 156 "sintatico.y"
                        {
				
				// Se for estático não pode receber um tipo diferente do definido
				if(yystack_[2].value.as < node > ().is_static) {
					if(yystack_[0].value.as < node > ().type != yystack_[2].value.as < node > ().type){
						report_error("Variavel '" + yystack_[2].value.as < node > ().label + "' do tipo estatico'" + yystack_[2].value.as < node > ().type + "' recebendo outro tipo '" + yystack_[0].value.as < node > ().type + "'"); // Colocar uma mensagem condizente
					}
				}

				materialize(yystack_[0].value.as < node > ());
				promote_symbol(yystack_[2].value.as < node > (),yystack_[0].value.as < node > ().type);
				materialize(yystack_[2].value.as < node > ());

				// Se for string, atribuição é usando strcpy
				if(yystack_[0].value.as < node > ().type == "string"){
					yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation + yystack_[2].value.as < node > ().translation;
					yylhs.value.as < node > ().translation += "\t" + yystack_[2].value.as < node > ().label + " = (char*) malloc(4096);\n";
					yylhs.value.as < node > ().translation += "\tstrcpy(" + yystack_[2].value.as < node > ().label + ", " + yystack_[0].value.as < node > ().label + ");\n";
				}

				else{
					//coercion($1,$3); 
					yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation + yystack_[2].value.as < node > ().translation;
					yylhs.value.as < node > ().translation += "\t" + yystack_[2].value.as < node > ().label + " = " + yystack_[0].value.as < node > ().label + ";\n";
				}
			}
#line 1040 "y.tab.cc"
    break;

  case 15: // ASSIGNMENT: TK_VAR TK_ID OP_AT RVAL
#line 184 "sintatico.y"
                        {

				materialize(yystack_[0].value.as < node > ());
				// Materializando manualmente
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->is_static = false;
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->type = yystack_[0].value.as < node > ().type;
				yystack_[2].value.as < std::shared_ptr<symbol> > ()->label = gen_tmp_variable();
				variables.push_back({yystack_[2].value.as < std::shared_ptr<symbol> > ()->label, to_ir_type(yystack_[2].value.as < std::shared_ptr<symbol> > ()->type)});

				register_symbol(yystack_[2].value.as < std::shared_ptr<symbol> > ()->name, yystack_[2].value.as < std::shared_ptr<symbol> > ());
				yylhs.value.as < node > ().translation = yylhs.value.as < node > ().translation + yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += '\t' + yystack_[2].value.as < std::shared_ptr<symbol> > ()->label + " = " + yystack_[0].value.as < node > ().label + ";\n";

			}
#line 1059 "y.tab.cc"
    break;

  case 16: // ASSIGNMENT: TK_VAR TK_ID ':' TK_TYPE OP_AT RVAL
#line 200 "sintatico.y"
                        {
				
				materialize(yystack_[0].value.as < node > ());
				if(yystack_[2].value.as < std::string > () != yystack_[0].value.as < node > ().type)
				 	report_error("Variável '" + yystack_[4].value.as < std::shared_ptr<symbol> > ()->name + "' do tipo '" + yystack_[2].value.as < std::string > () + "' recebendo " + "tipo '" + yystack_[0].value.as < node > ().type + "'");
				
				yystack_[4].value.as < std::shared_ptr<symbol> > ()->type = yystack_[2].value.as < std::string > ();
				yystack_[4].value.as < std::shared_ptr<symbol> > ()->is_static = true;

				
				yystack_[4].value.as < std::shared_ptr<symbol> > ()->label = gen_tmp_variable();
				variables.push_back({yystack_[4].value.as < std::shared_ptr<symbol> > ()->label, to_ir_type(yystack_[4].value.as < std::shared_ptr<symbol> > ()->type)});
				
				if(yystack_[4].value.as < std::shared_ptr<symbol> > ()->type == "string"){
					yylhs.value.as < node > ().translation += "\t" + yystack_[4].value.as < std::shared_ptr<symbol> > ()->label + " = (char*) malloc(4096);\n";
					yylhs.value.as < node > ().translation += "\t" + yystack_[4].value.as < std::shared_ptr<symbol> > ()->label + "[0] = '\\0';\n";
				}

				register_symbol(yystack_[4].value.as < std::shared_ptr<symbol> > ()->name, yystack_[4].value.as < std::shared_ptr<symbol> > ());
				yylhs.value.as < node > ().translation = yylhs.value.as < node > ().translation + yystack_[0].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += '\t' + yystack_[4].value.as < std::shared_ptr<symbol> > ()->label + " = " + yystack_[0].value.as < node > ().label + ";\n";

			}
#line 1087 "y.tab.cc"
    break;

  case 17: // ASSIGNMENT: LVAL OP_ADD OP_ADD
#line 224 "sintatico.y"
                        {
				materialize(yystack_[2].value.as < node > ());
				yylhs.value.as < node > ().translation = "\t" + yystack_[2].value.as < node > ().label + " = " + yystack_[2].value.as < node > ().label + " + 1;\n"; 
			}
#line 1096 "y.tab.cc"
    break;

  case 18: // ASSIGNMENT: LVAL OP_MINUS OP_MINUS
#line 229 "sintatico.y"
                        {
				materialize(yystack_[2].value.as < node > ());
				yylhs.value.as < node > ().translation = "\t" + yystack_[2].value.as < node > ().label + " = " + yystack_[2].value.as < node > ().label + " - 1;\n"; 
			}
#line 1105 "y.tab.cc"
    break;

  case 19: // $@1: %empty
#line 235 "sintatico.y"
                          { open_block(); }
#line 1111 "y.tab.cc"
    break;

  case 20: // BLOCK: TK_SBLOCK $@1 COMMANDS TK_EBLOCK
#line 236 "sintatico.y"
                        {
				close_block();

				yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation;
			}
#line 1121 "y.tab.cc"
    break;

  case 21: // $@2: %empty
#line 243 "sintatico.y"
                                   {open_block();}
#line 1127 "y.tab.cc"
    break;

  case 22: // BLOCK: TK_SBLOCK $@2 TK_EBLOCK
#line 244 "sintatico.y"
                        {
				close_block();
				yylhs.value.as < node > ().translation = "";
			}
#line 1136 "y.tab.cc"
    break;

  case 23: // CONDITIONAL: TK_IF '(' EXPR ')' BLOCK TK_ELSE BLOCK
#line 253 "sintatico.y"
                        {
				string label_if = gen_label_loop();
				string label_else = gen_label_loop();

				materialize(yystack_[4].value.as < node > ());
				yylhs.value.as < node > ().translation = yystack_[4].value.as < node > ().translation;

				yylhs.value.as < node > ().translation += "\tif(!" + yystack_[4].value.as < node > ().label + ") " + "goto " + label_else + ";\n";
				
				yylhs.value.as < node > ().translation += yystack_[2].value.as < node > ().translation + "\n"; // Bloco do if

				yylhs.value.as < node > ().translation += "\tgoto " + label_if + ";\n";// Se entrou no if, vá para fora depois de terminar
				
				// Labels
				yylhs.value.as < node > ().translation += label_else + ":" + "\n" + yystack_[0].value.as < node > ().translation + "\n"; // Label do else
				
				yylhs.value.as < node > ().translation += label_if + ":\n"; // Label de saida
				
			}
#line 1160 "y.tab.cc"
    break;

  case 24: // CONDITIONAL: TK_IF '(' EXPR ')' BLOCK
#line 273 "sintatico.y"
                        {
				string label_final = gen_label_loop();
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tif(!" + yystack_[2].value.as < node > ().label + ") " + "goto " + label_final + ";\n";
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().translation ; // Bloco do if

				// Labels
				yylhs.value.as < node > ().translation += label_final + ":" + "\n";
				
			}
#line 1175 "y.tab.cc"
    break;

  case 25: // $@3: %empty
#line 285 "sintatico.y"
                        { 
				materialize(yystack_[1].value.as < node > ()); 
				open_switch(yystack_[1].value.as < node > ());
			}
#line 1184 "y.tab.cc"
    break;

  case 26: // CONDITIONAL: TK_SWITCH '(' EXPR ')' $@3 ':' SWITCHBLOCK
#line 289 "sintatico.y"
                        {
				string end_label = get_back_switch()->end_label;
				
				yylhs.value.as < node > ().translation = yystack_[4].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().jumps; // adiciona todos os if's primeiro
				yylhs.value.as < node > ().translation += "\tgoto " + end_label + ";\n"; // Depois de todos os ifs vai para a label de saida
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().labels_jumps; // Labels + blocos
				yylhs.value.as < node > ().translation += end_label + ":\n"; // sempre vai para a label de saida
				
				context_stack.pop_back();	
			}
#line 1200 "y.tab.cc"
    break;

  case 27: // OPT_ASSIGNMENT: ASSIGNMENT
#line 302 "sintatico.y"
                             {yylhs.value.as < node > () = yystack_[0].value.as < node > ();}
#line 1206 "y.tab.cc"
    break;

  case 28: // OPT_ASSIGNMENT: %empty
#line 303 "sintatico.y"
                             {yylhs.value.as < node > ().translation = "";}
#line 1212 "y.tab.cc"
    break;

  case 29: // FOR_DECLARATION: TK_ID
#line 307 "sintatico.y"
                        {
				auto ini = lookup_symbol(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name);
				// ja foi declarado
				if(ini){
					// cria label se n existe (tava bugando)
					if(!ini->label.empty()){
						yystack_[0].value.as < std::shared_ptr<symbol> > ()->label = ini->label;
					} else {
						ini->label = gen_tmp_variable();
						variables.push_back({ini->label, "int"});
						yystack_[0].value.as < std::shared_ptr<symbol> > ()->label = ini->label;
					}

					if(ini->is_static == true && ini->type != "int"){
						report_error("variavel " + ini->name + " é estatica do tipo " + ini->type + "\n;");
						return 0;
					}

					ini->type  = "int"; // tem que atualizar o tipo na tabela (sempre int)
					yystack_[0].value.as < std::shared_ptr<symbol> > ()->type      = "int";
					yystack_[0].value.as < std::shared_ptr<symbol> > ()->is_static = ini->is_static;
				}
				else{
					yystack_[0].value.as < std::shared_ptr<symbol> > ()->label     = gen_tmp_variable();
					yystack_[0].value.as < std::shared_ptr<symbol> > ()->type      = "int";
					yystack_[0].value.as < std::shared_ptr<symbol> > ()->is_static = true;
					variables.push_back({yystack_[0].value.as < std::shared_ptr<symbol> > ()->label, "int"});
					register_symbol(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name, yystack_[0].value.as < std::shared_ptr<symbol> > ());
				}

				yylhs.value.as < node > ().label           = yystack_[0].value.as < std::shared_ptr<symbol> > ()->label;
				yylhs.value.as < node > ().type            = yystack_[0].value.as < std::shared_ptr<symbol> > ()->type;
				yylhs.value.as < node > ().is_static       = yystack_[0].value.as < std::shared_ptr<symbol> > ()->is_static;
				yylhs.value.as < node > ().is_materialized = true;
				yylhs.value.as < node > ().translation     = "";
			}
#line 1253 "y.tab.cc"
    break;

  case 30: // $@4: %empty
#line 345 "sintatico.y"
                                        {open_loop();}
#line 1259 "y.tab.cc"
    break;

  case 31: // LOOP: TK_WHILE '(' EXPR ')' $@4 BLOCK
#line 346 "sintatico.y"
                        {	
				materialize(yystack_[3].value.as < node > ());
				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;
				string label_continue = get_back_loop()->continue_label;

				yylhs.value.as < node > ().translation = label_start + ":\n";
				yylhs.value.as < node > ().translation += yystack_[3].value.as < node > ().translation;

				yylhs.value.as < node > ().translation += "\tif(!" + yystack_[3].value.as < node > ().label + ") goto " + label_end + ";\n";
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().translation; // bloco

				if(label_continue != "") yylhs.value.as < node > ().translation += label_continue + ":\n";
				yylhs.value.as < node > ().translation += "\tgoto " + label_start + ";\n";

				yylhs.value.as < node > ().translation += label_end + ":\n";
				context_stack.pop_back();
			}
#line 1282 "y.tab.cc"
    break;

  case 32: // $@5: %empty
#line 365 "sintatico.y"
                                {open_loop();}
#line 1288 "y.tab.cc"
    break;

  case 33: // LOOP: TK_DO $@5 BLOCK TK_WHILE '(' EXPR ')' ';'
#line 366 "sintatico.y"
                        {				
				materialize(yystack_[2].value.as < node > ());
				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;
				string label_continue = get_back_loop()->continue_label;
				string label_jump = gen_label_loop();

				// pula a primeria verificação
				yylhs.value.as < node > ().translation = "\tgoto " + label_jump + ";\n";

				yylhs.value.as < node > ().translation += label_start + ":\n";
				yylhs.value.as < node > ().translation += yystack_[2].value.as < node > ().translation;

				yylhs.value.as < node > ().translation += "\tif(!" + yystack_[2].value.as < node > ().label + ") goto " + label_end + ";\n";

				yylhs.value.as < node > ().translation += label_jump + ":\n";
				yylhs.value.as < node > ().translation += yystack_[5].value.as < node > ().translation; // bloco
				
				if(label_continue != "") yylhs.value.as < node > ().translation += label_continue + ":\n";
				yylhs.value.as < node > ().translation += "\tgoto " + label_start + ";\n";

				yylhs.value.as < node > ().translation += label_end + ":\n";

				context_stack.pop_back();
			}
#line 1318 "y.tab.cc"
    break;

  case 34: // $@6: %empty
#line 392 "sintatico.y"
                                                                                    {open_loop();}
#line 1324 "y.tab.cc"
    break;

  case 35: // LOOP: TK_FOR '(' OPT_ASSIGNMENT ';' EXPR ';' OPT_ASSIGNMENT ')' $@6 BLOCK
#line 393 "sintatico.y"
                        {
				materialize(yystack_[5].value.as < node > ());

				string label_start = get_back_loop()->start_label;
				string label_end = get_back_loop()->end_label;
				string label_continue = get_back_loop()->continue_label;

				// Primeiro assignment (declaração)
				yylhs.value.as < node > ().translation += yystack_[7].value.as < node > ().translation;

				yylhs.value.as < node > ().translation += label_start + ":\n";
				yylhs.value.as < node > ().translation += yystack_[5].value.as < node > ().translation;

				yylhs.value.as < node > ().translation += "\tif(!" + yystack_[5].value.as < node > ().label + ") goto " + label_end + ";\n";
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().translation; // bloco

				// segundo assignment (incremento)
				if(label_continue != "") yylhs.value.as < node > ().translation += label_continue + ":\n";
				yylhs.value.as < node > ().translation += yystack_[3].value.as < node > ().translation;

				yylhs.value.as < node > ().translation += "\tgoto " + label_start + ";\n";
				yylhs.value.as < node > ().translation += label_end + ":\n";

				context_stack.pop_back();
			}
#line 1354 "y.tab.cc"
    break;

  case 36: // $@7: %empty
#line 419 "sintatico.y"
                                                                                      {open_loop();}
#line 1360 "y.tab.cc"
    break;

  case 37: // LOOP: TK_FOR FOR_DECLARATION TK_IN TK_RANGE '(' EXPR ',' EXPR ')' $@7 BLOCK
#line 420 "sintatico.y"
                        {
				// nao materializa o $2, n sei pq mas da erro
				materialize(yystack_[5].value.as < node > ());
				materialize(yystack_[3].value.as < node > ());

				if(yystack_[5].value.as < node > ().type != "int" || yystack_[3].value.as < node > ().type != "int"){
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
				
				// cria a temporaria que recebe a verificação
				node cond = gen_expr(yystack_[9].value.as < node > () , op_lt, yystack_[3].value.as < node > ());
				yylhs.value.as < node > ().translation += cond.translation;	materialize(yystack_[3].value.as < node > ());

				if(yystack_[5].value.as < node > ().type != "int" || yystack_[3].value.as < node > ().type != "int"){
					report_error("Valor no intervalo in range() com tipo != int");
					return 0;
				}

				yylhs.value.as < node > ().translation += "\tif(!" + cond.label + ") goto " + label_end + ";\n";
				yylhs.value.as < node > ().translation += yystack_[0].value.as < node > ().translation;

				// brute force, da pra fazer melhor (basicamente a minha vida)
				if(label_continue != "") yylhs.value.as < node > ().translation += label_continue + ":\n";
				yylhs.value.as < node > ().translation += "\t" + yystack_[9].value.as < node > ().label + " = " + yystack_[9].value.as < node > ().label + " + 1;\n"; 

				yylhs.value.as < node > ().translation += "\tgoto " + label_start + ";\n";
				yylhs.value.as < node > ().translation += label_end + ":\n";

				context_stack.pop_back();
			}
#line 1407 "y.tab.cc"
    break;

  case 38: // LOOPCONTROL: TK_BREAK ';'
#line 466 "sintatico.y"
                        {
				if(context_stack.empty()){
					report_error("Break fora de loop");
					return 0;
				}

				yylhs.value.as < node > ().translation = "\tgoto " + context_stack.back().end_label + ";\n";
			}
#line 1420 "y.tab.cc"
    break;

  case 39: // LOOPCONTROL: TK_BREAK TK_INT ';'
#line 475 "sintatico.y"
                        {
				int n = stoi(yystack_[1].value.as < std::string > ());
				 
				if(n < 1){
					report_error("numero n invalido\n");
					return 0;
				}

				if(context_stack.size() < n){
					report_error("Break n é maior que a quantidade de loops\n");
					return 0;
				}
				
				auto& l = context_stack[context_stack.size() - n];
				
				yylhs.value.as < node > ().translation = "\tgoto " + l.end_label + ";\n";
				
			}
#line 1443 "y.tab.cc"
    break;

  case 40: // LOOPCONTROL: TK_CONTINUE ';'
#line 495 "sintatico.y"
                        {
				if(get_back_loop() == nullptr){
					report_error("Continue fora de loop");
				}
				get_back_loop()->continue_label = gen_label_loop();
				yylhs.value.as < node > ().translation = "\tgoto " + get_back_loop()->continue_label + ";\n";
			}
#line 1455 "y.tab.cc"
    break;

  case 41: // SWITCHBLOCK: CASE_LIST
#line 508 "sintatico.y"
                                {
					yylhs.value.as < node > ().jumps = yystack_[0].value.as < node > ().jumps;
					yylhs.value.as < node > ().labels_jumps = yystack_[0].value.as < node > ().labels_jumps;

				}
#line 1465 "y.tab.cc"
    break;

  case 42: // SWITCHBLOCK: CASE_LIST DEFAULT
#line 514 "sintatico.y"
                                {
					yylhs.value.as < node > ().jumps = yystack_[1].value.as < node > ().jumps + yystack_[0].value.as < node > ().jumps;
					yylhs.value.as < node > ().labels_jumps = yystack_[1].value.as < node > ().labels_jumps + yystack_[0].value.as < node > ().labels_jumps;

				}
#line 1475 "y.tab.cc"
    break;

  case 43: // CASE_LIST: CASE_LIST CASE_ITEM
#line 522 "sintatico.y"
                                {
					yylhs.value.as < node > ().jumps = yystack_[1].value.as < node > ().jumps + yystack_[0].value.as < node > ().jumps;
					yylhs.value.as < node > ().labels_jumps = yystack_[1].value.as < node > ().labels_jumps + yystack_[0].value.as < node > ().labels_jumps;
				}
#line 1484 "y.tab.cc"
    break;

  case 44: // CASE_LIST: CASE_ITEM
#line 528 "sintatico.y"
                                {
					yylhs.value.as < node > ().jumps = yystack_[0].value.as < node > ().jumps;
					yylhs.value.as < node > ().labels_jumps = yystack_[0].value.as < node > ().labels_jumps;
				}
#line 1493 "y.tab.cc"
    break;

  case 45: // CASE_ITEM: TK_CASE EXPR ':' BLOCK
#line 536 "sintatico.y"
                                {
					string L_case = gen_label_loop();
					string end_label = get_back_switch()->end_label; // Pega o label de saida da switch
					
					materialize(yystack_[2].value.as < node > ());

					op op_eq;
					op_eq.label = "==";
					node current_switch = get_back_switch()->switch_node; // Pega o switch atual da pilha
					node cmp_value = gen_expr(current_switch, op_eq, yystack_[2].value.as < node > ());
					
					// criando os ifs individuais
					yylhs.value.as < node > ().jumps = cmp_value.translation;
					yylhs.value.as < node > ().jumps += "\tif(" + cmp_value.label + ") goto " + L_case + ";\n";
					
					// bloco desse if
					yylhs.value.as < node > ().labels_jumps = L_case + ":\n" + yystack_[0].value.as < node > ().translation + "\tgoto " + end_label + ";\n";
					
					// O break deve vir aqui
				}
#line 1518 "y.tab.cc"
    break;

  case 46: // DEFAULT: TK_DEFAULT ':' BLOCK
#line 559 "sintatico.y"
                                {
					string L_default = gen_label_loop();
					string end_label =  get_back_switch()->end_label;

					yylhs.value.as < node > ().jumps = "\tgoto " + L_default + ";\n";
					
					yylhs.value.as < node > ().labels_jumps = L_default + ":\n" + yystack_[0].value.as < node > ().translation;
				}
#line 1531 "y.tab.cc"
    break;

  case 47: // IO: TK_PRINT '(' EXPR ')' ';'
#line 571 "sintatico.y"
                        {	
				materialize(yystack_[2].value.as < node > ());
				string type;
				
				if(yystack_[2].value.as < node > ().type == "string")	type = "\"%s\"";
				if(yystack_[2].value.as < node > ().type == "int")	type = "\"%d\"";
				if(yystack_[2].value.as < node > ().type == "float")	type = "\"%f\"";
				if(yystack_[2].value.as < node > ().type == "char")	type = "\"%c\"";
				if(yystack_[2].value.as < node > ().type == "bool")	type = "\"%i\"";
				  
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tprintf(" + type + ", " + yystack_[2].value.as < node > ().label + ");\n";
			}
#line 1549 "y.tab.cc"
    break;

  case 48: // IO: TK_PRINTL '(' EXPR ')' ';'
#line 585 "sintatico.y"
                        {	
				materialize(yystack_[2].value.as < node > ());
				string type;
				
				if(yystack_[2].value.as < node > ().type == "string")	type = "\"%s\\n\"";
				if(yystack_[2].value.as < node > ().type == "int")	type = "\"%d\\n\"";
				if(yystack_[2].value.as < node > ().type == "float")	type = "\"%f\\n\"";
				if(yystack_[2].value.as < node > ().type == "char")	type = "\"%c\\n\"";
				if(yystack_[2].value.as < node > ().type == "bool")	type = "\"%i\\n\"";
				  
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tprintf(" + type + ", " + yystack_[2].value.as < node > ().label + ");\n";
			}
#line 1567 "y.tab.cc"
    break;

  case 49: // IO: TK_INPUT '(' EXPR ')' ';'
#line 599 "sintatico.y"
                        {	
				string fmt;
				
				if(yystack_[2].value.as < node > ().type == "undefined"){
					promote_symbol(yystack_[2].value.as < node > (), "string");
					yystack_[2].value.as < node > ().type    = "string";
					yystack_[2].value.as < node > ().ir_type = "char*";
				}
				materialize(yystack_[2].value.as < node > ());
				
				if(yystack_[2].value.as < node > ().type == "string")	fmt = "\"%s\", "  + yystack_[2].value.as < node > ().label;
				if(yystack_[2].value.as < node > ().type == "int")	fmt = "\"%d\", &" + yystack_[2].value.as < node > ().label;
				if(yystack_[2].value.as < node > ().type == "float")	fmt = "\"%f\", &" +  yystack_[2].value.as < node > ().label;
				if(yystack_[2].value.as < node > ().type == "char")	fmt = "\"%c\", &" +  yystack_[2].value.as < node > ().label;
				if(yystack_[2].value.as < node > ().type == "bool")	fmt = "\"%i\", &" +  yystack_[2].value.as < node > ().label;
				
				
				yylhs.value.as < node > ().translation = yystack_[2].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\tscanf(" + fmt + ");\n";
			}
#line 1592 "y.tab.cc"
    break;

  case 50: // LVAL: TK_ID
#line 621 "sintatico.y"
                        {
				auto sym = lookup_symbol(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name);
				if(!sym){
					report_error("Variável '" + yystack_[0].value.as < std::shared_ptr<symbol> > ()->name + "' não declarada.");
				}
				yylhs.value.as < node > ().type  = sym->type;
				yylhs.value.as < node > ().label = sym->name;
				yylhs.value.as < node > ().is_static = sym->is_static;
				yylhs.value.as < node > ().translation = "";
			}
#line 1607 "y.tab.cc"
    break;

  case 51: // RVAL: EXPR
#line 633 "sintatico.y"
                       {yylhs.value.as < node > () = yystack_[0].value.as < node > ();}
#line 1613 "y.tab.cc"
    break;

  case 52: // EXPR: EXPR OP_ADD EXPR
#line 637 "sintatico.y"
                                     {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1619 "y.tab.cc"
    break;

  case 53: // EXPR: EXPR OP_MINUS EXPR
#line 638 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1625 "y.tab.cc"
    break;

  case 54: // EXPR: EXPR OP_MULT EXPR
#line 639 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1631 "y.tab.cc"
    break;

  case 55: // EXPR: EXPR OP_DIV EXPR
#line 640 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1637 "y.tab.cc"
    break;

  case 56: // EXPR: EXPR OP_MOD EXPR
#line 641 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1643 "y.tab.cc"
    break;

  case 57: // EXPR: EXPR OP_EQ EXPR
#line 644 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1649 "y.tab.cc"
    break;

  case 58: // EXPR: EXPR OP_NE EXPR
#line 645 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1655 "y.tab.cc"
    break;

  case 59: // EXPR: EXPR OP_LE EXPR
#line 646 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1661 "y.tab.cc"
    break;

  case 60: // EXPR: EXPR OP_GE EXPR
#line 647 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1667 "y.tab.cc"
    break;

  case 61: // EXPR: EXPR OP_LT EXPR
#line 648 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1673 "y.tab.cc"
    break;

  case 62: // EXPR: EXPR OP_GT EXPR
#line 649 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1679 "y.tab.cc"
    break;

  case 63: // EXPR: EXPR OP_OR EXPR
#line 652 "sintatico.y"
                                           {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1685 "y.tab.cc"
    break;

  case 64: // EXPR: EXPR OP_AND EXPR
#line 653 "sintatico.y"
                                           {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1691 "y.tab.cc"
    break;

  case 65: // EXPR: OP_NOT EXPR
#line 654 "sintatico.y"
                                       {yylhs.value.as < node > () = gen_unary("left",yystack_[1].value.as < op > (),yystack_[0].value.as < node > ());}
#line 1697 "y.tab.cc"
    break;

  case 66: // EXPR: TK_CAST EXPR
#line 655 "sintatico.y"
                                       {yylhs.value.as < node > () = casting(yystack_[0].value.as < node > (),yystack_[1].value.as < std::string > ());}
#line 1703 "y.tab.cc"
    break;

  case 67: // EXPR: '(' EXPR ')'
#line 657 "sintatico.y"
                                       {yylhs.value.as < node > () = yystack_[1].value.as < node > ();}
#line 1709 "y.tab.cc"
    break;

  case 68: // EXPR: TK_INT
#line 659 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"int",yystack_[0].value.as < std::string > ());}
#line 1715 "y.tab.cc"
    break;

  case 69: // EXPR: TK_FLOAT
#line 660 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"float",yystack_[0].value.as < std::string > ());}
#line 1721 "y.tab.cc"
    break;

  case 70: // EXPR: TK_CHAR
#line 661 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"char",yystack_[0].value.as < std::string > ());}
#line 1727 "y.tab.cc"
    break;

  case 71: // EXPR: TK_BOOL
#line 662 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"bool", yystack_[0].value.as < std::string > ());}
#line 1733 "y.tab.cc"
    break;

  case 72: // EXPR: TK_STRING
#line 664 "sintatico.y"
                        {
					gen_literal(yylhs.value.as < node > (), "string", yystack_[0].value.as < std::string > ());
			}
#line 1741 "y.tab.cc"
    break;

  case 73: // EXPR: TK_ID
#line 668 "sintatico.y"
                        {
				auto sym = lookup_symbol(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name);
				if (!sym){
					report_error("Variável '" + yystack_[0].value.as < std::shared_ptr<symbol> > ()->name + "' não declarada.");
				}
				yylhs.value.as < node > ().label = sym->name;
				yylhs.value.as < node > ().type  = sym->type;
				yylhs.value.as < node > ().is_static = sym->is_static;
				yylhs.value.as < node > ().translation = "";
			}
#line 1756 "y.tab.cc"
    break;


#line 1760 "y.tab.cc"

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


  const signed char parser::yypact_ninf_ = -46;

  const signed char parser::yytable_ninf_ = -22;

  const short
  parser::yypact_[] =
  {
     138,    15,    -6,   -28,     3,   -46,     0,   -16,     8,    10,
      16,    18,    40,   -46,    87,   138,   -46,   -46,    45,   -46,
     -46,   -46,   -46,   -46,   -10,   -22,   138,    79,     4,     4,
      81,    46,   -46,   -46,    -4,    80,   -46,     4,     4,     4,
       4,   -46,   -46,   -46,    71,    72,     4,     4,   -46,    93,
      42,   -46,   -46,   -46,   -46,   -46,   -46,     4,   -46,     4,
       4,   139,   158,    98,   -46,    86,   -46,    73,    96,   177,
     196,   215,   234,   -46,   -46,   -46,   343,   -46,    41,   -46,
     -46,   -46,   253,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,    81,   -46,    74,   -14,
       4,    75,   -46,    82,    85,   102,     4,   -46,   -46,     9,
       9,    89,    89,   -46,    65,    65,    65,    65,    65,    65,
      78,     5,   109,    81,     4,   110,   327,     4,   103,   -46,
     -46,   -46,   -46,    81,   -46,   272,   107,    -4,   104,   135,
     -46,   114,    77,     4,     4,   -46,    -9,   -46,   -46,   -46,
     291,   310,   115,   -46,   -46,    81,   -46,    81,    81,   -46,
      81,   -46,   -46,   -46
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,    19,     0,     0,    32,     0,     0,     0,     0,
       0,     0,     0,    50,     0,     2,     4,     5,     0,     7,
       8,     9,    10,    11,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    29,    28,     0,    40,     0,     0,     0,
       0,     1,     3,     6,     0,     0,     0,     0,    12,     0,
       0,    22,    68,    69,    70,    72,    71,     0,    73,     0,
       0,     0,     0,     0,    39,     0,    27,     0,     0,     0,
       0,     0,     0,    17,    18,    14,    51,    15,     0,    20,
      66,    65,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,     0,     0,
       0,     0,    25,     0,     0,     0,     0,    13,    67,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    24,     0,     0,     0,     0,     0,     0,    47,
      48,    49,    16,     0,    31,     0,     0,    28,     0,     0,
      23,     0,     0,     0,     0,    26,    41,    44,    33,    34,
       0,     0,     0,    43,    42,     0,    36,     0,     0,    35,
       0,    45,    46,    37
  };

  const short
  parser::yypgoto_[] =
  {
     -46,   -46,   136,   -11,   -46,   -33,   -30,   -46,   -46,   -46,
     -46,    30,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,
     -46,    35,   -46,   -46,   -46,   -45,   -12
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    26,    27,    20,
     128,    67,    35,    21,   123,    30,   155,   160,    22,   145,
     146,   147,   154,    23,    24,    75,    76
  };

  const short
  parser::yytable_[] =
  {
      63,    66,    77,    31,    42,    65,   -21,    52,    53,    54,
      55,    56,    33,   144,    57,   152,    61,    62,    28,    44,
      45,    47,    48,    49,    13,    69,    70,    71,    72,    47,
      34,   125,    58,    46,    83,    84,    85,    86,    87,    42,
      85,    86,    87,    25,    32,    80,    59,    81,    82,    29,
      60,     1,    36,     2,    79,     3,    37,     4,     5,     6,
       7,   132,    38,     8,    39,     9,   122,    10,    11,    12,
      13,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   106,   107,    40,    41,   126,    43,
      64,    51,     2,   134,    83,    84,    85,    86,    87,    68,
      73,    78,    74,   140,    66,    94,    95,    83,    84,    85,
      86,    87,   135,    98,    99,   138,   101,   100,   136,    95,
     124,   127,    87,   133,   149,   159,   129,   161,   162,   130,
     163,   150,   151,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,   131,     1,   139,     2,
     106,     3,   143,     4,     5,     6,     7,   144,   148,     8,
     158,     9,    50,    10,    11,    12,    13,   142,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,   153,     0,     0,     0,     0,    96,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
       0,     0,     0,     0,     0,    97,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,     0,
       0,     0,     0,     0,   102,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,     0,     0,
       0,     0,     0,   103,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,     0,     0,     0,
       0,     0,   104,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,     0,     0,     0,     0,
       0,   105,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,     0,     0,     0,     0,     0,
     108,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,     0,     0,     0,     0,     0,   141,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,     0,     0,     0,     0,     0,   156,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,     0,     0,     0,   157,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,     0,
       0,   137,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95
  };

  const short
  parser::yycheck_[] =
  {
      30,    34,    47,     3,    15,     9,    12,     3,     4,     5,
       6,     7,    28,    22,    10,    24,    28,    29,    46,    29,
      30,    43,    44,    45,    28,    37,    38,    39,    40,    43,
      46,    45,    28,    43,    29,    30,    31,    32,    33,    50,
      31,    32,    33,    28,    44,    57,    42,    59,    60,    46,
      46,     9,    44,    11,    12,    13,    46,    15,    16,    17,
      18,   106,    46,    21,    46,    23,    96,    25,    26,    27,
      28,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    43,    44,    46,     0,   100,    44,
      44,    12,    11,   123,    29,    30,    31,    32,    33,    19,
      29,     8,    30,   133,   137,    40,    41,    29,    30,    31,
      32,    33,   124,    15,    28,   127,    20,    44,     8,    41,
      46,    46,    33,    14,    47,   155,    44,   157,   158,    44,
     160,   143,   144,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    44,     9,    45,    11,
      43,    13,    48,    15,    16,    17,    18,    22,    44,    21,
      45,    23,    26,    25,    26,    27,    28,   137,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,   146,    -1,    -1,    -1,    -1,    47,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    -1,    -1,    47,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    47,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    47,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    47,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    47,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      47,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    47,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    47,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    45,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    44,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41
  };

  const signed char
  parser::yystos_[] =
  {
       0,     9,    11,    13,    15,    16,    17,    18,    21,    23,
      25,    26,    27,    28,    50,    51,    52,    53,    54,    55,
      58,    62,    67,    72,    73,    28,    56,    57,    46,    46,
      64,     3,    44,    28,    46,    61,    44,    46,    46,    46,
      46,     0,    52,    44,    29,    30,    43,    43,    44,    45,
      51,    12,     3,     4,     5,     6,     7,    10,    28,    42,
      46,    75,    75,    55,    44,     9,    54,    60,    19,    75,
      75,    75,    75,    29,    30,    74,    75,    74,     8,    12,
      75,    75,    75,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    47,    47,    15,    28,
      44,    20,    47,    47,    47,    47,    43,    44,    47,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    55,    63,    46,    45,    75,    46,    59,    44,
      44,    44,    74,    14,    55,    75,     8,    44,    75,    45,
      55,    47,    60,    48,    22,    68,    69,    70,    44,    47,
      75,    75,    24,    70,    71,    65,    47,    45,    45,    55,
      66,    55,    55,    55
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    49,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    53,    53,    54,    54,    54,    54,    54,    56,
      55,    57,    55,    58,    58,    59,    58,    60,    60,    61,
      63,    62,    64,    62,    65,    62,    66,    62,    67,    67,
      67,    68,    68,    69,    69,    70,    71,    72,    72,    72,
      73,    74,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     3,     5,     3,     4,     6,     3,     3,     0,
       4,     0,     3,     7,     5,     0,     7,     1,     0,     1,
       0,     6,     0,     8,     0,    10,     0,    11,     2,     3,
       2,     1,     2,     2,     1,     4,     3,     5,     5,     5,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     3,     1,     1,
       1,     1,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TK_INT", "TK_FLOAT",
  "TK_CHAR", "TK_STRING", "TK_BOOL", "TK_TYPE", "TK_VAR", "TK_CAST",
  "TK_SBLOCK", "TK_EBLOCK", "TK_IF", "TK_ELSE", "TK_WHILE", "TK_DO",
  "TK_BREAK", "TK_FOR", "TK_IN", "TK_RANGE", "TK_CONTINUE", "TK_CASE",
  "TK_SWITCH", "TK_DEFAULT", "TK_PRINT", "TK_PRINTL", "TK_INPUT", "TK_ID",
  "OP_ADD", "OP_MINUS", "OP_MULT", "OP_DIV", "OP_MOD", "OP_EQ", "OP_NE",
  "OP_LE", "OP_GE", "OP_LT", "OP_GT", "OP_OR", "OP_AND", "OP_NOT", "OP_AT",
  "';'", "':'", "'('", "')'", "','", "$accept", "S", "COMMANDS",
  "STATEMENT", "DECLARATION", "ASSIGNMENT", "BLOCK", "$@1", "$@2",
  "CONDITIONAL", "$@3", "OPT_ASSIGNMENT", "FOR_DECLARATION", "LOOP", "$@4",
  "$@5", "$@6", "$@7", "LOOPCONTROL", "SWITCHBLOCK", "CASE_LIST",
  "CASE_ITEM", "DEFAULT", "IO", "LVAL", "RVAL", "EXPR", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   112,   112,   125,   126,   129,   130,   131,   132,   133,
     134,   135,   137,   147,   155,   183,   199,   223,   228,   235,
     235,   243,   243,   252,   272,   285,   284,   302,   303,   306,
     345,   345,   365,   365,   392,   392,   419,   419,   465,   474,
     494,   507,   513,   521,   527,   535,   558,   570,   584,   598,
     620,   633,   637,   638,   639,   640,   641,   644,   645,   646,
     647,   648,   649,   652,   653,   654,   655,   657,   659,   660,
     661,   662,   663,   667
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
#line 2374 "y.tab.cc"

#line 678 "sintatico.y"


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
