#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ListTokens.h"
#include "ListChild.h"

struct AST {
    char *Stroka;
    ListTokens* Token;
    struct ListChild* ListChildren;
    int idNode;
    int type;
};

struct AST* initASTNode();

void add_child(struct AST* Node, struct AST* parent);

void setStroka(struct AST* node, char *str);
void setToken(struct AST* node, ListTokens *token);

void createTree(struct AST* Node);
void createConnect(FILE *graph, struct AST* Node);
void createBox(FILE *graph, struct AST* Node);
void toGvNode(FILE *graph, struct AST* Node);

#endif