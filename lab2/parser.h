#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ListTokens.h"
#include "lexer.h"
#include "AST.h"

typedef struct Parser {
    ListTokens* Tokens;
    ListTokens* lookahead;
    int count;
    struct AST *root;
} Parser;

Parser* parser;

struct AST* initParser(ListTokens* Tokens);
void S(Parser* parser);
void StList(struct AST* StartNode);
void input1(struct AST* inputNode);
void input2(struct AST* inputNode);
void input3();
void commaid(struct AST* inputNode);
void headcommaid(struct AST *node);
void tailcommaid();
void semiid();
void headsemiid();
void tailsemiid();
void print1(struct AST *node);
void print2(struct AST *node);
void initi();
void varormas();
void idornum();
void type();
void callOrAriph();
void cOar();
void term();
void add_prior1();
void add_prior2();
void mult_prior1();
void mult_prior2();
void group();
void mult_prior_oper();
void add_prior_oper();
void id_or_sign_number();
void method_or_array();
void call_method();
void pass_arg();
void tail_pass_arg();
void sign_number();
void sign();
void vetvlenie(struct AST* StartNode);
void expression();
void first_prior_expr1();
void first_prior_expr2();
void group_expr ();
void condition();
void tsicl(struct AST* StartNode);
void tsicl1(struct AST* StartNode);
void func(struct AST* StartNode);

void match(char* x);
void consume();
ListTokens* nextToken();
ListTokens* getLookahead();
void printErrorMessage(int row, int column, char *x);

#endif