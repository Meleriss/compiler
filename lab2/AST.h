#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ListTokens.h"
#include "ListChild.h"

int countNode;

typedef struct AST {
    ListTokens* Token;
    ListChild* ListChildren;
    int idNode;
} AST;

AST* init_node_ast(ListTokens* Token);
void add_child(AST* Node, AST* parent);
#endif