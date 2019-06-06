#include "parser.h"

struct AST* initParser(ListTokens* Tokens) {
	parser = (Parser*) calloc(1, sizeof(Parser));
	parser->Tokens = Tokens;
	parser->count = 0;
	parser->lookahead = Tokens;
	parser->root = NULL;

	S(parser);
	printf("End parsing\n");
	return parser->root;
}

void S(Parser* parser) {
	struct AST* StartNode = initASTNode();
	setStroka(StartNode, "start");
	parser->root = StartNode;
	StList(StartNode);
	match("end");
}

void StList(struct AST* StartNode) {
	if (strcmp(parser->lookahead->token, "input") == 0) {
		struct AST* InputNode = initASTNode();
		setStroka(InputNode, "input");
		add_child(InputNode, StartNode);

		input1(InputNode);
		StList(StartNode);
	} else if (strcmp(parser->lookahead->token, "print") == 0) {
		struct AST* printNode = initASTNode();
		setStroka(printNode, "print");
		add_child(printNode, StartNode);
		
		print1(printNode);
		StList(StartNode);
	} else if (strcmp(parser->lookahead->token, "dim") == 0) {
		initi();
		StList(StartNode);
	} else if (strcmp(parser->lookahead->token, "id") == 0) {
		callOrAriph();
		StList(StartNode);
	} else if (strcmp(parser->lookahead->token, "if") == 0) {
		vetvlenie(StartNode);
		StList(StartNode);
	} else if (strcmp(parser->lookahead->token, "do") == 0) {
		tsicl(StartNode);
		StList(StartNode);
	} else if (strcmp(parser->lookahead->token, "function") == 0) {
		func(StartNode);
		StList(StartNode);
	}
}

void input1(struct AST* inputNode) {
	match("input");
	input2(inputNode);
}

