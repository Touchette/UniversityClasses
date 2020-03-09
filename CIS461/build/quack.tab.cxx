// A Bison parser, made by GNU Bison 3.5.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "quack.tab.hxx"


// Unqualified %code blocks.
#line 19 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"

    #include "lex.yy.h"
    #undef yylex
    #define yylex lexer.yylex  // Within Bison's parse() we should invoke lexer.yylex(), not the global yylex()

    // this is used to simplify the grammar, as many call nodes 
    // use the same format to construct themselves for the AST
    AST::Node *getCallNode(Type callType, std::string callStr, 
                            AST::Node *dollarOne, AST::Node *dollarThree) {
        AST::Node *retVal = new AST::Node(CALL); 
        retVal->subType = callType; 
        retVal->insert(dollarOne);
        AST::Node *method = new AST::Node(IDENT, callStr); 
        method->subType = METHOD; 
        retVal->insert(method);
        AST::Node *actuals = new AST::Node(ACTUAL_ARGS);
        AST::Node *method_arg = new AST::Node(METHOD_ARG);
        dollarThree->subType = METHOD_ARG;
        method_arg->insert(dollarThree);
        actuals->insert(method_arg);
        retVal->insert(actuals);
        return retVal;
    }

    AST::Node *getNotCallNode(Type callType, std::string callStr, 
                            AST::Node *dollarOne) {
        AST::Node *retVal = new AST::Node(CALL); 
        retVal->subType = callType; 
        retVal->insert(dollarOne);
        AST::Node *method = new AST::Node(IDENT, callStr); 
        method->subType = METHOD; 
        retVal->insert(method);
        return retVal;
    }

#line 81 "quack.tab.cxx"


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

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


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
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
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
#line 172 "quack.tab.cxx"


  /// Build a parser object.
  parser::parser (yy::Lexer& lexer_yyarg, AST::Node** root_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg),
      root (root_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value (std::move (that.value))
    , location (std::move (that.location))
  {}
#endif

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_type.
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


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

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
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

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
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
  parser::yypop_ (int n)
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
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
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

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

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
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
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

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
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
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 111 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                        { *root = new AST::Node(PROGRAM); (yylhs.value.node) = *root; 
                          (yylhs.value.node)->insert((yystack_[1].value.node)); (yylhs.value.node)->insert((yystack_[0].value.node)); }
#line 629 "quack.tab.cxx"
    break;

  case 3:
#line 122 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                        { (yylhs.value.node)->insert((yystack_[0].value.node)); (yylhs.value.node) = (yystack_[1].value.node); }
#line 635 "quack.tab.cxx"
    break;

  case 4:
#line 123 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                        { (yylhs.value.node) = new AST::Node(CLASSES); }
#line 641 "quack.tab.cxx"
    break;

  case 5:
#line 128 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
            { (yylhs.value.node) = new AST::Node(CLASS); /*'*/
              (yystack_[8].value.node)->subType = CLASS_NAME; (yylhs.value.node)->insert((yystack_[8].value.node)); 
              (yylhs.value.node)->insert((yystack_[4].value.node)); 
              AST::Node *method = new AST::Node(METHOD); 
              method->subType = CONSTRUCTOR;
              AST::Node *methodname = new AST::Node(IDENT, METHOD_NAME, (yystack_[8].value.node)->name);
              method->insert(methodname);
              AST::Node *ret = new AST::Node(IDENT, RETURN_TYPE, (yystack_[8].value.node)->name);
              method->insert((yystack_[6].value.node));
              method->insert(ret);
              method->insert((yystack_[2].value.node));
              (yylhs.value.node)->insert(method);
              (yylhs.value.node)->insert((yystack_[1].value.node)); }
#line 659 "quack.tab.cxx"
    break;

  case 6:
#line 144 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                        { (yystack_[0].value.node)->subType = SUPER_NAME; (yylhs.value.node) = (yystack_[0].value.node); }
#line 665 "quack.tab.cxx"
    break;

  case 7:
#line 145 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                      { (yylhs.value.node) = new AST::Node(IDENT, SUPER_NAME, "Obj"); }
#line 671 "quack.tab.cxx"
    break;

  case 8:
#line 151 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                         { (yystack_[1].value.node)->insert((yystack_[0].value.node)); (yylhs.value.node) = (yystack_[1].value.node); }
#line 677 "quack.tab.cxx"
    break;

  case 9:
#line 152 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                      { (yylhs.value.node) = new AST::Node(METHODS); }
#line 683 "quack.tab.cxx"
    break;

  case 10:
#line 157 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                            { (yylhs.value.node) = new AST::Node(METHOD); (yystack_[4].value.node)->subType = METHOD_NAME; 
                              (yylhs.value.node)->insert((yystack_[4].value.node)); (yylhs.value.node)->insert((yystack_[2].value.node)); 
                              AST::Node *ret = new AST::Node(IDENT, RETURN_TYPE, "Nothing");
                              (yylhs.value.node)->insert(ret); 
                              (yystack_[0].value.node)->subType = STATEMENTS; (yylhs.value.node)->insert((yystack_[0].value.node)); }
