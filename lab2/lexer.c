#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char buf[100];
  if (argc > 1) {
    FILE *file;

    file = fopen (argv[1], "r");

    if (file == NULL) {
      printf("error\n");
      return -1;
    }

    char sym;
    int i = 0;

    while ((sym = fgetc(file)) != EOF) {
      //литералы
      if (sym == '"') {
        buf[i] = sym;
        i++;

        while ((sym = fgetc(file)) != '"'){
          buf[i] = sym;
          i++;
        }

        buf[i] = sym;
        i++;
        buf[i] = '\0';

        printf("%s\n", buf);

        i = 0;
        continue;
      }
      //игнор пробелов
      else if (sym == ' ' || sym == '\n') {
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

        printf("%s\n", buf);

        i = 0;
        continue;
      }
      //знаки в один символ
      else if (sym == ',' || sym == ';' || sym == '+' || sym == '-' ||
        sym == '*' || sym == '/' || sym == '\\' || sym == '^' ||
        sym == '=' || sym == '(' || sym == ')') {
        if (i != 0) {
          buf[i] = '\0';

          printf("%s\n", buf);

          i = 0;
        }

        buf[i] = sym;
        buf[i+1] = '\0';

        printf("%s\n", buf);

        i = 0;
        continue;
      }

      else if (sym == '>') {
        if (i != 0) {
          buf[i] = '\0';

          printf("%s\n", buf);

          i = 0;
        }

        buf[i] = sym;
        i++;

        if ((sym = fgetc(file)) == '=') {
          buf[i] = sym;
          i++;
          buf[i] = '\0';

          printf("%s\n", buf);

          i = 0;
          continue;
        } else {
          buf[i] = '\0';

          printf("%s\n", buf);

          i = 0;

          if (sym == ' ')
            continue;
        }
      }

      else if (sym == '<') {
        if (i != 0) {
          buf[i] = '\0';

          printf("%s\n", buf);

          i = 0;
        }
        buf[i] = sym;
        i++;

        sym = fgetc(file);

        if ((sym == '=') || (sym == '>')) {
          buf[i] = sym;
          i++;
          buf[i] = '\0';

          printf("%s\n", buf);

          i = 0;
          continue;
        } else {
          buf[i] = '\0';

          printf("%s\n", buf);

          i = 0;

          if (sym == ' ')
            continue;
        }
      }

      buf[i] = sym;
      i++;
      // printf("%c", sym);
    }

    fclose (file);
  }

  return 0;
}
