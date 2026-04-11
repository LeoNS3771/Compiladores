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



// First part of user prologue.
#line 19 "sintatico.y"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "tokens.hh"

using namespace std;

/*** Variáveis globais  ***/
int tmp_var_count;
string code;
vector<symbol> symbols;	//Tabela de símbolos
vector<pair<string, string>> variables;	//Variáveis temporárias

/*** Variáveis externas ***/
extern int yylineno;

/*** Geradores de código  ***/
string gen_tmp_variable();
string gen_declarations(); 

/*** Funções auxiliares ***/
symbol* search_symbol(string label);
node gen_expr(const node& l, string op, const node& r);


#line 69 "y.tab.cc"


#include "y.tab.hh"


// Unqualified %code blocks.
#line 14 "sintatico.y"

    #include "y.tab.hh"
	yy::parser::symbol_type yylex();

#line 81 "y.tab.cc"


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
#line 154 "y.tab.cc"

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
      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_BOOL: // TK_BOOL
        value.YY_MOVE_OR_COPY< literal > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_DECL: // DECL
      case symbol_kind::S_ATRI: // ATRI
      case symbol_kind::S_EXPR: // EXPR
        value.YY_MOVE_OR_COPY< node > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.YY_MOVE_OR_COPY< symbol > (YY_MOVE (that.value));
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
      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_BOOL: // TK_BOOL
        value.move< literal > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_DECL: // DECL
      case symbol_kind::S_ATRI: // ATRI
      case symbol_kind::S_EXPR: // EXPR
        value.move< node > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.move< symbol > (YY_MOVE (that.value));
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
      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_BOOL: // TK_BOOL
        value.copy< literal > (that.value);
        break;

      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_DECL: // DECL
      case symbol_kind::S_ATRI: // ATRI
      case symbol_kind::S_EXPR: // EXPR
        value.copy< node > (that.value);
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.copy< symbol > (that.value);
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
      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_BOOL: // TK_BOOL
        value.move< literal > (that.value);
        break;

      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_DECL: // DECL
      case symbol_kind::S_ATRI: // ATRI
      case symbol_kind::S_EXPR: // EXPR
        value.move< node > (that.value);
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.move< symbol > (that.value);
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
      case symbol_kind::S_TK_INT: // TK_INT
      case symbol_kind::S_TK_FLOAT: // TK_FLOAT
      case symbol_kind::S_TK_TYPE: // TK_TYPE
      case symbol_kind::S_TK_CHAR: // TK_CHAR
      case symbol_kind::S_TK_BOOL: // TK_BOOL
        yylhs.value.emplace< literal > ();
        break;

      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_DECL: // DECL
      case symbol_kind::S_ATRI: // ATRI
      case symbol_kind::S_EXPR: // EXPR
        yylhs.value.emplace< node > ();
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        yylhs.value.emplace< symbol > ();
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
#line 68 "sintatico.y"
                        {
				code = "/*Compilador FOCA*/\n#include <stdio.h>\nint main(void) {\n";
				code += gen_declarations();
				code += "\n" + yystack_[0].value.as < node > ().translation;
				code += "\treturn 0;\n}\n";
			}
#line 640 "y.tab.cc"
    break;

  case 3: // COMMANDS: COMMANDS STATEMENT
#line 76 "sintatico.y"
                                     {yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation + yystack_[0].value.as < node > ().translation;}
#line 646 "y.tab.cc"
    break;

  case 4: // COMMANDS: STATEMENT
