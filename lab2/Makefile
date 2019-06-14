all:
	gcc -Wall -g main.c lexer.c ListTokens.c parser.c AST.c ListChild.c hashtable.c semantics.c CodeGen.c -o main

.PHONY: asm
asm:
	nasm -felf64 main.asm -o main.o	
	gcc -no-pie main.o -o main

.PHONY: run
run:
	./main t.txt

.PHONY: check
check:
	valgrind ./main t.txt