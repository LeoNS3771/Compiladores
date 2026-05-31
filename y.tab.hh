// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file y.tab.hh
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_Y_TAB_HH_INCLUDED
# define YY_YY_Y_TAB_HH_INCLUDED
// "%code requires" blocks.
#line 11 "sintatico.y"

    #include "tokens.hh"

#line 53 "y.tab.hh"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif



#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

namespace yy {
#line 188 "y.tab.hh"




  /// A Bison parser.
  class parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // COMMANDS
      // STATEMENT
      // DECLARATION
      // ASSIGNMENT
      // BLOCK
      // CONDITIONAL
      // OPT_ASSIGNMENT
      // LOOP
      // LOOPCONTROL
      // SWITCHBLOCK
      // CASE_LIST
      // CASE_ITEM
      // DEFAULT
      // IO
      // LVAL
      // RVAL
      // EXPR
      char dummy1[sizeof (node)];

      // OP_ADD
      // OP_MINUS
      // OP_MULT
      // OP_DIV
      // OP_MOD
      // OP_EQ
      // OP_NE
      // OP_LE
      // OP_GE
      // OP_LT
      // OP_GT
      // OP_OR
      // OP_AND
      // OP_NOT
      char dummy2[sizeof (op)];

      // TK_ID
      char dummy3[sizeof (std::shared_ptr<symbol>)];