#line 77 "sintatico.y"
                                                 {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 652 "y.tab.cc"
    break;

  case 5: // STATEMENT: DECL
#line 79 "sintatico.y"
                       {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 658 "y.tab.cc"
    break;

  case 6: // STATEMENT: ATRI
#line 80 "sintatico.y"
                               {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 664 "y.tab.cc"
    break;

  case 7: // STATEMENT: EXPR
#line 81 "sintatico.y"
                               {yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation;}
#line 670 "y.tab.cc"
    break;

  case 8: // DECL: TK_TYPE TK_ID ';'
#line 84 "sintatico.y"
                        {
				symbol sym;
				sym.name = yystack_[1].value.as < symbol > ().label;
				sym.type = yystack_[2].value.as < literal > ().label;
				symbols.push_back(sym);  
				yylhs.value.as < node > ().translation = "";
			}
#line 682 "y.tab.cc"
    break;

  case 9: // ATRI: TK_ID OP_AT EXPR ';'
#line 93 "sintatico.y"
                        {
				symbol* sym = search_symbol(yystack_[3].value.as < symbol > ().label);
				if(sym){
					yylhs.value.as < node > ().label = sym->label;
					yylhs.value.as < node > ().translation = yystack_[1].value.as < node > ().translation + "\t" + yylhs.value.as < node > ().label + " = " + yystack_[1].value.as < node > ().label + ";\n";
				}
			}
#line 694 "y.tab.cc"
    break;

  case 10: // EXPR: EXPR '+' EXPR
#line 102 "sintatico.y"
                                {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"+",yystack_[0].value.as < node > ());}
#line 700 "y.tab.cc"
    break;

  case 11: // EXPR: EXPR '-' EXPR
#line 103 "sintatico.y"
                                        {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"-",yystack_[0].value.as < node > ());}
#line 706 "y.tab.cc"
    break;

  case 12: // EXPR: EXPR '*' EXPR
#line 104 "sintatico.y"
                                        {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"*",yystack_[0].value.as < node > ());}
#line 712 "y.tab.cc"
    break;

  case 13: // EXPR: EXPR '/' EXPR
#line 105 "sintatico.y"
                                        {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"/",yystack_[0].value.as < node > ());}
#line 718 "y.tab.cc"
    break;

  case 14: // EXPR: EXPR '%' EXPR
#line 106 "sintatico.y"
                                        {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"%",yystack_[0].value.as < node > ());}
#line 724 "y.tab.cc"
    break;

  case 15: // EXPR: EXPR OP_EQ EXPR
#line 109 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"==",yystack_[0].value.as < node > ());}
#line 730 "y.tab.cc"
    break;

  case 16: // EXPR: EXPR OP_NE EXPR
#line 110 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"!=",yystack_[0].value.as < node > ());}
#line 736 "y.tab.cc"
    break;

  case 17: // EXPR: EXPR OP_LE EXPR
#line 111 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"<=",yystack_[0].value.as < node > ());}
#line 742 "y.tab.cc"
    break;

  case 18: // EXPR: EXPR OP_GE EXPR
#line 112 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),">=",yystack_[0].value.as < node > ());}
#line 748 "y.tab.cc"
    break;

  case 19: // EXPR: EXPR OP_LT EXPR
#line 113 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"<",yystack_[0].value.as < node > ());}
#line 754 "y.tab.cc"
    break;

  case 20: // EXPR: EXPR OP_GT EXPR
#line 114 "sintatico.y"
                                          {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),">",yystack_[0].value.as < node > ());}
#line 760 "y.tab.cc"
    break;

  case 21: // EXPR: EXPR OP_OR EXPR
#line 117 "sintatico.y"
                                           {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"||",yystack_[0].value.as < node > ());}
#line 766 "y.tab.cc"
    break;

  case 22: // EXPR: EXPR OP_AND EXPR
#line 118 "sintatico.y"
                                           {yylhs.value.as < node > () = gen_expr(yystack_[2].value.as < node > (),"&&",yystack_[0].value.as < node > ());}
#line 772 "y.tab.cc"
    break;

  case 23: // EXPR: OP_NOT EXPR
#line 120 "sintatico.y"
                        {
				yylhs.value.as < node > ().label = gen_tmp_variable();
				variables.push_back({yylhs.value.as < node > ().label, "int"});
				yylhs.value.as < node > ().translation = yystack_[0].value.as < node > ().translation + "\t" + 
				yylhs.value.as < node > ().label + " = " + "!" + yystack_[0].value.as < node > ().label + ";\n";
			}
