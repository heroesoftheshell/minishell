/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:13:43 by hekang            #+#    #+#             */
/*   Updated: 2021/08/24 14:14:18 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_chdir(char **cmd)
{
	char	*pwd;
	char	buf[255];
	int		cd;

	if (cmd[1] == NULL || !ft_strcmp("~", cmd[1]))
	{
		pwd = get_env_variable("HOME");
		if (pwd == NULL)
		{
			ft_putendl_fd("\033[1;4;34;47mHOS :\033[0m cd: HOME not set", STDERR_FILENO);
			return ;
		}
		chdir(pwd);
		set_env_variable("PWD", getcwd(buf, 255));
	}
	else
	{
		pwd = get_env_variable("PWD");
		pwd = ft_strjoin(pwd, "/");
		cd = chdir(ft_strjoin(pwd, cmd[1]));
		if (cd == -1)
		{
			ft_putstr_fd("\033[1;4;34;47mHOS :\033[0m cd: ", STDERR_FILENO);
			ft_putstr_fd(cmd[1],STDERR_FILENO);
			ft_putendl_fd(": Not a directory", STDERR_FILENO);
		}
		set_env_variable("PWD", getcwd(buf, 255));
	}
	free(pwd);
	all()->end_code = 0;
}