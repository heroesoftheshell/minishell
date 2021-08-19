/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:13:43 by hekang            #+#    #+#             */
/*   Updated: 2021/08/19 16:40:56 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_chdir(char **cmd)
{
	char	*pwd;
	pwd = get_env_variable("PWD");
	pwd = ft_strjoin(pwd, "/");
	printf("pwd : %s\n", pwd);
	int n = chdir(ft_strjoin(pwd, cmd[1]));
	printf("chdir : %s\n", ft_strjoin(pwd, cmd[1]));
	printf("chdir n : %d\n", n);
	exit(0);
}