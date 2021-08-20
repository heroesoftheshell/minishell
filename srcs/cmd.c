/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:19:08 by hekang            #+#    #+#             */
/*   Updated: 2021/08/20 15:33:31 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		run_cmd(char **chunk)
{
	char		*path;
	char		**split_path;
	int			cnt;
	// extern char	**environ;
	// char 		**chunk;
	// char		**line;
	// pid_t		pids[128];

	// line = ft_split(cmd, '|');
	cnt = -1;
	// while (++cnt < ft_strlen(line))
	// {
	// 	fork();
	// 	wait(NULL);
	// }
	// chunk = ft_split(cmd, ' ');
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
		ft_exit(chunk[1]);
	else 
	{
		path = get_env_path();
		split_path = ft_split(path, ':');
		if (chunk[0][0] != '/')
			chunk[0] = ft_strjoin("/", chunk[0]);
		cnt = -1;
		while (split_path[++cnt])
			execve(ft_strjoin(split_path[cnt], chunk[0]), chunk, (char *const *)(all()->envp));
		execve(chunk[0], chunk, (char *const *)(all()->envp));
		perror(chunk[0]);
	}
	
}