      // TK_INT
      // TK_FLOAT
      // TK_CHAR
      // TK_STRING
      // TK_BOOL
      // TK_TYPE
      // TK_VAR
      // TK_CAST
      // TK_SBLOCK
      // TK_EBLOCK
      // TK_IF
      // TK_ELSE
      // TK_WHILE
      // TK_DO
      // TK_BREAK
      // TK_FOR
      // TK_IN
      // TK_RANGE
      // TK_CONTINUE
      // TK_CASE
      // TK_SWITCH
      // TK_DEFAULT
      // TK_PRINT
      // TK_INPUT
      char dummy4[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;


    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    TK_INT = 258,                  // TK_INT
    TK_FLOAT = 259,                // TK_FLOAT
    TK_CHAR = 260,                 // TK_CHAR
    TK_STRING = 261,               // TK_STRING
    TK_BOOL = 262,                 // TK_BOOL
    TK_TYPE = 263,                 // TK_TYPE
    TK_VAR = 264,                  // TK_VAR
    TK_CAST = 265,                 // TK_CAST
    TK_SBLOCK = 266,               // TK_SBLOCK
    TK_EBLOCK = 267,               // TK_EBLOCK
    TK_IF = 268,                   // TK_IF
    TK_ELSE = 269,                 // TK_ELSE
    TK_WHILE = 270,                // TK_WHILE
    TK_DO = 271,                   // TK_DO
    TK_BREAK = 272,                // TK_BREAK
    TK_FOR = 273,                  // TK_FOR
    TK_IN = 274,                   // TK_IN
    TK_RANGE = 275,                // TK_RANGE
    TK_CONTINUE = 276,             // TK_CONTINUE
    TK_CASE = 277,                 // TK_CASE
    TK_SWITCH = 278,               // TK_SWITCH
    TK_DEFAULT = 279,              // TK_DEFAULT
    TK_PRINT = 280,                // TK_PRINT
    TK_INPUT = 281,                // TK_INPUT
    TK_ID = 282,                   // TK_ID
    OP_ADD = 283,                  // OP_ADD
    OP_MINUS = 284,                // OP_MINUS
    OP_MULT = 285,                 // OP_MULT
    OP_DIV = 286,                  // OP_DIV
    OP_MOD = 287,                  // OP_MOD
    OP_EQ = 288,                   // OP_EQ
    OP_NE = 289,                   // OP_NE
    OP_LE = 290,                   // OP_LE
    OP_GE = 291,                   // OP_GE
    OP_LT = 292,                   // OP_LT
    OP_GT = 293,                   // OP_GT
    OP_OR = 294,                   // OP_OR
    OP_AND = 295,                  // OP_AND
    OP_NOT = 296,                  // OP_NOT
    OP_AT = 297                    // OP_AT
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 48, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_TK_INT = 3,                            // TK_INT
        S_TK_FLOAT = 4,                          // TK_FLOAT
        S_TK_CHAR = 5,                           // TK_CHAR
        S_TK_STRING = 6,                         // TK_STRING
        S_TK_BOOL = 7,                           // TK_BOOL
        S_TK_TYPE = 8,                           // TK_TYPE
        S_TK_VAR = 9,                            // TK_VAR
        S_TK_CAST = 10,                          // TK_CAST
        S_TK_SBLOCK = 11,                        // TK_SBLOCK
        S_TK_EBLOCK = 12,                        // TK_EBLOCK
        S_TK_IF = 13,                            // TK_IF
        S_TK_ELSE = 14,                          // TK_ELSE
        S_TK_WHILE = 15,                         // TK_WHILE
        S_TK_DO = 16,                            // TK_DO
        S_TK_BREAK = 17,                         // TK_BREAK
        S_TK_FOR = 18,                           // TK_FOR
        S_TK_IN = 19,                            // TK_IN
        S_TK_RANGE = 20,                         // TK_RANGE
        S_TK_CONTINUE = 21,                      // TK_CONTINUE
        S_TK_CASE = 22,                          // TK_CASE
        S_TK_SWITCH = 23,                        // TK_SWITCH
        S_TK_DEFAULT = 24,                       // TK_DEFAULT
        S_TK_PRINT = 25,                         // TK_PRINT
        S_TK_INPUT = 26,                         // TK_INPUT
        S_TK_ID = 27,                            // TK_ID
        S_OP_ADD = 28,                           // OP_ADD
        S_OP_MINUS = 29,                         // OP_MINUS
        S_OP_MULT = 30,                          // OP_MULT
        S_OP_DIV = 31,                           // OP_DIV
        S_OP_MOD = 32,                           // OP_MOD
        S_OP_EQ = 33,                            // OP_EQ
        S_OP_NE = 34,                            // OP_NE
        S_OP_LE = 35,                            // OP_LE
        S_OP_GE = 36,                            // OP_GE
        S_OP_LT = 37,                            // OP_LT
        S_OP_GT = 38,                            // OP_GT
        S_OP_OR = 39,                            // OP_OR
        S_OP_AND = 40,                           // OP_AND
        S_OP_NOT = 41,                           // OP_NOT
        S_OP_AT = 42,                            // OP_AT
        S_43_ = 43,                              // ';'
        S_44_ = 44,                              // ':'
        S_45_ = 45,                              // '('
        S_46_ = 46,                              // ')'
        S_47_ = 47,                              // ','
        S_YYACCEPT = 48,                         // $accept
        S_S = 49,                                // S
        S_COMMANDS = 50,                         // COMMANDS
        S_STATEMENT = 51,                        // STATEMENT
        S_DECLARATION = 52,                      // DECLARATION
        S_ASSIGNMENT = 53,                       // ASSIGNMENT
        S_BLOCK = 54,                            // BLOCK
        S_55_1 = 55,                             // $@1
        S_56_2 = 56,                             // $@2
        S_CONDITIONAL = 57,                      // CONDITIONAL
        S_58_3 = 58,                             // $@3
        S_OPT_ASSIGNMENT = 59,                   // OPT_ASSIGNMENT
        S_LOOP = 60,                             // LOOP
        S_61_4 = 61,                             // $@4
        S_62_5 = 62,                             // $@5
        S_63_6 = 63,                             // $@6
        S_64_7 = 64,                             // $@7
        S_LOOPCONTROL = 65,                      // LOOPCONTROL
        S_SWITCHBLOCK = 66,                      // SWITCHBLOCK
        S_CASE_LIST = 67,                        // CASE_LIST
        S_CASE_ITEM = 68,                        // CASE_ITEM
        S_DEFAULT = 69,                          // DEFAULT
        S_IO = 70,                               // IO
        S_LVAL = 71,                             // LVAL
        S_RVAL = 72,                             // RVAL
        S_EXPR = 73                              // EXPR
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
      {
        switch (this->kind ())
    {
      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
      case symbol_kind::S_BLOCK: // BLOCK
      case symbol_kind::S_CONDITIONAL: // CONDITIONAL
      case symbol_kind::S_OPT_ASSIGNMENT: // OPT_ASSIGNMENT
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
        value.move< node > (std::move (that.value));
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
        value.move< op > (std::move (that.value));
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.move< std::shared_ptr<symbol> > (std::move (that.value));
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
      case symbol_kind::S_TK_INPUT: // TK_INPUT
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#else
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, node&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const node& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, op&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const op& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<symbol>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<symbol>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v)
        : Base (t)
        , value (v)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
      case symbol_kind::S_BLOCK: // BLOCK
      case symbol_kind::S_CONDITIONAL: // CONDITIONAL
      case symbol_kind::S_OPT_ASSIGNMENT: // OPT_ASSIGNMENT
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
        value.template destroy< node > ();
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
        value.template destroy< op > ();
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.template destroy< std::shared_ptr<symbol> > ();
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
      case symbol_kind::S_TK_INPUT: // TK_INPUT
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#else
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, op v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const op& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::shared_ptr<symbol> v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const std::shared_ptr<symbol>& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const std::string& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
    };

    /// Build a parser object.
    parser ();
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF ()
      {
        return symbol_type (token::YYEOF);
      }
#else
      static
      symbol_type
      make_YYEOF ()
      {
        return symbol_type (token::YYEOF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#else
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#else
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_INT (std::string v)
      {
        return symbol_type (token::TK_INT, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_INT (const std::string& v)
      {
        return symbol_type (token::TK_INT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_FLOAT (std::string v)
      {
        return symbol_type (token::TK_FLOAT, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_FLOAT (const std::string& v)
      {
        return symbol_type (token::TK_FLOAT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_CHAR (std::string v)
      {
        return symbol_type (token::TK_CHAR, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_CHAR (const std::string& v)
      {
        return symbol_type (token::TK_CHAR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_STRING (std::string v)
      {
        return symbol_type (token::TK_STRING, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_STRING (const std::string& v)
      {
        return symbol_type (token::TK_STRING, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_BOOL (std::string v)
      {
        return symbol_type (token::TK_BOOL, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_BOOL (const std::string& v)
      {
        return symbol_type (token::TK_BOOL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_TYPE (std::string v)
      {
        return symbol_type (token::TK_TYPE, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_TYPE (const std::string& v)
      {
        return symbol_type (token::TK_TYPE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_VAR (std::string v)
      {
        return symbol_type (token::TK_VAR, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_VAR (const std::string& v)
      {
        return symbol_type (token::TK_VAR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_CAST (std::string v)
      {
        return symbol_type (token::TK_CAST, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_CAST (const std::string& v)
      {
        return symbol_type (token::TK_CAST, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_SBLOCK (std::string v)
      {
        return symbol_type (token::TK_SBLOCK, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_SBLOCK (const std::string& v)
      {
        return symbol_type (token::TK_SBLOCK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_EBLOCK (std::string v)
      {
        return symbol_type (token::TK_EBLOCK, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_EBLOCK (const std::string& v)
      {
        return symbol_type (token::TK_EBLOCK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_IF (std::string v)
      {
        return symbol_type (token::TK_IF, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_IF (const std::string& v)
      {
        return symbol_type (token::TK_IF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_ELSE (std::string v)
      {
        return symbol_type (token::TK_ELSE, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_ELSE (const std::string& v)
      {
        return symbol_type (token::TK_ELSE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_WHILE (std::string v)
      {
        return symbol_type (token::TK_WHILE, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_WHILE (const std::string& v)
      {
        return symbol_type (token::TK_WHILE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_DO (std::string v)
      {
        return symbol_type (token::TK_DO, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_DO (const std::string& v)
      {
        return symbol_type (token::TK_DO, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_BREAK (std::string v)
      {
        return symbol_type (token::TK_BREAK, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_BREAK (const std::string& v)
      {
        return symbol_type (token::TK_BREAK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_FOR (std::string v)
      {
        return symbol_type (token::TK_FOR, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_FOR (const std::string& v)
      {
        return symbol_type (token::TK_FOR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_IN (std::string v)
      {
        return symbol_type (token::TK_IN, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_IN (const std::string& v)
      {
        return symbol_type (token::TK_IN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_RANGE (std::string v)
      {
        return symbol_type (token::TK_RANGE, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_RANGE (const std::string& v)
      {
        return symbol_type (token::TK_RANGE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_CONTINUE (std::string v)
      {
        return symbol_type (token::TK_CONTINUE, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_CONTINUE (const std::string& v)
      {
        return symbol_type (token::TK_CONTINUE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_CASE (std::string v)
      {
        return symbol_type (token::TK_CASE, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_CASE (const std::string& v)
      {
        return symbol_type (token::TK_CASE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_SWITCH (std::string v)
      {
        return symbol_type (token::TK_SWITCH, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_SWITCH (const std::string& v)
      {
        return symbol_type (token::TK_SWITCH, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_DEFAULT (std::string v)
      {
        return symbol_type (token::TK_DEFAULT, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_DEFAULT (const std::string& v)
      {
        return symbol_type (token::TK_DEFAULT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_PRINT (std::string v)
      {
        return symbol_type (token::TK_PRINT, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_PRINT (const std::string& v)
      {
        return symbol_type (token::TK_PRINT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_INPUT (std::string v)
      {
        return symbol_type (token::TK_INPUT, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_INPUT (const std::string& v)
      {
        return symbol_type (token::TK_INPUT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TK_ID (std::shared_ptr<symbol> v)
      {
        return symbol_type (token::TK_ID, std::move (v));
      }
#else
      static
      symbol_type
      make_TK_ID (const std::shared_ptr<symbol>& v)
      {
        return symbol_type (token::TK_ID, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_ADD (op v)
      {
        return symbol_type (token::OP_ADD, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_ADD (const op& v)
      {
        return symbol_type (token::OP_ADD, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_MINUS (op v)
      {
        return symbol_type (token::OP_MINUS, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_MINUS (const op& v)
      {
        return symbol_type (token::OP_MINUS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_MULT (op v)
      {
        return symbol_type (token::OP_MULT, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_MULT (const op& v)
      {
        return symbol_type (token::OP_MULT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_DIV (op v)
      {
        return symbol_type (token::OP_DIV, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_DIV (const op& v)
      {
        return symbol_type (token::OP_DIV, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_MOD (op v)
      {
        return symbol_type (token::OP_MOD, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_MOD (const op& v)
      {
        return symbol_type (token::OP_MOD, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_EQ (op v)
      {
        return symbol_type (token::OP_EQ, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_EQ (const op& v)
      {
        return symbol_type (token::OP_EQ, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_NE (op v)
      {
        return symbol_type (token::OP_NE, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_NE (const op& v)
      {
        return symbol_type (token::OP_NE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_LE (op v)
      {
        return symbol_type (token::OP_LE, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_LE (const op& v)
      {
        return symbol_type (token::OP_LE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_GE (op v)
      {
        return symbol_type (token::OP_GE, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_GE (const op& v)
      {
        return symbol_type (token::OP_GE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_LT (op v)
      {
        return symbol_type (token::OP_LT, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_LT (const op& v)
      {
        return symbol_type (token::OP_LT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_GT (op v)
      {
        return symbol_type (token::OP_GT, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_GT (const op& v)
      {
        return symbol_type (token::OP_GT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_OR (op v)
      {
        return symbol_type (token::OP_OR, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_OR (const op& v)
      {
        return symbol_type (token::OP_OR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_AND (op v)
      {
        return symbol_type (token::OP_AND, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_AND (const op& v)
      {
        return symbol_type (token::OP_AND, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_NOT (op v)
      {
        return symbol_type (token::OP_NOT, std::move (v));
      }
#else
      static
      symbol_type
      make_OP_NOT (const op& v)
      {
        return symbol_type (token::OP_NOT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_AT ()
      {
        return symbol_type (token::OP_AT);
      }
#else
      static
      symbol_type
      make_OP_AT ()
      {
        return symbol_type (token::OP_AT);
      }
#endif


    class context
    {
    public:
      context (const parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 374,     ///< Last index in yytable_.
      yynnts_ = 26,  ///< Number of nonterminal symbols.
      yyfinal_ = 38 ///< Termination state number.
    };



  };

  inline
  parser::symbol_kind_type
  parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      45,    46,     2,     2,    47,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,    43,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
    };
    // Last valid token kind.
    const int code_max = 297;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
    {
      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
      case symbol_kind::S_BLOCK: // BLOCK
      case symbol_kind::S_CONDITIONAL: // CONDITIONAL
      case symbol_kind::S_OPT_ASSIGNMENT: // OPT_ASSIGNMENT
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
        value.copy< node > (YY_MOVE (that.value));
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
        value.copy< op > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.copy< std::shared_ptr<symbol> > (YY_MOVE (that.value));
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
      case symbol_kind::S_TK_INPUT: // TK_INPUT
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_COMMANDS: // COMMANDS
      case symbol_kind::S_STATEMENT: // STATEMENT
      case symbol_kind::S_DECLARATION: // DECLARATION
      case symbol_kind::S_ASSIGNMENT: // ASSIGNMENT
      case symbol_kind::S_BLOCK: // BLOCK
      case symbol_kind::S_CONDITIONAL: // CONDITIONAL
      case symbol_kind::S_OPT_ASSIGNMENT: // OPT_ASSIGNMENT
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
        value.move< node > (YY_MOVE (s.value));
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
        value.move< op > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TK_ID: // TK_ID
        value.move< std::shared_ptr<symbol> > (YY_MOVE (s.value));
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
      case symbol_kind::S_TK_INPUT: // TK_INPUT
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_kind.
  inline
  parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


} // yy
#line 2323 "y.tab.hh"




#endif // !YY_YY_Y_TAB_HH_INCLUDED
