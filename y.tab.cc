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
	shared_ptr<symbol> lookup_symbol(const string& name);
	const string lookup_variables(const string& label);
	void promote_symbol(node& n, const string& type);
	
	/*** Funções auxiliares: conversão ***/
	bool is_numeric(const string& s);
	const string get_type(node& n);

	void check_conversion(const string& l, const string& r);
	node conversion(node& t, const string& type);
	/*void coercion(node& l, node& r, const string& op);*/
	void coercion(node& l, node& r);
	node casting(node& t, const string& type);

	/*** Funções auxiliares: inferência ***/
	void inference(node& l, node& r);

	/*** Funções auxiliares: debug ***/
	void report_error(const string& msg);
	/*TODO: Lançar exceção para main capturar */

#line 96 "y.tab.cc"


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
#line 169 "y.tab.cc"

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
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
      case symbol_kind::S_EXPR: // EXPR
        value.YY_MOVE_OR_COPY< node > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.YY_MOVE_OR_COPY< std::shared_ptr<symbol> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_BOOL: // TK_BOOL
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_VAR: // TK_VAR
      case symbol_kind::S_TK_CAST: // TK_CAST
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
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
      case symbol_kind::S_EXPR: // EXPR
        value.move< node > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.move< std::shared_ptr<symbol> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_BOOL: // TK_BOOL
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_VAR: // TK_VAR
      case symbol_kind::S_TK_CAST: // TK_CAST
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
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
      case symbol_kind::S_EXPR: // EXPR
        value.copy< node > (that.value);
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.copy< std::shared_ptr<symbol> > (that.value);
        break;

      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_BOOL: // TK_BOOL
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_VAR: // TK_VAR
      case symbol_kind::S_TK_CAST: // TK_CAST
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
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
      case symbol_kind::S_EXPR: // EXPR
        value.move< node > (that.value);
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.move< std::shared_ptr<symbol> > (that.value);
        break;

      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_BOOL: // TK_BOOL
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_VAR: // TK_VAR
      case symbol_kind::S_TK_CAST: // TK_CAST
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
      case symbol_kind::S_LVAL: // LVAL
      case symbol_kind::S_RVAL: // RVAL
      case symbol_kind::S_EXPR: // EXPR
        yylhs.value.emplace< node > ();
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        yylhs.value.emplace< std::shared_ptr<symbol> > ();
        break;

      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_BOOL: // TK_BOOL
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_VAR: // TK_VAR
      case symbol_kind::S_TK_CAST: // TK_CAST
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
#line 85 "sintatico.y"
                        {
				code = "/*Compilador FOCA*/\n#include <stdio.h>\nint main(void) {\n";
				code += gen_declarations();
				code += "\n" + yystack_[0].value.as < node > ().translation;
				code += "\treturn 0;\n}\n";
			}
#line 675 "y.tab.cc"
    break;

  case 3: // COMMANDS: COMMANDS STATEMENT
#line 93 "sintatico.y"
                                     {yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation + yystack_[0].value.as < node > ().translation;}
#line 681 "y.tab.cc"
    break;

  case 4: // COMMANDS: STATEMENT
