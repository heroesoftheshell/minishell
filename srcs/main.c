/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:22:47 by hekang            #+#    #+#             */
/*   Updated: 2021/07/27 14:37:53 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define STDIN_PIPE 0x1
#define STDOUT_PIPE 0x2

void		exec_command(char *command, int pipefd[2], int flags)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid > 0)
		return ;
	else if (cpid < 0)
		perror("fork");
	if (flags & STDIN_PIPE)
		if (dup2(pipefd[0], STDIN_PIPE) < 0)
			perror("dup2");
	if (flags & STDOUT_PIPE)
		if (dup2(pipefd[1], STDOUT_PIPE) < 0)
			perror("dup2");
	close(pipefd[0]);
	close(pipefd[1]);

	char *const argv[] = {command, NULL};
	char *const envp[] = {NULL};
	printf("%s \n\n", command);
	execve(command, argv, envp);
	perror("execv");
}

static void catch_function(int signo) {
    (void)signo;
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	rl_redisplay();
}

int			main(void)
{
	char	*input;
	// char	**line;
	// int		cnt;
	// int		pipefd1[2];
	// int		pipefd2[2];
	pid_t	pid;

	rl_bind_key('\t', rl_complete);
	// printf("PATH : %s", get_env_path());
	signal(SIGINT, catch_function);
	signal(SIGQUIT, catch_function);
	while (1)
	{
        input = readline("\033[1;4;34;47mHOS >\033[0m ");
		if (input == NULL)
		{
			rl_replace_line("", 0);
			// rl_redisplay();	
			printf("exit\n");
			return (0);
		}
		// if (input != NULL)
		// {
		else
		{
			rl_on_new_line();
			pid = fork();
			waitpid(0, 0, 0);
			if (pid == 0)
				run_cmd(input);

		// }
	// 	line = ft_split(input, '|');
	// 	cnt = 0;
	// 	pipe(pipefd1);
	// 	pipe(pipefd2);
	// 	// while (++cnt)
	// 	// {
	// 		exec_command("/bin/ls", pipefd1, STDOUT_PIPE);
	// 		close(pipefd1[1]);
	// 		exec_command("/bin/echo", pipefd2, STDIN_PIPE);
	// 		close(pipefd2[0]);
	// 		int temp_pipefd[] = {pipefd1[0], pipefd2[1]};
    //     	exec_command("/usr/bin/wc", temp_pipefd, STDIN_PIPE | STDOUT_PIPE);

    //     	close(pipefd1[0]);
    //     	close(pipefd2[1]);

    //     	int wstatus;
    //     	while (wait(&wstatus) > 0)
	// 			printf("1\n");
	// 		return 0;
	// 	// }


	// 		// if (pid == 0) // child
	// 		// {
	// 		// 	// pipefd[2] = get_fd(line); //stdin stdout 관리
	// 		// 	// execve() 명령어 실행
	// 		// }
		add_history(input);
		free(input);
		}

	}
	return 0;
}