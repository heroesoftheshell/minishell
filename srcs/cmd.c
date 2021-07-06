/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:19:08 by hekang            #+#    #+#             */
/*   Updated: 2021/07/06 17:49:05 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		run_cmd(char *cmd)
{
	char		*path;
	char		**split_path;
	int			cnt;
	extern char	**environ;
	char 		**chunk;

	chunk = ft_split(cmd, ' ');

	path = get_env_path();
	split_path = ft_split(path, ':');
	if (chunk[0][0] != '/')
		chunk[0] = ft_strjoin("/", chunk[0]);
	cnt = -1;
	while (split_path[++cnt])
		execve(ft_strjoin(split_path[cnt], chunk[0]), chunk, environ);
	execve(chunk[0], chunk, environ);
	perror(chunk[0]);
}