#line 693 "quack.tab.cxx"
    break;

  case 11:
#line 163 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                            { (yylhs.value.node) = new AST::Node(METHOD); 
                              (yystack_[6].value.node)->subType = METHOD_NAME; (yylhs.value.node)->insert((yystack_[6].value.node)); 
                              (yylhs.value.node)->insert((yystack_[4].value.node)); (yystack_[1].value.node)->subType = RETURN_TYPE; (yylhs.value.node)->insert((yystack_[1].value.node)); 
                              (yystack_[0].value.node)->subType = STATEMENTS; (yylhs.value.node)->insert((yystack_[0].value.node)); }
#line 702 "quack.tab.cxx"
    break;

  case 12:
#line 173 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
               { (yylhs.value.node) = (yystack_[0].value.node); }
#line 708 "quack.tab.cxx"
    break;

  case 13:
#line 174 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                      { (yylhs.value.node) = new AST::Node(FORMAL_ARGS); }
#line 714 "quack.tab.cxx"
    break;

  case 14:
#line 178 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
              { (yylhs.value.node) = new AST::Node(FORMAL_ARGS); (yylhs.value.node)->insert((yystack_[0].value.node)); }
#line 720 "quack.tab.cxx"
    break;

  case 15:
#line 179 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                       { (yylhs.value.node) = (yystack_[2].value.node); (yystack_[2].value.node)->insert((yystack_[0].value.node)); }
#line 726 "quack.tab.cxx"
    break;

  case 16:
#line 183 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                          { (yylhs.value.node) = new AST::Node(CLASS_ARG); (yystack_[2].value.node)->subType = VAR_IDENT; (yylhs.value.node)->insert((yystack_[2].value.node)); 
                            (yystack_[0].value.node)->subType = TYPE_IDENT; (yylhs.value.node)->insert((yystack_[0].value.node)); }
#line 733 "quack.tab.cxx"
    break;

  case 17:
#line 190 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                        { (yylhs.value.node) = (yystack_[1].value.node); }
#line 739 "quack.tab.cxx"
    break;

  case 18:
#line 194 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                     { (yystack_[1].value.node)->insert((yystack_[0].value.node)); (yylhs.value.node) = (yystack_[1].value.node); }
#line 745 "quack.tab.cxx"
    break;

  case 19:
#line 195 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                      { (yylhs.value.node) = new AST::Node(BLOCK); (yylhs.value.node)->subType = STATEMENTS; }
#line 751 "quack.tab.cxx"
    break;

  case 20:
#line 201 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                                        { (yylhs.value.node) = new AST::Node(IF); AST::Node *cond = new AST::Node(COND); 
                                          cond->insert((yystack_[2].value.node)); (yylhs.value.node)->insert(cond); 
                                          (yystack_[1].value.node)->subType = TRUE_STATEMENTS; (yylhs.value.node)->insert((yystack_[1].value.node)); (yylhs.value.node)->insert((yystack_[0].value.node)); }
#line 759 "quack.tab.cxx"
    break;

  case 21:
