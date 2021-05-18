#include <stdlib.h>
#include <stdio.h>
extern char **environ;

int main() {
  char **s = environ;
  setenv("NAMAAAAA", "1", 1);
  s = environ;
  unsetenv("LOGNAME11");

  s = environ;
  for (; *s; s++) {
//    printf("%s\n", *s);
    printf("declare -x %s\n", *s);
  }	
  return 0;
}
