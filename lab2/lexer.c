#include <stdio.h>
#include <string.h>
#include "ListTokens.h"

int main(int argc, char const *argv[]) {
  char buf[100];
  if (argc > 1) {
    FILE *file;

    file = fopen (argv[1], "r");

    if (file == NULL) {
      printf("error\n");
      return -1;
    }

    ListTokens *List = init();
    ListTokens *head = List;

    char sym;
    int i = 0;
    int row = 1, column = 1;

    while ((sym = fgetc(file)) != EOF) {
      //литералы
      if (sym == '"') {
        buf[i] = sym;
        i++;
        column++;

        while ((sym = fgetc(file)) != '"'){
          buf[i] = sym;
          i++;
          column++;
        }

        buf[i] = sym;
        i++;
        column++;
        buf[i] = '\0';

        List = addlexeme(List, buf, row, column-i);

        i = 0;
        continue;
      }
      //игнор пробелов
      else if (sym == ' ') {
        if (i == 0) {
          column++;
          continue;
        }

        buf[i] = '\0';
        //игнор комментов
        if (strcmp(buf, "REM") == 0) {
          while ((sym = fgetc(file)) != '\n')
            continue;
          //memset (buf, '0', i+1);
          i = 0;
          row++;
          column = 1;
          continue;
        }

        List = addlexeme(List, buf, row, column-i);

        i = 0;
        column++;
        continue;
      }
      //новая строка
      else if (sym == '\n') {

        if (i == 0)
          continue;

        buf[i] = '\0';
        //игнор комментов
        if (strcmp(buf, "REM") == 0) {
          while ((sym = fgetc(file)) != '\n')
            continue;
          //memset (buf, '0', i+1);
          i = 0;
          continue;
        }

        List = addlexeme(List, buf, row, column-i);

        column = 1;
        row++;
        i = 0;
        continue;
      }
      //знаки в один символ
      else if (sym == ',' || sym == ';' || sym == '+' || sym == '-' ||
        sym == '*' || sym == '/' || sym == '\\' || sym == '^' ||
        sym == '=' || sym == '(' || sym == ')') {
        if (i != 0) {
          buf[i] = '\0';

          List = addlexeme(List, buf, row, column-i);

          i = 0;
        }

        buf[i] = sym;
        i++;
        column++;
        buf[i] = '\0';

        List = addlexeme(List, buf, row, column-i);

        i = 0;
        continue;
      }

      else if (sym == '>') {
        if (i != 0) {
          buf[i] = '\0';

          List = addlexeme(List, buf, row, column-i);

          i = 0;
        }

        buf[i] = sym;
        i++;
        column++;

        if ((sym = fgetc(file)) == '=') {
          buf[i] = sym;
          i++;
          column++;
          buf[i] = '\0';

          List = addlexeme(List, buf, row, column-i);

          i = 0;
          continue;
        } else {
          buf[i] = '\0';

          List = addlexeme(List, buf, row, column-i);

          i = 0;

          if (sym == ' ') {
            column++;
            continue;
          }
        }
      }

      else if (sym == '<') {
        if (i != 0) {
          buf[i] = '\0';

          List = addlexeme(List, buf, row, column-i);

          i = 0;
        }
        buf[i] = sym;
        i++;
        column++;

        sym = fgetc(file);

        if ((sym == '=') || (sym == '>')) {
          buf[i] = sym;
          i++;
          column++;
          buf[i] = '\0';

          List = addlexeme(List, buf, row, column-i);

          i = 0;
          continue;
        } else {
          buf[i] = '\0';

          List = addlexeme(List, buf, row, column-i);

          i = 0;

          if (sym == ' ') {
            column++;
            continue;
          }
        }
      }

      buf[i] = sym;
      i++;
      column++;
      // printf("%c", sym);
    }
    ListPrint(head);
    fclose (file);
  }

  // addlexeme(List, "sdffd", 1, 1);
  // addlexeme(List, "snjkl", 2, 6);
  // ListPrint(head);

  return 0;
}
