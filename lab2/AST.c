#include "AST.h"

int countNode = 1;

struct AST* initASTNode() {
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

void setToken(struct AST *node, ListTokens *token) {
	
}

void createTree(struct AST* Node) {
	FILE *graph;
	if ((graph = fopen("graph.gv", "w")) == NULL) {
		printf ("Cannot open file.\n");
		exit(1); 
	}
	fprintf(graph, "digraph {\n");
	createConnect(graph, Node);
	fprintf(graph, "}\n");
}

void createConnect(FILE *graph, struct AST* Node) {
	createBox(graph, Node);
	struct ListChild* child = Node->ListChildren;
	while (child != NULL) {
		fprintf(graph, "\t");
		toGvNode(graph, Node);
		fprintf(graph, " -> ");
		toGvNode(graph, child->Node);
		fprintf(graph, "\n");
		createConnect(graph, child->Node);
		child = child->next;
	}
}

void createBox(FILE *graph, struct AST* Node) {
	fprintf(graph, "\t\"node%d\" [label=%s]\n", Node->idNode, Node->Stroka);
}

void toGvNode(FILE *graph, struct AST* Node) {
	fprintf(graph, "\"node%d\"", Node->idNode);
}