/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:22:47 by hekang            #+#    #+#             */
/*   Updated: 2021/08/27 17:18:07 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		!ft_strcmp(cmd, "$?") ||
		!ft_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	char	*input;
	int		pipefd[2];
	int		pipefd2[2];
	int		pipefd_backup[2];
	char	**cmd_chunks;
	int		chunk_idx;
	int		pid;
	int		pid_list[BUFSIZ];
	int		exit_status;
	int		is_pipe;
	t_parse_data	*parsed_data;
	int		idx;
	int		backup_fd;

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
		dup2(pipefd_backup[0], 0);
		dup2(pipefd_backup[1], 1);
        input = readline("\033[1;4;34;47mHOS >\033[0m ");
		if (input == 0)
			break ;
		else
		{
			signal(SIGINT, do_nothing);
			// rl_on_new_line();
			cmd_chunks = line_parse((const char *)input);
			chunk_idx = -1;
			while (cmd_chunks && cmd_chunks[++chunk_idx] != NULL)
			{
				parsed_data = cmd_chunk_parse((const char *)cmd_chunks[chunk_idx]);
				if (parsed_data == NULL)
				{
					continue ;
				}
				if (parsed_data->redirections)
				{
					handle_redirection(parsed_data->redirections);
				}
				if (cmd_chunks[chunk_idx + 1] != NULL && is_pipe != 1)
				{
					is_pipe = 1;
					pipe(pipefd);
					pid = fork();
					if (pid == 0) // child
					{
						dup2(pipefd_backup[0], STDIN_FILENO);
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
				else if (cmd_chunks[chunk_idx + 1] != NULL && is_pipe == 1)
				{
					pipe(pipefd2);
					pid = fork();
					if (pid == 0) // child
					{
						dup2(pipefd[0], STDIN_FILENO);
						close(pipefd[0]);
						close(pipefd[1]);
						dup2(pipefd2[1], STDOUT_FILENO);
						close(pipefd2[1]); // fd 교체
						close(pipefd2[0]);
						run_cmd(parsed_data->cmd);
						exit(all()->end_code);
					}
					if (pid > 0)
					{
						close(pipefd2[1]);
						close(pipefd[0]);
						pid_list[++idx] = pid;
						dup2(pipefd2[0], pipefd[0]);
						close(pipefd2[0]);
					}
				}
				else if (is_pipe)
				{
					pid = fork();
					if (pid == 0) // child
					{
						dup2(pipefd[0], STDIN_FILENO);
						close(pipefd[0]);
						dup2(pipefd_backup[1], STDOUT_FILENO);
						run_cmd(parsed_data->cmd);
						exit(all()->end_code);
					}
					if (pid > 0)
					{
						close(pipefd[0]);
						close(pipefd_backup[1]);
						pid_list[++idx] = pid;
						idx = -1;
						while (pid_list[++idx])
						{
							waitpid(pid_list[idx], &exit_status, 0);
							if (WTERMSIG(exit_status) == SIGINT || WTERMSIG(exit_status) == SIGQUIT)
								all()->end_code = WEXITSTATUS(exit_status);
							pid_list[idx] = 0;
						}
						idx = -1;
						is_pipe = 0;
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
			signal(SIGINT, catch_function);

			free(input);
		}
	}
	return 0;
} 