#line 94 "sintatico.y"
                                                 {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 687 "y.tab.cc"
    break;

  case 5: // STATEMENT: DECLARATION
#line 96 "sintatico.y"
                              {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 693 "y.tab.cc"
    break;

  case 6: // STATEMENT: ASSIGNMENT
#line 97 "sintatico.y"
                                      {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 699 "y.tab.cc"
    break;

  case 7: // DECLARATION: TK_VAR TK_ID ';'
#line 101 "sintatico.y"
                        {
				auto sym = lookup_symbol(yystack_[1].value.as < std::shared_ptr<symbol> > ()->name);
				if(sym){
						string msg = "Variável '" + sym->name + "' já declarada.";
						report_error(msg);
					}
				yystack_[1].value.as < std::shared_ptr<symbol> > ()->type = "wildcard";
				yylhs.value.as < node > ().translation = "";

				auto [it, inserted] = symbols.try_emplace(yystack_[1].value.as < std::shared_ptr<symbol> > ()->name, yystack_[1].value.as < std::shared_ptr<symbol> > ());
			}
#line 715 "y.tab.cc"
    break;

  case 8: // DECLARATION: TK_VAR TK_ID ':' TK_TYPE ';'
#line 113 "sintatico.y"
                        {
				auto sym = lookup_symbol(yystack_[3].value.as < std::shared_ptr<symbol> > ()->name);
				if(sym){
						string msg = "Variável '" + yystack_[3].value.as < std::shared_ptr<symbol> > ()->name + "' já declarada.";
						report_error(msg);
					}
				//sym->is_dynamic = false;
				yystack_[3].value.as < std::shared_ptr<symbol> > ()->type = yystack_[1].value.as < std::string > ();
				yylhs.value.as < node > ().translation = "";

				auto [it, inserted] = symbols.try_emplace(yystack_[3].value.as < std::shared_ptr<symbol> > ()->name, yystack_[3].value.as < std::shared_ptr<symbol> > ());
			}
#line 732 "y.tab.cc"
    break;

  case 9: // ASSIGNMENT: LVAL OP_AT RVAL ';'
#line 127 "sintatico.y"
                        {
				materialize(yystack_[1].value.as < node > ());

				if(get_type(yystack_[1].value.as < node > ()) != "undefined"){
					promote_symbol(yystack_[3].value.as < node > (),yystack_[1].value.as < node > ().type);
				} 
				else coercion(yystack_[3].value.as < node > (),yystack_[1].value.as < node > ()); 

				materialize(yystack_[3].value.as < node > ());
				yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation + yystack_[3].value.as < node > ().translation;
				yylhs.value.as < node > ().translation += "\t" + yystack_[3].value.as < node > ().label + " = " + yystack_[1].value.as < node > ().label + ";\n";
			}
#line 749 "y.tab.cc"
    break;

  case 10: // LVAL: TK_ID
#line 141 "sintatico.y"
                        {
				auto sym = lookup_symbol(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name);
				if(!sym){
					string msg = "Identificador '" + yystack_[0].value.as < std::shared_ptr<symbol> > ()->name + "' não declarado.";
					report_error(msg);
				}
				yylhs.value.as < node > ().type  = sym->type;
				yylhs.value.as < node > ().label = sym->name;
				yylhs.value.as < node > ().translation = "";
			}
#line 764 "y.tab.cc"
    break;

  case 11: // RVAL: EXPR
#line 153 "sintatico.y"
                       {yylhs.value.as < node > () = yystack_[0].value.as < node > ();}
#line 770 "y.tab.cc"
    break;

  case 12: // EXPR: EXPR OP_ADD EXPR
#line 157 "sintatico.y"
                                     {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"+",yystack_[0].value.as < node > ());}
#line 776 "y.tab.cc"
    break;

  case 13: // EXPR: EXPR OP_MINUS EXPR
#line 158 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"-",yystack_[0].value.as < node > ());}
#line 782 "y.tab.cc"
    break;

  case 14: // EXPR: EXPR OP_MULT EXPR
#line 159 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"*",yystack_[0].value.as < node > ());}
#line 788 "y.tab.cc"
    break;

  case 15: // EXPR: EXPR OP_DIV EXPR
#line 160 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"/",yystack_[0].value.as < node > ());}
#line 794 "y.tab.cc"
    break;

  case 16: // EXPR: EXPR OP_MOD EXPR
#line 161 "sintatico.y"
                                             {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"%",yystack_[0].value.as < node > ());}
#line 800 "y.tab.cc"
    break;

  case 17: // EXPR: EXPR OP_EQ EXPR
#line 164 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"==",yystack_[0].value.as < node > ());}
#line 806 "y.tab.cc"
    break;

  case 18: // EXPR: EXPR OP_NE EXPR
#line 165 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"!=",yystack_[0].value.as < node > ());}
#line 812 "y.tab.cc"
    break;

  case 19: // EXPR: EXPR OP_LE EXPR
#line 166 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"<=",yystack_[0].value.as < node > ());}
#line 818 "y.tab.cc"
    break;

  case 20: // EXPR: EXPR OP_GE EXPR
#line 167 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),">=",yystack_[0].value.as < node > ());}
#line 824 "y.tab.cc"
    break;

  case 21: // EXPR: EXPR OP_LT EXPR
#line 168 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"<",yystack_[0].value.as < node > ());}
#line 830 "y.tab.cc"
    break;

  case 22: // EXPR: EXPR OP_GT EXPR
#line 169 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),">",yystack_[0].value.as < node > ());}
#line 836 "y.tab.cc"
    break;

  case 23: // EXPR: EXPR OP_OR EXPR
#line 172 "sintatico.y"
                                           {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"||",yystack_[0].value.as < node > ());}
#line 842 "y.tab.cc"
    break;

  case 24: // EXPR: EXPR OP_AND EXPR
#line 173 "sintatico.y"
                                           {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"&&",yystack_[0].value.as < node > ());}
#line 848 "y.tab.cc"
    break;

  case 25: // EXPR: OP_NOT EXPR
#line 174 "sintatico.y"
                                       {yylhs.value.as < node > () = gen_unary("left","!",yystack_[0].value.as < node > ());}
