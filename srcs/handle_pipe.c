/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:18:53 by hekang            #+#    #+#             */
/*   Updated: 2021/09/02 11:44:03 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_pipe(t_parse_data *parsed_data, int *pid_list, int *pipefd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(all()->pipefd_backup[0], STDIN_FILENO);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		run_cmd(parsed_data->cmd, parsed_data);
		exit(all()->end_code);
	}
	if (pid > 0)
	{
		pid_list[pid_list[0]] = pid;
		pid_list[0] = pid_list[0] + 1;
		close(pipefd[1]);
	}
}

void	middle_pipe(t_parse_data *parsed_data, int *pid_list, int *pipefd)
{
	int	pipefd2[2];
	int	pid;

	pipe(pipefd2);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		dup2(pipefd2[1], STDOUT_FILENO);
		close(pipefd2[1]);
		close(pipefd2[0]);
		run_cmd(parsed_data->cmd, parsed_data);
		exit(all()->end_code);
	}
	if (pid > 0)
	{
		close(pipefd2[1]);
		close(pipefd[0]);
		pid_list[pid_list[0]] = pid;
		pid_list[0] = pid_list[0] + 1;
		dup2(pipefd2[0], pipefd[0]);
		close(pipefd2[0]);
	}
}

void	last_pipe(t_parse_data *parsed_data, int *pid_list, int *pipefd)
{
	int	pid;
	int	exit_status;
	int	idx;

	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		dup2(all()->pipefd_backup[1], STDOUT_FILENO);
		run_cmd(parsed_data->cmd, parsed_data);
		exit(all()->end_code);
	}
	if (pid > 0)
	{
		close_both(pipefd[0], all()->pipefd_backup[1]);
		pid_list[pid_list[0]] = pid;
		idx = 0;
		while (pid_list[++idx])
			waitpid(pid_list[idx], &exit_status, 0);
		handle_exit_status(exit_status);
		pid_list[idx] = 0;
	}
	pid_list[0] = 1;
}

void	none_pipe(t_parse_data *parsed_data)
{
	int	pid;
	int	exit_status;
	int	sig_num;

	pid = 0;
	sig_num = 0;
	if (is_builtin((parsed_data->cmd)[0]))
		run_cmd(parsed_data->cmd, parsed_data);
	else
	{
		pid = fork();
		if (pid == 0)
			run_cmd(parsed_data->cmd, parsed_data);
		else
		{
			waitpid(pid, &exit_status, 0);
			handle_exit_status(exit_status);
		}
	}
}
