all:
	gcc -Wall -g main.c lexer.c ListTokens.c parser.c AST.c ListChild.c hashtable.c semantics.c -o main

.PHONY: run
run:
	./main t.txt

.PHONY: check
check:
	valgrind ./main t.txt