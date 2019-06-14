#include "CodeGen.h"

void code_gen(struct AST *root)
{
	if ((asmb = fopen("main.asm", "w")) == NULL) {
		printf ("Cannot open file.\n");
		exit(1); 
	}

	fprintf(asmb, "section .text\n");
	fprintf(asmb, "\tglobal\tmain\n");

	treversal(root, NULL);

	fclose(asmb);
}

void treversal(struct AST *node, struct idTable *table)
{
	struct idTable *currTab = table;
	if (node->table != NULL)
		currTab = node->table;
	if (strcmp(node->Stroka, "assign") == 0) {
		struct ListChild *child1 = node->ListChildren;
		struct ListChild *child2 = child1->next;

		char *name = child1->Node->Token->lexeme;
		struct listnode *elemOfTab = findInAllTable(currTab, name);
		int offset = elemOfTab->offset;

		int sizeNumb = getSizeNumber(offset);
		char* str1 = (char*) calloc(7 + sizeNumb, sizeof(char));
		sprintf(str1, "[rbp-%d]", offset);

		char* str2 = rightPart(node, currTab);

		fprintf(asmb, "\tmov\t\t%s, %s\n", str1, "testReg");

		free(str1);
	}

	struct ListChild* Children = node->ListChildren;
	while (Children != NULL) {
		treversal(Children->Node, currTab);
		Children = Children->next;
	}
}

char* rightPart(struct AST *node, struct idTable *table)
{
	if (strcmp(node->Stroka, "") == 0) {

	}
}

int getSizeNumber(int num)
{
	int size = 1;
	int mult = 10;
	while (mult < num) {
		mult *= 10;
		size++;
	}
	return size;
}