/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:22:47 by hekang            #+#    #+#             */
/*   Updated: 2021/08/24 16:22:28 by hekang           ###   ########.fr       */
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
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void do_nothing(int signo)
{
	(void)signo;
}

int			is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "echo") ||
		!ft_strcmp(cmd, "exit") ||
		!ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "export") ||
		!ft_strcmp(cmd, "unset") ||
		!ft_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	char	*input;
	// char	**line;
	// int		cnt;
	int		pipefd[2];
	int		pipefd_backup[2];
	// pid_t	pid;
	char	**cmd_chunks;
	char	**parsed_chunk_data;
	int		chunk_idx;
	int		pid;
	int		exit_status;
	int		is_pipe;

	(void)argc;
	(void)argv;
	init_env(envp);
	pipefd_backup[0] = dup(STDIN_FILENO);
	pipefd_backup[1] = dup(STDOUT_FILENO);
	rl_getc_function = custom_rl_getc_fuction;
	rl_catch_signals = 0;
	
	rl_bind_key('\t', rl_complete);
	signal(SIGINT, catch_function);
	signal(SIGQUIT, do_nothing);

	is_pipe = 0;
	while (1)
	{
        input = readline("\033[1;4;34;47mHOS >\033[0m ");
		pipefd[0] = dup(pipefd_backup[0]);
		pipefd[1] = dup(pipefd_backup[1]);
		if (input == 0)
			break ;
		else
		{
			rl_on_new_line();
			cmd_chunks = line_parse((const char *)input);
			chunk_idx = -1;
			while (cmd_chunks && cmd_chunks[++chunk_idx] != NULL)
			{
				parsed_chunk_data = cmd_chunk_parse((const char *)cmd_chunks[chunk_idx]);
				if (parsed_chunk_data == NULL)
				{
					// perror("hosh: ");
					delete_split_strs(cmd_chunks);
					break ;
				}
				if (cmd_chunks[1] != NULL || is_pipe)
				{
					is_pipe = 1;
					dup2(pipefd[0], STDIN_FILENO);
					close(pipefd[0]);
					pipe(pipefd);
					signal(SIGINT, catch_function);
					signal(SIGQUIT, do_nothing);
					pid = fork();
					// ft_putnbr_fd(pid, 2);
					// ft_putchar_fd('\n', 2);
					// ft_putstr_fd(cmd_chunks[chunk_idx], 2);
					// ft_putchar_fd('\n', 2);

					if (pid == 0) // child
					{
						dup2(pipefd[1], STDOUT_FILENO);
						close(pipefd[1]); // fd 교체
						run_cmd(parsed_chunk_data);
						exit(all()->end_code);
					}
					if (pid > 0)
					{
						waitpid(pid, &exit_status, 0);
						if (WTERMSIG(exit_status) == SIGINT || WTERMSIG(exit_status) == SIGQUIT)
							all()->end_code = WEXITSTATUS(exit_status);
						close(pipefd[1]);
						is_pipe = 0;
					}
				}
				else
				{
					if (is_builtin(parsed_chunk_data[0]))
						run_cmd(parsed_chunk_data);
					else
					{
						pid = fork();
						if (pid == 0)
							run_cmd(parsed_chunk_data);
						else
						{
							waitpid(pid, &exit_status, WCONTINUED);
							if (WIFEXITED(exit_status))
								all()->end_code = WEXITSTATUS(exit_status);
						}
					}
				}

				// TODO: process excute
				// ex 1) exec_func(const char ** parsed_chunk_data, char *envp);
				// ex 2) exec_func(const char *cmd, const char *arg, const char *redir, char *envp)
				delete_split_strs(parsed_chunk_data);
			}
			delete_split_strs(cmd_chunks);
			// pid = fork();
			// waitpid(0, 0, 0);
			// if (pid == 0)
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