/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:13:43 by hekang            #+#    #+#             */
/*   Updated: 2021/09/09 09:34:25 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chdir_errno(int err, char *name)
{
	if (err == ENOTDIR)
	{
		ft_putstr_fd("\033[1;4;34;47mHOS :\033[0m cd: ", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
	}
	else if (err == EACCES)
	{
		ft_putstr_fd("\033[1;4;34;47mHOS :\033[0m cd: ", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	else if (err == ENOENT)
	{
		ft_putstr_fd("\033[1;4;34;47mHOS :\033[0m cd: ", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	else if (err == EFAULT)
		ft_putendl_fd("\033[1;4;34;47mHOS :\033[0m cd: HOME not set" \
		, STDERR_FILENO);
	return ;
}

void	ft_chdir(char **cmd)
{
	char	*pwd;
	char	buf[255];

	if (cmd[1] == NULL || !ft_strcmp("~", cmd[1]))
		pwd = get_env_variable("HOME");
	else if (cmd[1][0] == '/')
		pwd = ft_strdup(cmd[1]);
	else
	{
		pwd = get_env_variable("PWD");
		pwd = ft_strjoin_free_a(pwd, "/");
		pwd = ft_strjoin_free_a(pwd, cmd[1]);
	}
	chdir(pwd);
	if (errno)
	{
		chdir_errno(errno, cmd[1]);
		all()->end_code = 1;
		free(pwd);
		return ;
	}
	set_env_variable("PWD", getcwd(buf, 255));
	free(pwd);
	all()->end_code = 0;
}