#line 854 "y.tab.cc"
    break;

  case 26: // EXPR: TK_CAST EXPR
#line 175 "sintatico.y"
                                       {yylhs.value.as < node > () = casting(yystack_[0].value.as < node > (),yystack_[1].value.as < std::string > ());}
#line 860 "y.tab.cc"
    break;

  case 27: // EXPR: '(' EXPR ')'
#line 177 "sintatico.y"
                                       {yylhs.value.as < node > () = yystack_[1].value.as < node > ();}
#line 866 "y.tab.cc"
    break;

  case 28: // EXPR: TK_INT
#line 179 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"int",yystack_[0].value.as < std::string > ());}
#line 872 "y.tab.cc"
    break;

  case 29: // EXPR: TK_FLOAT
#line 180 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"float",yystack_[0].value.as < std::string > ());}
#line 878 "y.tab.cc"
    break;

  case 30: // EXPR: TK_CHAR
#line 181 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"char",yystack_[0].value.as < std::string > ());}
#line 884 "y.tab.cc"
    break;

  case 31: // EXPR: TK_BOOL
#line 182 "sintatico.y"
                                        {gen_literal(yylhs.value.as < node > (),"int", yystack_[0].value.as < std::string > ());}
#line 890 "y.tab.cc"
    break;

  case 32: // EXPR: TK_ID
#line 184 "sintatico.y"
                        {
				auto sym = lookup_symbol(yystack_[0].value.as < std::shared_ptr<symbol> > ()->name);
				if (!sym){
					string msg = "Identificador '" + yystack_[0].value.as < std::shared_ptr<symbol> > ()->name + "' não declarado.";
					report_error(msg);
				}
				yylhs.value.as < node > ().label = sym->name;
				yylhs.value.as < node > ().type  = sym->type;
				yylhs.value.as < node > ().translation = "";
			}
#line 905 "y.tab.cc"
    break;


