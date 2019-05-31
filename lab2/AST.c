#include "AST.h"

AST* init_node_ast(ListTokens* Token) {
    AST* ast = calloc(1, sizeof(AST*));
    ast->Token = Token;
    ast->ListChildren = NULL;
    ast->idNode = countNode;
    countNode++;

    return ast;
}

void add_child(AST* Node, AST* parent) {
    ListChild* child = calloc(1, sizeof(ListChild*));
    child->next = NULL;
    ListChild* pnode = parent->ListChildren;  
    if (pnode == NULL) {
        pnode = child;
    } else {
        while (pnode->next != NULL)
        {
            pnode = pnode->next;
        }
        pnode->next = child;
    }
}