#line 783 "y.tab.cc"
    break;

  case 24: // EXPR: '(' EXPR ')'
#line 127 "sintatico.y"
                                       {yylhs.value.as < node > () = yystack_[1].value.as < node > ();}
#line 789 "y.tab.cc"
    break;

  case 25: // EXPR: TK_INT
#line 130 "sintatico.y"
                        {
				yylhs.value.as < node > ().label = gen_tmp_variable();
				variables.push_back({yylhs.value.as < node > ().label, "int"});
				yylhs.value.as < node > ().translation = "\t" + yylhs.value.as < node > ().label + " = " + yystack_[0].value.as < literal > ().label + ";\n";
			}
#line 799 "y.tab.cc"
    break;

  case 26: // EXPR: TK_FLOAT
#line 137 "sintatico.y"
                        {
				yylhs.value.as < node > ().label = gen_tmp_variable();
				variables.push_back({yylhs.value.as < node > ().label, "float"});
				yylhs.value.as < node > ().translation = "\t" + yylhs.value.as < node > ().label + " = " + yystack_[0].value.as < literal > ().label + ";\n";
			}
#line 809 "y.tab.cc"
    break;

  case 27: // EXPR: TK_CHAR
#line 144 "sintatico.y"
                        {
				yylhs.value.as < node > ().label = yystack_[0].value.as < literal > ().label;
				yylhs.value.as < node > ().translation = "";
			}
#line 818 "y.tab.cc"
    break;

  case 28: // EXPR: TK_BOOL
#line 150 "sintatico.y"
                        {
				yylhs.value.as < node > ().label = yystack_[0].value.as < literal > ().label;
				yylhs.value.as < node > ().translation = "";
			}
#line 827 "y.tab.cc"
    break;

  case 29: // EXPR: TK_ID
#line 156 "sintatico.y"
                        {
				symbol *sym = search_symbol(yystack_[0].value.as < symbol > ().label);
				yylhs.value.as < node > ().label = sym->label;
				yylhs.value.as < node > ().translation = "";
			}
#line 837 "y.tab.cc"
    break;


#line 841 "y.tab.cc"

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
        std::string msg = YY_("syntax error");
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

