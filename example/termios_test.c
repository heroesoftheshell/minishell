#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char c;

	while (read(0, &c, sizeof(c)) > 0)
	{
		printf("input: %c\n", c);
	}
}
