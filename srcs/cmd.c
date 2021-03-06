/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:19:08 by hekang            #+#    #+#             */
/*   Updated: 2021/09/09 10:27:26 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_cmd_error(char *cmd)
{
	ft_putstr_fd("\033[1;4;34;47mHOS\033[0m: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	all()->end_code = 127;
}

char	**make_env(void)
{
	char		**env;
	t_list		*current;
	int			idx;

	idx = -1;
	current = all()->envp;
	env = ft_calloc(ft_lstsize(current), sizeof(char *));
	while (current)
	{
		env[++idx] = current->content;
		current = current->next;
	}
	return (env);
}

int	run_builtin(char **chunk)
{
	if (!ft_strcmp(chunk[0], "cd"))
		ft_chdir(chunk);
	else if (!ft_strcmp(chunk[0], "echo"))
		ft_echo(chunk);
	else if (!ft_strcmp(chunk[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(chunk[0], "export"))
		ft_export(chunk);
	else if (!ft_strcmp(chunk[0], "env"))
		ft_env();
	else if (!ft_strcmp(chunk[0], "unset"))
		ft_unset(chunk);
	else if (!ft_strcmp(chunk[0], "$?"))
		ft_print_endcode();
	else if (!ft_strcmp(chunk[0], "exit"))
		ft_exit(chunk);
	else
		return (0);
	return (1);
}

void	run_cmd(char **chunk, t_parse_data	*parsed_data)
{
	char		*path;
	char		**split_path;
	int			cnt;
	char		*exec_path;

	if (handle_redirection(parsed_data, chunk[0]))
		return ;
	if (!run_builtin(chunk) && !is_builtin(chunk[0]))
	{
		path = get_env_path();
		split_path = ft_split(path, ':');
		cnt = -1;
		while (split_path[++cnt])
		{
			exec_path = ft_strjoin3(split_path[cnt], "/", chunk[0]);
			execve(exec_path, chunk, NULL);
			free(exec_path);
		}
		execve(chunk[0], chunk, NULL);
		ft_print_cmd_error(chunk[0]);
		exit(all()->end_code);
	}
}