#line 909 "y.tab.cc"

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


  const signed char parser::yypact_ninf_ = -23;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      11,     6,   -23,    20,    11,   -23,   -23,   -23,    12,   -22,
     -23,   -23,    -3,   -23,    17,   -23,   -23,   -23,   -23,    -3,
     -23,    -3,    -3,    29,    45,    55,   -23,   -23,    27,   -23,
      -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,    -3,
      -3,    -3,    -3,   -23,   -23,   -10,   -10,   -10,   -10,   -10,
     -10,    51,    56,    30,    30,    58,    58,   -23
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,    10,     0,     2,     4,     5,     6,     0,     0,
       1,     3,     0,     7,     0,    28,    29,    30,    31,     0,
      32,     0,     0,     0,    11,     0,    26,    25,     0,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,    27,    17,    18,    19,    20,    21,
      22,    23,    24,    12,    13,    14,    15,    16
  };

  const signed char
  parser::yypgoto_[] =
  {
     -23,   -23,   -23,    79,   -23,   -23,   -23,   -23,    -4
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     3,     4,     5,     6,     7,     8,    23,    24
  };

  const signed char
  parser::yytable_[] =
  {
      15,    16,    17,    18,    13,    14,    19,    20,    36,    37,
      38,    39,    40,    41,    42,    26,     9,    27,    28,     1,
      10,     2,    21,    12,    25,    22,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    40,    41,    42,    29,    44,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      37,    38,    39,    40,    41,    42,    38,    39,    40,    41,
      42,    43,    42,    11
  };

  const signed char
  parser::yycheck_[] =
  {
       3,     4,     5,     6,    26,    27,     9,    10,    18,    19,
      20,    21,    22,    23,    24,    19,    10,    21,    22,     8,
       0,    10,    25,    11,     7,    28,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    22,    23,    24,    26,    29,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      19,    20,    21,    22,    23,    24,    20,    21,    22,    23,
      24,    26,    24,     4
  };

  const signed char
  parser::yystos_[] =
  {
       0,     8,    10,    31,    32,    33,    34,    35,    36,    10,
       0,    33,    11,    26,    27,     3,     4,     5,     6,     9,
      10,    25,    28,    37,    38,     7,    38,    38,    38,    26,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    26,    29,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    30,    31,    32,    32,    33,    33,    34,    34,    35,
      36,    37,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    38
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     1,     1,     3,     5,     4,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     3,     1,     1,
       1,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TK_INT", "TK_FLOAT",
  "TK_CHAR", "TK_BOOL", "TK_TYPE", "TK_VAR", "TK_CAST", "TK_ID", "OP_AT",
  "OP_EQ", "OP_NE", "OP_LE", "OP_GE", "OP_LT", "OP_GT", "OP_OR", "OP_AND",
  "OP_ADD", "OP_MINUS", "OP_MULT", "OP_DIV", "OP_MOD", "OP_NOT", "';'",
  "':'", "'('", "')'", "$accept", "S", "COMMANDS", "STATEMENT",
  "DECLARATION", "ASSIGNMENT", "LVAL", "RVAL", "EXPR", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,    84,    84,    93,    94,    96,    97,   100,   112,   126,
     140,   153,   157,   158,   159,   160,   161,   164,   165,   166,
     167,   168,   169,   172,   173,   174,   175,   177,   179,   180,
     181,   182,   183
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
#line 1408 "y.tab.cc"

#line 194 "sintatico.y"


void gen_literal(node& n, const string& type, const string& literal){
	n.label = literal;
	n.type = type;
	n.translation = "";
}

void materialize(node& n){
    if(!n.is_materialized){
		/* Verifica se é um identificador pela tabela de símbolos */
		auto sym = lookup_symbol(n.label);
		if(sym){
			/* Reutiliza um temporário previamente registrado  */
			if(!sym->label.empty()) n.label = sym->label;
		
			/* Gera um temporário novo para um identificador */
			else{
				string label = gen_tmp_variable();
				sym->label = label;

				variables[label] = n.type;
				n.label = label;
			}
		}
		/* Verifica se é um literal pela ausência de tradução */
		else if(n.translation.empty()){
			string label = gen_tmp_variable();
			n.translation += "\t" + label + " = " + n.label + ";\n";

			n.label = label;
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
node gen_expr(node& l, const string& op, node& r)
{
    materialize(l);
    materialize(r);

    coercion(l,r); 

    node n;
    n.type = get_type(l);
    materialize(n);

    n.translation = l.translation + r.translation;
    n.translation += "\t" + n.label + " = " + l.label + " " + op + " " + r.label + ";\n";
    return n;
}

/* Gerador de expressões unárias */
node gen_unary(const string& side, const string& op, node& t){
	
	/* Criação de temporário para o nó */
	materialize(t);

	string tt = get_type(t);

	/* TODO: Regras de conversão por tipo de operação */
	check_conversion(tt, t.type);
	conversion(t, tt);

    node n;
	n.type = get_type(t);
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

	/*TODO: Aceitar outros tipos de conversão */
	if(!is_numeric(l) || !is_numeric(r)){
		report_error("Conversão não permitida entre tipos ("+ l +") e ("+ r +")");
	}
	if(l == "undefined" || r == "undefined"){
        report_error("Uso de variável não inicializada na expressão.");
	}
}

/* Função de conversão explícita */
node casting(node& t, const string& type) {
    
	materialize(t);
    string tt = get_type(t);
    
    if (tt == type) return t; 
    check_conversion(tt, type);

    return conversion(t, type);
}

/* Função auxiliar para conversão */
node conversion(node& t, const string& type) {
   
    node n;
    n.type = type;
    materialize(n);

    n.translation = t.translation;
    n.translation += "\t" + n.label + " = (" + type + ") " + t.label + ";\n";
    
    return n;
}

/* Função de conversão implícita */
void coercion(node& l, node& r) {
    string lt = get_type(l);
    string rt = get_type(r);

    check_conversion(lt, rt);

    if (lt == "float" && rt == "int"){
        r = conversion(r, "float");
    } 
    else if (lt == "int" && rt == "float"){
        l = conversion(l, "float");
    }
}

const string get_type(node& n){
    if(n.type != "wildcard") return n.type;
    
    auto sym = lookup_symbol(n.label);
    if(sym && !sym->label.empty()){
        return variables[sym->label];
    }

	auto var = lookup_variables(n.label);
	if(!var.empty()){
		return var;
	}
    return "undefined";
}

/*** INFERÊNCIA DE TIPAGEM ***/

/* Modificação do tipo e atualização do mapa de variáveis */
void promote_symbol(node& n, const string& type){
	/* Verifica se é um identificador pela tabela de símbolos */
	auto sym = lookup_symbol(n.label);

	/* Promove o tipo do indetificador */
	if(sym && sym->type == "wildcard"){
		string label = gen_tmp_variable();
		sym->label = label;

		variables[label] = type;
		n.label = label;
		n.type = type;
		n.is_materialized = true;
	}
}

shared_ptr<symbol> lookup_symbol(const string& name){
	auto it = symbols.find(name);
	
	if (it != symbols.end()) return it->second; 
	else return nullptr;
}

const string lookup_variables(const string& label){
	auto it = variables.find(label);
	
	if (it != variables.end()) return it->second; 
	else return {};
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
