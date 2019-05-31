#include "lexer.h"
#include "parser.h"

int main(int argc, char const *argv[]) {

    ListTokens* Tokens = IdentifyTokens(argc, argv[1]);
    // ListPrint(Tokens);
    initParser(Tokens);
    return 0;
}