#if YYDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char parser::yypact_ninf_ = -20;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      25,   -20,   -20,    -3,   -20,   -20,   -10,    31,    31,    36,
      25,   -20,   -20,   -20,    82,    16,    31,   -20,   -20,    48,
     -20,   -20,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,   -20,    66,   -20,    -9,    -9,
      -9,    -9,    -9,    -9,    87,    32,   -19,   -19,   -20,   -20,
     -20,   -20
  };

  const signed char
  parser::yydefact_[] =
  {
       0,    25,    26,     0,    27,    28,    29,     0,     0,     0,
       2,     4,     5,     6,     7,     0,     0,    29,    23,     0,
       1,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,    24,    15,    16,
      17,    18,    19,    20,    22,    21,    10,    11,    12,    13,
      14,     9
  };

  const signed char
  parser::yypgoto_[] =
  {
     -20,   -20,   -20,    33,   -20,   -20,    -7
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     9,    10,    11,    12,    13,    14
  };

  const signed char
  parser::yytable_[] =
  {
      18,    19,    32,    33,    34,    15,    28,    29,    16,    36,
      30,    31,    32,    33,    34,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,     1,     2,
       3,     4,     5,     6,     1,     2,    20,     4,     5,    17,
      35,     0,     7,    21,     0,     0,     0,    28,     7,     0,
       8,    30,    31,    32,    33,    34,     8,    22,    23,    24,
      25,    26,    27,    28,    29,     0,     0,    30,    31,    32,
      33,    34,     0,     0,    37,    22,    23,    24,    25,    26,
      27,    28,    29,     0,     0,    30,    31,    32,    33,    34,
      51,    22,    23,    24,    25,    26,    27,    28,    29,     0,
       0,    30,    31,    32,    33,    34,    30,    31,    32,    33,
      34
  };

  const signed char
  parser::yycheck_[] =
  {
       7,     8,    21,    22,    23,     8,    15,    16,    18,    16,
      19,    20,    21,    22,    23,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,     3,     4,
       5,     6,     7,     8,     3,     4,     0,     6,     7,     8,
      24,    -1,    17,    10,    -1,    -1,    -1,    15,    17,    -1,
      25,    19,    20,    21,    22,    23,    25,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    19,    20,    21,
      22,    23,    -1,    -1,    26,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    19,    20,    21,    22,    23,
      24,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    19,    20,    21,    22,    23,    19,    20,    21,    22,
      23
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,    17,    25,    28,
      29,    30,    31,    32,    33,     8,    18,     8,    33,    33,
       0,    30,     9,    10,    11,    12,    13,    14,    15,    16,
      19,    20,    21,    22,    23,    24,    33,    26,    33,    33,
      33,    33,    33,    33,    33,    33,    33,    33,    33,    33,
      33,    24
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    27,    28,    29,    29,    30,    30,    30,    31,    32,
      33,    33,    33,    33,    33,    33,    33,    33,    33,    33,
      33,    33,    33,    33,    33,    33,    33,    33,    33,    33
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     1,     1,     1,     3,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     1,     1,     1,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TK_INT", "TK_FLOAT",
  "TK_TYPE", "TK_CHAR", "TK_BOOL", "TK_ID", "OP_EQ", "OP_NE", "OP_LE",
  "OP_GE", "OP_LT", "OP_GT", "OP_AND", "OP_OR", "OP_NOT", "OP_AT", "'+'",
  "'-'", "'*'", "'/'", "'%'", "';'", "'('", "')'", "$accept", "S",
  "COMMANDS", "STATEMENT", "DECL", "ATRI", "EXPR", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,    67,    67,    76,    77,    79,    80,    81,    83,    92,
     102,   103,   104,   105,   106,   109,   110,   111,   112,   113,
     114,   117,   118,   119,   127,   129,   136,   143,   149,   155
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
#line 1183 "y.tab.cc"

#line 162 "sintatico.y"


void yy::parser::error(const std::string& s){
    std::cerr << "Erro na linha " << yylineno << ": " << s << std::endl;
}

string gen_tmp_variable()
{
	tmp_var_count++;
	return "t" + to_string(tmp_var_count);
}

string gen_declarations(){
	string res;
    for(const auto& var : variables)
        res += "\t" + var.second + " " + var.first + ";\n";
    return res;
}

node gen_expr(const node& l, string op, const node& r){
    node v;
    v.label = gen_tmp_variable(); 
    variables.push_back({v.label, "int"}); 
    v.translation = l.translation + r.translation + "\t" + 
                    v.label + " = " + l.label + " " + op + " " + r.label + ";\n";
    return v;
}
// Procurar a variavel na tabela
symbol* search_symbol(string label){
	for(symbol& sym : symbols){ 
		if(sym.name == label){
			if(sym.label.empty()){
				sym.label = gen_tmp_variable(); // Se nao tiver label alocada, aloca
				variables.push_back({sym.label, sym.type});
			}
			return &sym;
		}
	}	
	return nullptr; // Não tem 
}

int main(int argc, char* argv[]){
    tmp_var_count = 0;
    yy::parser p;
    
    if (p.parse() == 0){ 
        cout << code;
        
        ofstream outFile("code.c");
        if(outFile.is_open()) outFile << code << endl;
        
        ofstream ofile("tabela_de_simbolos.txt");
        if(ofile.is_open()) {
            for(const auto& sym : symbols) {
                ofile << sym.type << " | " << sym.name << " | " << sym.label << endl;
            }
        }
    }
    return 0;
}
