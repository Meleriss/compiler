#ifndef CODEGEN_H
#define CODEGEN_H

#include "AST.h"
#include "hashtable.h"

FILE *asmb;

void code_gen(struct AST *root);
void treversal(struct AST *node, struct idTable *table);
char* rightPart(struct AST *node, struct idTable *table);

void mov(char *str1, char *str2);

int getSizeNumber(int num);

#endif