#line 207 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                                        { (yylhs.value.node) = new AST::Node(BLOCK); (yylhs.value.node)->subType = FALSE_STATEMENTS;
                                          AST::Node *newif = new AST::Node(IF); AST::Node *cond = new AST::Node(COND); 
                                          cond->insert((yystack_[2].value.node)); newif->insert(cond); 
                                          (yystack_[1].value.node)->subType = TRUE_STATEMENTS; newif->insert((yystack_[1].value.node)); 
                                          newif->insert((yystack_[0].value.node)); (yylhs.value.node)->insert(newif); }
#line 769 "quack.tab.cxx"
    break;

  case 22:
#line 212 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                            { (yystack_[0].value.node)->subType = FALSE_STATEMENTS; (yylhs.value.node) = (yystack_[0].value.node); }
#line 775 "quack.tab.cxx"
    break;

  case 23:
#line 213 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                            { (yylhs.value.node) = new AST::Node(BLOCK); (yylhs.value.node)->subType = FALSE_STATEMENTS; }
#line 781 "quack.tab.cxx"
    break;

  case 24:
#line 218 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                                  { (yylhs.value.node) = new AST::Node(WHILE); AST::Node *cond = new AST::Node(COND); 
                                    cond->insert((yystack_[1].value.node)); (yylhs.value.node)->insert(cond); (yylhs.value.node)->insert((yystack_[0].value.node)); }
#line 788 "quack.tab.cxx"
    break;

  case 25:
#line 224 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                                { (yylhs.value.node) = new AST::Node(ASSIGN); (yylhs.value.node)->insert((yystack_[3].value.node)); (yystack_[1].value.node)->subType = R_EXPR; (yylhs.value.node)->insert((yystack_[1].value.node)); }
#line 794 "quack.tab.cxx"
    break;

  case 26:
#line 225 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                                          { (yylhs.value.node) = new AST::Node(ASSIGN); (yylhs.value.node)->insert((yystack_[5].value.node)); (yystack_[3].value.node)->subType = TYPE_IDENT; (yylhs.value.node)->insert((yystack_[3].value.node)); 
                                            (yystack_[1].value.node)->subType = R_EXPR; (yylhs.value.node)->insert((yystack_[1].value.node)); }
#line 801 "quack.tab.cxx"
    break;

  case 27:
#line 227 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                     { (yylhs.value.node) = (yystack_[1].value.node); }
#line 807 "quack.tab.cxx"
    break;

  case 28:
#line 228 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                            { (yylhs.value.node) = new AST::Node(RETURN); (yystack_[1].value.node)->subType = R_EXPR; (yylhs.value.node)->insert((yystack_[1].value.node)); }
#line 813 "quack.tab.cxx"
    break;

  case 29:
#line 229 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                     { (yylhs.value.node) = new AST::Node(RETURN); (yylhs.value.node)->insert(new AST::Node(IDENT, "Nothing")); }
#line 819 "quack.tab.cxx"
    break;

  case 30:
#line 230 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                   { (yylhs.value.node) = (yystack_[0].value.node); }
#line 825 "quack.tab.cxx"
    break;

  case 31:
#line 236 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                                            { (yylhs.value.node) = new AST::Node(TYPECASE); 
                                              (yylhs.value.node)->insert((yystack_[3].value.node)); (yylhs.value.node)->insert((yystack_[1].value.node)); }
#line 832 "quack.tab.cxx"
    break;

  case 32:
#line 241 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                             { (yystack_[1].value.node)->insert((yystack_[0].value.node)); (yylhs.value.node) = (yystack_[1].value.node); }
#line 838 "quack.tab.cxx"
    break;

  case 33:
#line 242 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                             { (yylhs.value.node) = new AST::Node(TYPE_ALTERNATIVES); }
#line 844 "quack.tab.cxx"
    break;

  case 34:
#line 246 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                                     { (yylhs.value.node) = new AST::Node(TYPE_ALTERNATIVE); 
                                       (yystack_[3].value.node)->subType = VAR_IDENT; (yylhs.value.node)->insert((yystack_[3].value.node)); 
                                       (yystack_[1].value.node)->subType = TYPE_IDENT; (yylhs.value.node)->insert((yystack_[1].value.node)); (yylhs.value.node)->insert((yystack_[0].value.node)); }