void input2(struct AST* inputNode) {
	if (strcmp(parser->lookahead->token, "id") == 0) {
		commaid(inputNode);
	} else if (strcmp(parser->lookahead->token, "literal") == 0) {
		match("literal");
		input3();
	} else {
		printf("error: %d:%d: expecting id or literal, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}   
}

void input3() {
	if (strcmp(parser->lookahead->token, "comma") == 0) {
		match("comma");
		match("id");
	} else if (strcmp(parser->lookahead->token, "semi") == 0) {
		match("semi");
		semiid();
	} else {
		printf("error: %d:%d: expecting comma or semi, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void commaid(struct AST* node) {
	headcommaid(node);
	tailcommaid();
}

void headcommaid(struct AST* node) {
	struct AST* idNode = initASTNode();
	setStroka(idNode, "id");
	setToken(idNode, getLookahead());
	
	add_child(idNode, node);
	match("id");
}

void tailcommaid() {
	if (strcmp(parser->lookahead->token, "comma") == 0) {
		match("comma");
		match("id");
		tailcommaid();
	}
}

void semiid() {
	headsemiid();
	tailsemiid();
}

void headsemiid() {
	match("id");
}

void tailsemiid() {
	if (strcmp(parser->lookahead->token, "semi") == 0) {
		match("semi");
		match("id");
		tailsemiid();
	}
}

void print1(struct AST *node) {
	match("print");
	print2(node);
}

void print2(struct AST *node) {
	if (strcmp(parser->lookahead->token, "id") == 0) {
		commaid(node);
	} else if (strcmp(parser->lookahead->token, "literal") == 0) {
		match("literal");
		match("comma");
		commaid(node);
	} else {
		printf("error: %d:%d: expecting id or literal, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}  
}

void initi() {
	match("dim");
	match("id");
	varormas();
}

void varormas() {
	if ((strcmp(parser->lookahead->token, "comma") == 0) || 
		(strcmp(parser->lookahead->token, "as") == 0)) {
		tailcommaid();
		match("as");
		type();
	} else if (strcmp(parser->lookahead->token, "l_paren") == 0) {
		match("l_paren");
		idornum();
		match("r_paren");
		match("as");
		type();
	} else {
		printf("error: %d:%d: expecting l_paren or comma or as, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void idornum() {
	if (strcmp(parser->lookahead->token, "id") == 0) {
		match("id");
	} else if (strcmp(parser->lookahead->token, "numeric") == 0) {
		match("numeric");
	} else {
		printf("error: %d:%d: expecting id or numeric, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void type() {
	if (strcmp(parser->lookahead->token, "integer") == 0) {
		match("integer");
	} else if (strcmp(parser->lookahead->token, "string") == 0) {
		match("string");
	} else {
		printf("error: %d:%d: expecting integer or string, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void callOrAriph() {
	match("id");
	cOar();
}

void cOar() {
	if (strcmp(parser->lookahead->token, "l_paren") == 0) {
		call_method();
	} else if (strcmp(parser->lookahead->token, "equal") == 0) {
		match("equal");
		term();
	}  else {
		printf("error: %d:%d: expecting l_paren or equal, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void term() {
	add_prior1();
}

void add_prior1() {
	mult_prior1();
	add_prior2();
}

void add_prior2() {
	if ((strcmp(parser->lookahead->token, "plus") == 0) || 
		(strcmp(parser->lookahead->token, "minus") == 0)) {
			add_prior_oper();
			mult_prior1();
			add_prior2();
	}
}

void mult_prior1() {
	group();
	mult_prior2();
}

void mult_prior2() {
	if ((strcmp(parser->lookahead->token, "multiply") == 0) || 
		(strcmp(parser->lookahead->token, "divide") == 0)) {
			mult_prior_oper();
			group();
			mult_prior2();
	}
}

void group() {
	if (strcmp(parser->lookahead->token, "l_paren") == 0) {
		match ("l_paren");
		term();
		match ("r_paren");
	} else if ((strcmp(parser->lookahead->token, "id") == 0) ||
	(strcmp(parser->lookahead->token, "plus") == 0) ||
	(strcmp(parser->lookahead->token, "minus") == 0) ||
	(strcmp(parser->lookahead->token, "numeric") == 0)) {
		id_or_sign_number();
	}  else {
		printf("error: %d:%d: expecting l_paren or id or plus or minus or numeric, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void mult_prior_oper() {
	if (strcmp(parser->lookahead->token, "multiply") == 0) {
		match ("multiply");
	} else if (strcmp(parser->lookahead->token, "divide") == 0) {
		match("divide");
	}  else {
		printf("error: %d:%d: expecting multiply or divide, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void add_prior_oper() {
	if (strcmp(parser->lookahead->token, "plus") == 0) {
		match ("plus");
	} else if (strcmp(parser->lookahead->token, "minus") == 0) {
		match("minus");
	}  else {
		printf("error: %d:%d: expecting plus or minus, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void id_or_sign_number() {
	if (strcmp(parser->lookahead->token, "id") == 0) {
		match ("id");
		method_or_array();
	} else if ((strcmp(parser->lookahead->token, "plus") == 0) ||
	(strcmp(parser->lookahead->token, "minus") == 0) ||
	(strcmp(parser->lookahead->token, "numeric") == 0)) {
		sign_number();
	}  else {
		printf("error: %d:%d: expecting id or plus or minus or numeric, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void method_or_array() {
	if (strcmp(parser->lookahead->token, "l_paren") == 0) {
		match("l_paren");
		pass_arg();
		match("r_paren");
	}
}

void call_method() {
	if (strcmp(parser->lookahead->token, "l_paren") == 0) {
		match("l_paren");
		pass_arg();
		match("r_paren");
	} else {
		printf("error: %d:%d: expecting l_paren, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void pass_arg() {
	if ((strcmp(parser->lookahead->token, "l_paren") == 0) ||
	(strcmp(parser->lookahead->token, "id") == 0) ||
	(strcmp(parser->lookahead->token, "plus") == 0) ||
	(strcmp(parser->lookahead->token, "minus") == 0) ||
	(strcmp(parser->lookahead->token, "numeric") == 0)) {
		term();
		tail_pass_arg();
	}
}

void tail_pass_arg() {
	if (strcmp(parser->lookahead->token, "comma") == 0) {
		match("comma");
		term();
		tail_pass_arg();
	}
}

void sign_number() {
	if ((strcmp(parser->lookahead->token, "plus") == 0) ||
	(strcmp(parser->lookahead->token, "minus") == 0) ||
	(strcmp(parser->lookahead->token, "numeric") == 0)) {
		sign();
		match("numeric");
	} else {
		printf("error: %d:%d: expecting plus or minus or numeric, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void sign() {
	if (strcmp(parser->lookahead->token, "plus") == 0) {
		match("plus");
	} else if (strcmp(parser->lookahead->token, "minus") == 0) 
		match("minus");
}

void vetvlenie(struct AST* StartNode) {
	match("if");
	expression();
	match("then");
	StList(StartNode);
	match("else");
	StList(StartNode);
	match("end");
	match("if");
}

void expression() {
	if ((strcmp(parser->lookahead->token, "l_paren") == 0) ||
	(strcmp(parser->lookahead->token, "id") == 0) ||
	(strcmp(parser->lookahead->token, "plus") == 0) ||
	(strcmp(parser->lookahead->token, "minus") == 0) ||
	(strcmp(parser->lookahead->token, "numeric") == 0)) {
		first_prior_expr1();
	} else {
		printf("error: %d:%d: expecting l_paren or id or plus or minus or numeric, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void first_prior_expr1() {
	group_expr();
	first_prior_expr2();
}

void first_prior_expr2() {
	if ((strcmp(parser->lookahead->token, "equal") == 0) ||
	(strcmp(parser->lookahead->token, "not_equal") == 0) ||
	(strcmp(parser->lookahead->token, "less") == 0) ||
	(strcmp(parser->lookahead->token, "less_or_equal") == 0) ||
	(strcmp(parser->lookahead->token, "more") == 0) ||
	(strcmp(parser->lookahead->token, "more_or_equal") == 0)) {
		condition();
		group_expr();
		first_prior_expr2();
	}
}

void group_expr () {
	term();
}

void condition() {
	if (strcmp(parser->lookahead->token, "equal") == 0) {
		match("equal");
	} else if (strcmp(parser->lookahead->token, "not_equal") == 0) {
		match("not_equal");
	} else if (strcmp(parser->lookahead->token, "less") == 0) {
		match("less");
	} else if (strcmp(parser->lookahead->token, "less_or_equal") == 0) {
		match("less_or_equal");
	} else if (strcmp(parser->lookahead->token, "more") == 0) {
		match("more");
	} else if (strcmp(parser->lookahead->token, "more_or_equal") == 0) {
		match("more_or_equal");
	} else { 
		printf("error: %d:%d: expecting plus or sign condition, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void tsicl(struct AST* StartNode) {
	if (strcmp(parser->lookahead->token, "do") == 0) {
		match("do");
		tsicl1(StartNode);
	}
}

void tsicl1(struct AST* StartNode) {
	if (strcmp(parser->lookahead->token, "while") == 0) {
		match("while");
		expression();
		StList(StartNode);
		match("loop");
	} else if (strcmp(parser->lookahead->token, "until") == 0) {
		 match("while");
		expression();
		StList(StartNode);
		match("loop");
	} else {
		printf("error: %d:%d: expecting while or until, find %s\n", 
		parser->lookahead->row, parser->lookahead->column, parser->lookahead->token);
		exit(1);
	}
}

void func(struct AST* StartNode) {
	match("function");
	match("id");
	match("l_paren");
	commaid(StartNode);
	match("r_paren");
	StList(StartNode);
	match("end");
	match("function");
}

void match(char* x) {
	if(strcmp(parser->lookahead->token, x) == 0) {
		consume();
	} else {
		printErrorMessage(parser->lookahead->row, parser->lookahead->column, x);
		exit(1);
	}
}

void consume() {
	parser->lookahead = nextToken(); 
}

ListTokens* nextToken() {
	parser->count++;
	return parser->lookahead->next;
}

ListTokens* getLookahead()
{
	return parser->lookahead;
}

void printErrorMessage(int row, int column, char *x) {
	printf("%d:%d: error: expecting %s; find %s\n", row, column, x, parser->lookahead->token);
}