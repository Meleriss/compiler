#include "AST.h"

int countNode = 1;

struct AST* init_node_ast() {
	struct AST* ast;
	ast = (struct AST*) calloc(1, sizeof(struct AST));
	ast->Stroka = NULL;
	ast->Token = NULL;
	ast->ListChildren = NULL;
	ast->idNode = countNode;
	countNode++;
	ast->type = 0;

	return ast;
}

void add_child(struct AST* Node, struct AST* parent) {
	struct ListChild* child;
	child = (struct ListChild*) calloc(1, sizeof(struct ListChild));
	child->next = NULL;
	child->Node = Node;
	struct ListChild* pnode = parent->ListChildren;  
	if (pnode == NULL) {
		parent->ListChildren = child;
	} else {
		while (pnode->next != NULL)
		{
			pnode = pnode->next;
		}
		pnode->next = child;
	}
}

void setStroka(struct AST *node, char* str)
{
	node->Stroka = (char*) calloc(strlen(str), sizeof(char*));
	strcpy(node->Stroka, str);
}