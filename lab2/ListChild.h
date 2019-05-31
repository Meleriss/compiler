#ifndef LISTCHILD_H
#define LISTCHILD_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "AST.h"

typedef struct ListChild {
    AST *Node;
    struct ListChild *next;
} ListChild;

ListChild *chinit();
ListChild *addChild(ListChild *List, AST *Node);

// void ListPrint(ListTokens *head);

#endif
