// Adapted from: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

// TODO: you can either continue adding to this grammar file or
// rename parser_full.y to parser.y once you're happy with
// how this example works.

%code requires{
    #include "ast.hpp"

	using namespace ast;

    extern NodeList* g_root;
    extern FILE* yyin;
    int yylex(void);
    void yyerror(const char*);
	int yylex_destroy(void);
}

%union{
  Node*				node;
  NodeList*			node_list;
  int          		number_int;
  double       		number_float;
  std::string*		string;
  TypeSpecifier 	type_specifier;
  yytokentype  		token;
}

%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token TYPE_NAME TYPEDEF EXTERN STATIC AUTO REGISTER SIZEOF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <node> external_declaration function_definition primary_expression postfix_expression
%type <node> unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression
%type <node> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> conditional_expression assignment_expression expression constant_expression declaration init_declarator_list
%type <node> init_declarator struct_specifier struct_declaration_list struct_declaration specifier_qualifier_list struct_declarator_list
%type <node> struct_declarator enum_specifier enumerator_list enumerator declarator direct_declarator pointer parameter_declaration
%type <node> identifier_list type_name abstract_declarator direct_abstract_declarator initializer initializer_list statement labeled_statement
%type <node> compound_statement declaration_list expression_statement selection_statement iteration_statement jump_statement switch_case default_case


%type <node_list> statement_list parameter_list argument_expression_list translation_unit switch_case_list

%type <number_int> INT_CONSTANT STRING_LITERAL
%type <number_float> FLOAT_CONSTANT
%type <string> IDENTIFIER assignment_operator
%type <type_specifier> type_specifier declaration_specifiers


%start ROOT
%%

ROOT
    : translation_unit { g_root = $1; }

translation_unit
	: external_declaration { $$ = new NodeList(NodePtr($1)); }
    | translation_unit external_declaration { $1->PushBack(NodePtr($2)); $$=$1; }
	;


external_declaration
	: function_definition { $$ = $1; }
	| declaration { $$ = $1; } // Add global variables later
	;

function_definition
	: declaration_specifiers declarator compound_statement {
		$$ = new FunctionDefinition($1, NodePtr($2), NodePtr($3));
	}
    | declaration_specifiers declarator ';' {
		$$ = new FunctionDefinition($1, NodePtr($2), nullptr);
	}
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator ';' { $$ = new VariableDeclare($1, NodePtr($2)); }
	;

declaration_specifiers
	: type_specifier { $$ = $1; }
	;

type_specifier
	: INT {
		$$ = TypeSpecifier::INT;
	}
	| VOID {
		$$ = TypeSpecifier::VOID;
	}
	| FLOAT {
		$$ = TypeSpecifier::FLOAT;
	}
	| DOUBLE {
		$$ = TypeSpecifier::DOUBLE;
	}
	;

init_declarator
	: declarator { $$ = new InitDeclarator(NodePtr($1), nullptr); }
	| declarator '=' initializer { $$ = new InitDeclarator(NodePtr($1), NodePtr($3)); }
	;

initializer
	: expression

declarator
	: direct_declarator { $$ = new Declarator(NodePtr($1), 0); }
	| pointer direct_declarator { $$ = new Declarator(NodePtr($2), 1); }
	;

direct_declarator
	: IDENTIFIER {
		$$ = new Identifier(std::move(*$1));
		delete $1;
	}
	| direct_declarator '(' ')' {
		$$ = new DirectDeclarator(NodePtr($1));
	}
	| direct_declarator '(' parameter_list ')' {
		$$ = new DirectDeclarator(NodePtr($1), NodePtr($3));
	}
	| direct_declarator '[' INT_CONSTANT ']' {
		$$ = new DirectDeclarator(NodePtr($1), nullptr, $3);
	}
	;
pointer
	: '*' {  }
	| '*' pointer {  }
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

parameter_list
	: parameter_declaration { $$ = new NodeList(NodePtr($1)); }
	//fix this
	| parameter_list ',' parameter_declaration { $1->PushBack(NodePtr($3)); $$=$1; }
	;

