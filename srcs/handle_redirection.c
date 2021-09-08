/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:42:00 by ghong             #+#    #+#             */
/*   Updated: 2021/09/08 17:57:46 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_ouput(char *filename, bool is_append_mode, t_parse_data *p_data)
{
	int	fd;

	if (is_append_mode)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open (filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		all()->end_code = 1;
		ft_putstr_fd("\033[1;4;34;47mHOS:\033[0m ", STDERR_FILENO);
		perror(filename);
		exit(all()->end_code);
	}
	if (ft_strcmp(p_data->last_out_fname, filename) == 0)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

void	clear_temp(bool is_heredoc_mode)
{
	char	**argv;
	pid_t	pid;
	int		exit_status;

	if (!is_heredoc_mode)
		return ;
	argv = malloc(sizeof(char *) * 3);
	argv[0] = "-f";
	argv[1] = "./temp";
	argv[2] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve("/bin/rm", (char *const *)argv, NULL);
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &exit_status, 0);
		if (WTERMSIG(exit_status) == SIGINT || WTERMSIG(exit_status) == SIGQUIT)
			all()->end_code = WEXITSTATUS(exit_status);
	}
	free(argv);
}

int	redirect_input(char *filename, char *cmd, t_parse_data *p_data)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		all()->end_code = 1;
		ft_putstr_fd("\033[1;4;34;47mHOS:\033[0m ", STDERR_FILENO);
		perror(filename);
		if (is_builtin(cmd))
			return (FAIL);
		else
			exit(all()->end_code);
	}
	if (ft_strcmp(p_data->last_in_fname, filename) == 0)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

int	classify_redirection_type(char *str, char *cmd, t_parse_data *p_data)
{
	int	idx;
	int	err_chk;

	idx = -1;
	while (str[++idx])
	{
		if (str[idx] == '>')
		{
			if (str[idx + 1] == '>')
				err_chk = redirect_ouput(&(str[idx + 2]), true, p_data);
			else
				err_chk = redirect_ouput(&(str[idx + 1]), false, p_data);
			return (err_chk);
		}
		else if (str[idx] == '<')
		{
			if (str[idx + 1] == '<')
				return (SUCCESS);
			else
				err_chk = redirect_input(&(str[idx + 1]), cmd, p_data);
			return (err_chk);
		}
	}
	return (FAIL);
}

int	handle_redirection(t_parse_data *parsed_data, char *cmd)
{
	char	**splitted_red;
	int		idx;
	int		err_chk;

	if (parsed_data->redirections == NULL)
		return (SUCCESS);
	splitted_red = ft_split(parsed_data->redirections, ',');
	if (splitted_red == NULL)
		return (FAIL);
	catch_heredoc(splitted_red, parsed_data);
	idx = -1;
	while (splitted_red[++idx])
	{
		err_chk = classify_redirection_type(splitted_red[idx], \
					cmd, parsed_data);
		if (err_chk != SUCCESS)
		{
			delete_split_strs(splitted_red);
			return (err_chk);
		}
	}
	delete_split_strs(splitted_red);
	return (err_chk);
}
