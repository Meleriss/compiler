#ifndef CODEGEN_H
#define CODEGEN_H

#include "AST.h"
#include "hashtable.h"

FILE *asmb;

void code_gen(struct AST *root);

#endif