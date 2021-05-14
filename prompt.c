#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#define PROMPT_NAME "ghong-1.0$ "
#define PROMPT_SIZE 11
#define BUFFER_SIZE 1024

int	show_prompt(void)
{
	int		input_bytes;
	int		err_chk;
	char	buf[BUFFER_SIZE];

	err_chk = write(1, PROMPT_NAME, PROMPT_SIZE);
	if (err_chk < 0)
		return (err_chk);
	// FIXME : read() -> get_next_line()
	err_chk = read(0, buf, BUFFER_SIZE);
	if (err_chk < 0)
		return (err_chk);
	// FIXME : input str parse start and handle data
	printf("%s", buf);
	return (0);
}