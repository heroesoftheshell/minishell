/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:04:23 by hekang            #+#    #+#             */
/*   Updated: 2021/07/05 17:22:01 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gcc readline.c -lreadline

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

static void		connect_pipe(int pipefd[2], int io)
{
	dup2(pipefd[io], io);
	close(pipefd[0]);
	close(pipefd[1]);
}

int	rl_printf(int a, int b)
{
	printf("abcd\n");
	return (0);
}

int
quote_detector(char *line, int index)
{
    return (
        index > 0 &&
        line[index - 1] == '\\' &&
        !quote_detector(line, index - 1)
    );
}

int ft_readline()
{
    char* input;
	char* line;
	int		cnt;
	int		pipefd[2];

    // Configure readline to auto-complete paths when the tab key is hit.
    rl_bind_key('\t', rl_complete);
	rl_completer_quote_characters = "'\"|";
    while(1) {
        // Create prompt string from user name and current working directory.
        // snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", getenv("USER"), getcwd(NULL, 1024));

        // Display promp and read input (n.b. input must be freed after use)...
        // input = readline("minishell% ");
        // input = readline(shell_prompt);
        input = readline("\033[1;4;34;47mHOS >\033[0m ");
		// line = split(input, '\n');

		strtok(input, "\n");
        printf("%s\n", input);
		printf("%d\n",rl_on_new_line());
        // line = ft_split(input, '|');
		cnt = 0;
		pipe(pipefd);
		printf("\n%d, %d\n", pipefd[0], pipefd[1]);
		// while (line[cnt])
		// {
		// 	ft_execve(line[cnt], STDIN_FILENO, STDOUT_FILENO);

		// }

        // Check for EOF.
        if (!input)
            break;

        // Add input to history.
        add_history(input);

        // Do stuff...

        // Free input.
        free(input);
    }
}