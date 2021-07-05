#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int my_startup(void);
int my_bind_cr(int, int);
int my_bind_eoq(int, int);
char *my_readline(void);

int my_eoq; 

int
main(int argc, char *argv[])
{

  if (isatty(STDIN_FILENO)) {
    rl_readline_name = "my";
    rl_startup_hook = my_startup;
    my_readline();
  }
}

int
my_startup(void) 
{
  my_eoq = 0;
  rl_bind_key('\n', my_bind_cr);
  rl_bind_key('\r', my_bind_cr);
  rl_bind_key(';', my_bind_eoq);
}

int
my_bind_cr(int count, int key) {
//   if (my_eoq == 1) {
//     rl_done = 1;
//   }
  printf("\n");
}

int
my_bind_eoq(int count, int key) {
  my_eoq = 1;

  printf(";");
}

char * 
my_readline(void)
{
  char *line;

  if ((line = readline("")) == NULL) {
    return NULL;
  }

  printf("LINE : %s\n", line);
}