parameter_declaration
	: declaration_specifiers declarator { $$ = new Parameter($1, NodePtr($2)); }
	;

statement
	: jump_statement { $$ = $1; }
    | declaration { $$ = $1; }
	| expression_statement { $$ = $1; }
	| compound_statement { $$ = new CompoundStatement(NodePtr($1)); }
	| selection_statement { $$ = $1; }
	| iteration_statement { $$ = $1; }
	;

compound_statement
	: '{' statement_list '}' { $$ = $2; }
	| '{' '}' { $$ = new NodeList(nullptr); }
	;

statement_list
	: statement { $$ = new NodeList(NodePtr($1)); }
	| statement_list statement { $1->PushBack(NodePtr($2)); $$=$1; }
	;

jump_statement
	: RETURN ';' {
		$$ = new ReturnStatement(nullptr);
	}
	| RETURN expression ';' {
		$$ = new ReturnStatement(NodePtr($2));
	}
	;

primary_expression
	: INT_CONSTANT {
		$$ = new IntConstant($1);
	}
    | IDENTIFIER { $$ = new Identifier(std::move(*$1)); delete $1; }
	| '(' expression ')' { $$ = $2; }
	| FLOAT_CONSTANT { $$ = new FloatConstant($1); }
	;

postfix_expression
	: primary_expression {
        if ($1->GetIdentifier() != ""){
            $$ = new VariableCall(std::move($1->GetIdentifier()) , nullptr);
        } else {
            $$ = $1;
        } }
    | postfix_expression '[' expression ']' { $$ = new VariableCall(std::move($1->GetIdentifier()), NodePtr($3)); }
	| postfix_expression '(' ')' { $$ = new FunctionCall(NodePtr($1), nullptr); }
	| postfix_expression '(' argument_expression_list ')' { $$ = new FunctionCall(NodePtr($1), NodePtr($3)); }
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP {
        if ($1->GetIdentifier() != ""){
            $$ = new VariablePostInc (std::move($1->GetIdentifier()));
        } else {
            $$ = $1;
        }
        }
	| postfix_expression DEC_OP {
        if ($1->GetIdentifier() != ""){
            $$ = new VariablePostDec (std::move($1->GetIdentifier()));
        } else {
            $$ = $1;
        }
        }
	;

argument_expression_list
	: assignment_expression { $$ = new ArgumentExpressionList(NodePtr($1)); }
	| argument_expression_list ',' assignment_expression { $1->PushBack(NodePtr($3)); $$=$1; }
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| '-' postfix_expression {   $$ = new Negation(NodePtr($2)); }
	| '&' unary_expression { $$ = new AddressOfExpr(NodePtr($2)); }
	| '*' unary_expression { $$ = new DereferenceExpr(NodePtr($2)); }
	| '~' unary_expression
	| '!' unary_expression
	| SIZEOF unary_expression
	;

cast_expression
	: unary_expression { $$ = $1; }
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression '*' cast_expression { $$ = new MulExpr(NodePtr($1), NodePtr($3)); }
	| multiplicative_expression '/' cast_expression { $$ = new DivExpr(NodePtr($1), NodePtr($3)); }
	| multiplicative_expression '%' cast_expression { $$ = new ModExpr(NodePtr($1), NodePtr($3)); }
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression { $$ = new AddExpr(NodePtr($1), NodePtr($3)); }
	| additive_expression '-' multiplicative_expression { $$ = new SubExpr(NodePtr($1), NodePtr($3)); }
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression { $$ = new LeftShiftExpr(NodePtr($1), NodePtr($3)); }
	| shift_expression RIGHT_OP additive_expression { $$ = new RightShiftExpr(NodePtr($1), NodePtr($3)); }
	;


relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression { $$ = new LessThanExpr(NodePtr($1), NodePtr($3)); }
	| relational_expression '>' shift_expression { $$ = new GreaterThanExpr(NodePtr($1), NodePtr($3)); }
	| relational_expression LE_OP shift_expression { $$ = new LessThanEqualExpr(NodePtr($1), NodePtr($3)); }
	| relational_expression GE_OP shift_expression { $$ = new GreaterThanEqualExpr(NodePtr($1), NodePtr($3)); }
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression { $$ = new EqualityExpr(NodePtr($1), NodePtr($3)); }
	| equality_expression NE_OP relational_expression { $$ = new InequalityExpr(NodePtr($1), NodePtr($3)); }
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression { $$ = new BitwiseAndExpr(NodePtr($1), NodePtr($3)); }
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression '^' and_expression { $$ = new BitwiseExclusiveOrExpr(NodePtr($1), NodePtr($3)); }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression { $$ = new BitwiseInlcusiveOrExpr(NodePtr($1), NodePtr($3)); }
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression { $$ = new LogicalAndExpr(NodePtr($1), NodePtr($3)); }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression { $$ = new LogicalOrExpr(NodePtr($1), NodePtr($3)); }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	//| IDENTIFIER assignment_operator assignment_expression {$$ = new VariableAssign(std::move(*$1), NodePtr($3), std::move(*$2)); delete $1; delete $2; }
    | unary_expression assignment_operator assignment_expression { $$ = new VariableAssign(NodePtr($1), NodePtr($3), std::move(*$2)); delete $2; }
	;

assignment_operator
    : '=' { $$ = new std::string("="); }
    | MUL_ASSIGN { $$ = new std::string("*="); }
    | DIV_ASSIGN { $$ = new std::string("/="); }
    | MOD_ASSIGN { $$ = new std::string("%="); }
    | ADD_ASSIGN { $$ = new std::string("+="); }
    | SUB_ASSIGN { $$ = new std::string("-="); }
    | LEFT_ASSIGN { $$ = new std::string("<<="); }
    | RIGHT_ASSIGN { $$ = new std::string(">>="); }
    | AND_ASSIGN { $$ = new std::string("&="); }
    | XOR_ASSIGN { $$ = new std::string("^="); }
    | OR_ASSIGN { $$ = new std::string("|="); }
    ;

expression
	: assignment_expression { $$ = $1; }
	;

expression_statement
	: expression ';' { $$ = $1; }
	;

selection_statement
	: IF '(' expression ')' statement { $$ = new IfStatement(NodePtr($3), NodePtr($5), nullptr ); }
	| IF '(' expression ')' statement ELSE statement { $$ = new IfStatement(NodePtr($3), NodePtr($5), NodePtr($7)); }
	| SWITCH '(' expression ')' statement {  }
	;
// TODO Implement Switch statements
/*
switch_case_list
	: switch_case { $$ = new NodeList(NodePtr($1)); }
	| switch_case_list switch_case { $1->PushBack(NodePtr($2)); $$=$1; }
	;

switch_case
	: CASE constant_expression ':' statement { $$ = new SwitchCase(NodePtr($2), NodePtr($4)); }
	;

default_case
    : DEFAULT ':' statement { $$ = new SwitchCase(nullptr, NodePtr($3)); }
    ;
*/

iteration_statement
	: WHILE '(' expression ')' statement { $$ = new WhileStatement(NodePtr($3), NodePtr($5)); }
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement { $$ = new ForStatement(nullptr, NodePtr($3), NodePtr($4), NodePtr($6)); }
	| FOR '(' expression_statement expression_statement expression ')' statement { $$ = new ForStatement(NodePtr($3), NodePtr($4), NodePtr($5), NodePtr($7)); }
	| FOR '(' declaration expression_statement expression_statement ')' statement { $$ = new ForInitStatement(NodePtr($3), NodePtr($4), NodePtr($5), NodePtr($7)); }
	;

%%

NodeList* g_root;

NodePtr ParseAST(std::string file_name)
{
  yyin = fopen(file_name.c_str(), "r");
  if(yyin == NULL){
    std::cerr << "Couldn't open input file: " << file_name << std::endl;
    exit(1);
  }
  g_root = nullptr;
  yyparse();
  fclose(yyin);
  yylex_destroy();
  return NodePtr(g_root);
}