#line 852 "quack.tab.cxx"
    break;

  case 35:
#line 254 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                     { (yylhs.value.node) = new AST::Node(STRCONST, std::string((yystack_[0].value.str))); }
#line 858 "quack.tab.cxx"
    break;

  case 36:
#line 255 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                  { (yylhs.value.node) = new AST::Node(INTCONST, (yystack_[0].value.num)); }
#line 864 "quack.tab.cxx"
    break;

  case 37:
#line 256 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                 { (yylhs.value.node) = new AST::Node(LOAD); (yylhs.value.node)->insert((yystack_[0].value.node)); (yylhs.value.node)->subType = L_EXPR; }
#line 870 "quack.tab.cxx"
    break;

  case 38:
#line 257 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                                  { AST::Node *zero = new AST::Node(INTCONST, 0);
                                    (yylhs.value.node) = getCallNode(MINUS, "MINUS", zero, (yystack_[0].value.node)); }
#line 877 "quack.tab.cxx"
    break;

  case 39:
#line 259 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                            { (yylhs.value.node) = getCallNode(MULT, "TIMES", (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 883 "quack.tab.cxx"
    break;

  case 40:
#line 260 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                            { (yylhs.value.node) = getCallNode(DIV, "DIVIDE", (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 889 "quack.tab.cxx"
    break;

  case 41:
#line 261 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                            { (yylhs.value.node) = getCallNode(PLUS, "PLUS", (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 895 "quack.tab.cxx"
    break;

  case 42:
#line 262 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                            { (yylhs.value.node) = getCallNode(MINUS, "MINUS", (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 901 "quack.tab.cxx"
    break;

  case 43:
#line 263 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                               { (yylhs.value.node) = getCallNode(EQ, "EQUALS", (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 907 "quack.tab.cxx"
    break;

  case 44:
#line 264 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                               { (yylhs.value.node) = getCallNode(ATMOST, "ATMOST", (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 913 "quack.tab.cxx"
    break;

  case 45:
#line 265 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                            { (yylhs.value.node) = getCallNode(LESSER, "LESSER", (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 919 "quack.tab.cxx"
    break;

  case 46:
#line 266 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                                { (yylhs.value.node) = getCallNode(ATLEAST, "ATLEAST", (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 925 "quack.tab.cxx"
    break;

  case 47:
#line 267 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                            { (yylhs.value.node) = getCallNode(GREATER, "GREATER", (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 931 "quack.tab.cxx"
    break;

  case 48:
#line 268 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                            { (yylhs.value.node) = getCallNode(AND, "AND", (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 937 "quack.tab.cxx"
    break;

  case 49:
#line 269 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                           { (yylhs.value.node) = getCallNode(OR, "OR", (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 943 "quack.tab.cxx"
    break;

  case 50:
#line 270 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                     { (yylhs.value.node) = getNotCallNode(NOT, "NOT", (yystack_[0].value.node)); }
#line 949 "quack.tab.cxx"
    break;

  case 51:
#line 271 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                         { (yylhs.value.node) = (yystack_[1].value.node); }
#line 955 "quack.tab.cxx"
    break;

  case 52:
#line 272 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                                               { (yylhs.value.node) = new AST::Node(CALL); (yylhs.value.node)->insert((yystack_[5].value.node)); (yystack_[3].value.node)->subType = METHOD;
                                                 (yylhs.value.node)->insert((yystack_[3].value.node)); (yylhs.value.node)->insert((yystack_[1].value.node)); }
#line 962 "quack.tab.cxx"
    break;

  case 53:
#line 274 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                                    { (yylhs.value.node) = new AST::Node(CONSTRUCTOR); (yylhs.value.node)->insert((yystack_[3].value.node)); (yylhs.value.node)->insert((yystack_[1].value.node)); }
#line 968 "quack.tab.cxx"
    break;

  case 54:
