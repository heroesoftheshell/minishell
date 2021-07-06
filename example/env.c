#include <stdlib.h>
#include <stdio.h>
extern char **environ;

int main() {
  char **s = environ;
  setenv("NAMAAAAA", "1", 1);
  s = environ;
  unsetenv("LOGNAME11");
  char *path = getenv("PATH");

  s = environ;
  for (; *s; s++) {
   printf("%s\n", *s);
    // printf("declare -x %s\n", *s);
  }	
  s = environ;

  printf("\n\n%s\n", s[3]);
  printf("\n\n%s\n", path);
  return 0;
}
