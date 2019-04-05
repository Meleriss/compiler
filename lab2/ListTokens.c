#include "ListTokens.h"

ListTokens *init() {
  ListTokens *ListToken;
  ListToken = (ListTokens*)malloc(sizeof(ListTokens));
  ListToken->row = -1;
  ListToken->next = NULL;
  return ListToken;
}

ListTokens *addlexeme(ListTokens *List, char *lexeme, int row, int column) {
  if (List->row == -1) {
    strcpy(List->lexeme, lexeme);
    List->row = row;
    List->column = column;
    return List;
  } else {
    ListTokens *List2;
    List2 = (ListTokens*)malloc(sizeof(ListTokens));
    List->next = List2;
    strcpy(List2->lexeme, lexeme);
    List2->row = row;
    List2->column = column;
    List2->next = NULL;
    return List2;
  }
  return NULL;
}

void ListPrint(ListTokens *head) {
  ListTokens *print;
  print = head;
  while (print != NULL) {
    printf("%s ", print->lexeme);
    printf("%d %d \n", print->row, print->column);
    print = print->next;
  }
}