#line 278 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                { (yylhs.value.node) = (yystack_[0].value.node); (yylhs.value.node)->subType = LOC; /* new AST::Node(LOAD); $$->insert($1); */ }
#line 974 "quack.tab.cxx"
    break;

  case 55:
#line 279 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                           { (yylhs.value.node) = new AST::Node(DOT); (yylhs.value.node)->subType = L_EXPR; (yylhs.value.node)->insert((yystack_[2].value.node)); 
                             (yystack_[0].value.node)->subType = R_EXPR; (yylhs.value.node)->insert((yystack_[0].value.node)); }
#line 981 "quack.tab.cxx"
    break;

  case 56:
#line 286 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                  { (yylhs.value.node) = (yystack_[0].value.node); }
#line 987 "quack.tab.cxx"
    break;

  case 57:
#line 287 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                      { (yylhs.value.node) = new AST::Node(ACTUAL_ARGS); }
#line 993 "quack.tab.cxx"
    break;

  case 58:
#line 291 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                 { (yylhs.value.node) = new AST::Node(ACTUAL_ARGS); (yylhs.value.node)->insert((yystack_[0].value.node)); }
#line 999 "quack.tab.cxx"
    break;

  case 59:
#line 292 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                             { (yylhs.value.node) = (yystack_[2].value.node); (yystack_[2].value.node)->insert((yystack_[0].value.node)); }
#line 1005 "quack.tab.cxx"
    break;

  case 60:
#line 296 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                 { (yylhs.value.node) = new AST::Node(METHOD_ARG); (yystack_[0].value.node)->subType = METHOD_ARG; (yylhs.value.node)->insert((yystack_[0].value.node)); }
#line 1011 "quack.tab.cxx"
    break;

  case 61:
#line 302 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"
                { (yylhs.value.node) = new AST::Node(IDENT, (yystack_[0].value.str)); }
#line 1017 "quack.tab.cxx"
    break;


