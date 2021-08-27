/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:22:47 by hekang            #+#    #+#             */
/*   Updated: 2021/08/27 09:42:58 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define STDIN_PIPE 0x0
#define STDOUT_PIPE 0x1

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
	int		pipefd[2];
	int		pipefd_backup[2];
	char	**cmd_chunks;
	// char	**parsed_chunk_data;
	int		chunk_idx;
	int		pid;
	int		pid_list[BUFSIZ];
	int		exit_status;
	int		is_pipe;
	t_parse_data	*parsed_data;
	int		idx;

	(void)argc;
	(void)argv;
	init_env(envp);
	pipefd_backup[0] = dup(STDIN_FILENO);
	pipefd_backup[1] = dup(STDOUT_FILENO);
	rl_getc_function = custom_rl_getc_fuction;
	rl_catch_signals = 0;
	
	signal(SIGINT, catch_function);
	signal(SIGQUIT, do_nothing);
	idx = -1;
	is_pipe = 0;
	while (1)
	{
		pipefd[0] = dup(pipefd_backup[0]);
		pipefd[1] = dup(pipefd_backup[1]);
		dup2(pipefd_backup[1], 1);
		dup2(pipefd_backup[0], 0);
        input = readline("\033[1;4;34;47mHOS >\033[0m ");
		if (input == 0)
			break ;
		else
		{
			rl_on_new_line();
			cmd_chunks = line_parse((const char *)input);
			chunk_idx = -1;
			while (cmd_chunks && cmd_chunks[++chunk_idx] != NULL)
			{
				parsed_data = cmd_chunk_parse((const char *)cmd_chunks[chunk_idx]);
				if (parsed_data == NULL)
				{
					continue ;
				}
				printf("redirections : %s\n", parsed_data->redirections);
				if (parsed_data->redirections)
				{
					handle_redirection(parsed_data->redirections);
				}
				if (cmd_chunks[1] != NULL || is_pipe)
				{
					is_pipe = 1;
					pipe(pipefd);
					pid = fork();
					if (pid == 0) // child
					{
						dup2(pipefd[0], STDIN_FILENO);
						close(pipefd[0]);
						dup2(pipefd[1], STDOUT_FILENO);
						close(pipefd[1]); // fd 교체
						run_cmd(parsed_data->cmd);
						exit(all()->end_code);
					}
					if (pid > 0)
					{
						pid_list[++idx] = pid;
						close(pipefd[1]);
					}
				}
				else if (is_pipe)
				{
					pid = fork();
					// pipe(pipefd);
					if (pid == 0) // child
					{
						dup2(pipefd[0], STDIN_FILENO);
						dup2(pipefd_backup[1], STDOUT_FILENO);
						close(pipefd[0]);
						close(pipefd[1]);
						run_cmd(parsed_data->cmd);
						exit(all()->end_code);
					}
					if (pid > 0)
					{
						pid_list[++idx] = pid;
						close(pipefd[1]);
						idx = -1;
						while (pid_list[++idx])
						{
							waitpid(pid_list[idx], &exit_status, WCONTINUED);
							// ft_putnbr_fd(pid_list[idx], 2);
							if (WTERMSIG(exit_status) == SIGINT || WTERMSIG(exit_status) == SIGQUIT)
								all()->end_code = WEXITSTATUS(exit_status);
							pid_list[idx] = 0;
						}
					}
				}
				else
				{
					if (is_builtin((parsed_data->cmd)[0]))
					{
						run_cmd(parsed_data->cmd);
					}
					else
					{
						pid = fork();
						if (pid == 0)
							run_cmd(parsed_data->cmd);
						else
						{
							waitpid(pid, &exit_status, WCONTINUED);
							if (WIFEXITED(exit_status))
								all()->end_code = WEXITSTATUS(exit_status);
						}
					}
				}
				delete_parsed_data(parsed_data);
			}
			delete_split_strs(cmd_chunks);
			add_history(input);
			free(input);
		}
	}
	return 0;
} 