#line 1021 "quack.tab.cxx"

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
      YY_STACK_PRINT ();

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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

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
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -49;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     -49,     1,    27,   -49,    17,   -49,   131,   -49,     8,   -49,
     -49,    11,    11,    85,    11,    11,    11,    11,   -49,   -49,
     142,   -18,     9,    17,   206,   -49,   206,   -49,   158,   225,
     277,   -49,   244,    11,    11,    11,    11,    11,    11,    11,
      11,    11,    11,    11,    17,   -49,    17,    11,    11,    13,
      22,   -49,    28,   -49,     3,   -49,   -49,   -49,   -49,   -17,
     -17,   -17,   277,   277,   -17,   -17,    -6,    -6,    15,    15,
      31,    29,   174,   262,    32,    33,   -49,    57,    17,    17,
     108,    11,    34,   -49,   -16,    11,    11,   -49,   -49,    11,
      17,    35,   -49,   -49,   -49,   206,   -49,   -49,   -49,    36,
      38,   190,   -49,   -49,   -49,     3,    17,   -49,   -49,   131,
     -49,    34,     0,   -49,    17,   -49,   -49,    42,    17,    45,
       2,    17,   -49,    34,   -49
  };

  const signed char
  parser::yydefact_[] =
  {
       4,     0,    19,     1,     0,     3,     2,    61,     0,    35,
      36,     0,     0,     0,     0,     0,     0,     0,    18,    30,
       0,    37,    54,    13,     0,    37,     0,    29,     0,     0,
      50,    38,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    27,     0,     0,    57,     0,
      12,    14,     0,    19,    23,    24,    28,    33,    51,    46,
      44,    43,    48,    49,    45,    47,    42,    41,    39,    40,
      55,     0,     0,    60,     0,    56,    58,     7,     0,     0,
       0,     0,     0,    20,     0,    57,     0,    25,    53,     0,
       0,     0,    15,    16,    17,     0,    22,    31,    32,     0,
       0,     0,    59,     6,    19,    23,     0,    52,    26,     9,
      21,     0,     0,    34,     0,     5,     8,     0,    13,     0,
       0,     0,    10,     0,    11
  };

  const signed char
  parser::yypgoto_[] =
  {
     -49,   -49,   -49,   -49,   -49,   -49,   -49,   -45,   -49,     4,
     -24,   -48,   -49,   -27,   -49,   -49,   -49,    12,    -3,    -2,
     -49,   -10,    -4
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     1,     2,     5,    91,   112,   116,    49,    50,    51,
      54,     6,    18,    83,    19,    84,    98,    20,    25,    74,
      75,    76,    22
  };

  const signed char
  parser::yytable_[] =
  {
       8,     3,    55,    21,     7,    80,   114,    40,    41,    42,
      43,    44,    81,    82,     9,    10,    46,    97,    47,    52,
      42,    43,    44,    24,    26,    28,    29,    30,    31,    32,
      15,     7,     4,   115,    53,    16,   121,     7,    23,    48,
      70,    17,    71,    44,    77,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,   109,    78,    96,    72,
      73,    85,    79,    88,    90,    86,    53,   104,    89,   107,
     106,   105,   118,   119,    52,    93,   120,    21,   110,   102,
      99,     0,    92,   100,     0,     0,   103,   113,     9,    10,
       0,     0,     0,    95,     0,     0,   122,    73,   101,   124,
       0,    73,   111,     0,    15,     7,    21,     0,     0,    16,
     117,     9,    10,     0,    52,    17,    11,   123,     0,    12,
      13,    14,    27,     0,     0,     0,     0,    15,     7,     0,
       0,     0,    16,     0,     9,    10,     0,     0,    17,    11,
       0,    94,    12,    13,    14,     0,     0,     0,     0,     0,
      15,     7,     0,     0,     0,    16,    33,    34,    35,    36,
      37,    17,     0,     0,    38,    39,    40,    41,    42,    43,
      44,     0,    33,    34,    35,    36,    37,     0,     0,    45,
      38,    39,    40,    41,    42,    43,    44,     0,    33,    34,
      35,    36,    37,     0,     0,    56,    38,    39,    40,    41,
      42,    43,    44,     0,    33,    34,    35,    36,    37,     0,
       0,    87,    38,    39,    40,    41,    42,    43,    44,     0,
      33,    34,    35,    36,    37,     0,     0,   108,    38,    39,
      40,    41,    42,    43,    44,     0,     0,     0,    53,    33,
      34,    35,    36,    37,     0,     0,     0,    38,    39,    40,
      41,    42,    43,    44,     0,     0,     0,    57,    33,    34,
      35,    36,    37,     0,     0,     0,    38,    39,    40,    41,
      42,    43,    44,     0,     0,    58,    33,    34,    35,    36,
      37,     0,     0,     0,    38,    39,    40,    41,    42,    43,
      44,    33,    34,    35,     0,     0,     0,     0,     0,    38,
      39,    40,    41,    42,    43,    44
  };

  const signed char
  parser::yycheck_[] =
  {
       4,     0,    26,     6,    20,    53,     6,    24,    25,    26,
      27,    28,     9,    10,     3,     4,    34,    33,    36,    23,
      26,    27,    28,    11,    12,    13,    14,    15,    16,    17,
      19,    20,     5,    33,    32,    24,    34,    20,    30,    30,
      44,    30,    46,    28,    31,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,   104,    35,    82,    47,
      48,    30,    34,    31,     7,    36,    32,    32,    35,    31,
      34,    95,    30,   118,    78,    79,    31,    80,   105,    89,
      84,    -1,    78,    85,    -1,    -1,    90,   111,     3,     4,
      -1,    -1,    -1,    81,    -1,    -1,   120,    85,    86,   123,
      -1,    89,   106,    -1,    19,    20,   109,    -1,    -1,    24,
     114,     3,     4,    -1,   118,    30,     8,   121,    -1,    11,
      12,    13,    37,    -1,    -1,    -1,    -1,    19,    20,    -1,
      -1,    -1,    24,    -1,     3,     4,    -1,    -1,    30,     8,
      -1,    33,    11,    12,    13,    -1,    -1,    -1,    -1,    -1,
      19,    20,    -1,    -1,    -1,    24,    14,    15,    16,    17,
      18,    30,    -1,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    14,    15,    16,    17,    18,    -1,    -1,    37,
      22,    23,    24,    25,    26,    27,    28,    -1,    14,    15,
      16,    17,    18,    -1,    -1,    37,    22,    23,    24,    25,
      26,    27,    28,    -1,    14,    15,    16,    17,    18,    -1,
      -1,    37,    22,    23,    24,    25,    26,    27,    28,    -1,
      14,    15,    16,    17,    18,    -1,    -1,    37,    22,    23,
      24,    25,    26,    27,    28,    -1,    -1,    -1,    32,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    -1,    32,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    31,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    22,    23,    24,    25,    26,    27,
      28,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    26,    27,    28
  };

  const signed char
  parser::yystos_[] =
  {
       0,    39,    40,     0,     5,    41,    49,    20,    60,     3,
       4,     8,    11,    12,    13,    19,    24,    30,    50,    52,
      55,    56,    60,    30,    55,    56,    55,    37,    55,    55,
      55,    55,    55,    14,    15,    16,    17,    18,    22,    23,
      24,    25,    26,    27,    28,    37,    34,    36,    30,    45,
      46,    47,    60,    32,    48,    48,    37,    32,    31,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      60,    60,    55,    55,    57,    58,    59,    31,    35,    34,
      49,     9,    10,    51,    53,    30,    36,    37,    31,    35,
       7,    42,    47,    60,    33,    55,    48,    33,    54,    60,
      57,    55,    59,    60,    32,    48,    34,    31,    37,    49,
      51,    60,    43,    48,     6,    33,    44,    60,    30,    45,
      31,    34,    48,    60,    48
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    38,    39,    40,    40,    41,    42,    42,    43,    43,
      44,    44,    45,    45,    46,    46,    47,    48,    49,    49,
      50,    51,    51,    51,    50,    50,    50,    50,    50,    50,
      50,    52,    53,    53,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    56,    56,    57,    57,    58,    58,
      59,    60
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     2,     0,    10,     2,     0,     2,     0,
       6,     8,     1,     0,     1,     3,     3,     3,     2,     0,
       4,     4,     2,     0,     3,     4,     6,     2,     3,     2,
       1,     5,     2,     0,     4,     1,     1,     1,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     3,     6,     4,     1,     3,     1,     0,     1,     3,
       1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "STRING_LIT", "INT_LIT", "CLASS", "DEF",
  "EXTENDS", "IF", "ELIF", "ELSE", "WHILE", "RETURN", "TYPECASE",
  "ATLEAST", "ATMOST", "EQUALS", "AND", "OR", "NOT", "IDENT", "NEG", "'<'",
  "'>'", "'-'", "'+'", "'*'", "'/'", "'.'", "UMINUS", "'('", "')'", "'{'",
  "'}'", "':'", "','", "'='", "';'", "$accept", "program", "classes",
  "class", "extends", "methods", "method", "formal_args", "args", "arg",
  "stmt_block", "stmts", "stmt", "opt_elif", "typecase", "type_alts",
  "type_alt", "r_expr", "l_expr", "actual_args", "actuals", "actual",
  "ident", YY_NULLPTR
  };


  const short
  parser::yyrline_[] =
  {
       0,   111,   111,   122,   123,   127,   144,   145,   151,   152,
     156,   162,   173,   174,   178,   179,   183,   190,   194,   195,
     201,   207,   212,   213,   218,   224,   225,   227,   228,   229,
     230,   236,   241,   242,   246,   254,   255,   256,   257,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   274,   278,   279,   286,   287,   291,   292,
     296,   302
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
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

  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      30,    31,    26,    25,    35,    24,    28,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    34,    37,
      22,    36,    23,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    29
    };
    const int user_token_number_max_ = 277;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

} // yy
#line 1481 "quack.tab.cxx"

#line 305 "/home/nataliee/Documents/Repos/UniversityClasses/CIS461/src/quack.yxx"


// -~-~-~- -~-~-~- -~-~-~-~

#include "Messages.h"

void yy::parser::error(const location_type& loc, const std::string& msg) {
    report::error_at(loc, msg, PARSER);
}
