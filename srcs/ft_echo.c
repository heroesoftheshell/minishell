/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:33:00 by hekang            #+#    #+#             */
/*   Updated: 2021/08/20 15:31:31 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd)
{
	int		cnt;

	cnt = 0;
	if (!strcmp(cmd[1], "-n"))
		++cnt;
	while (cmd[++cnt])
	{
		write(STDOUT_FILENO, cmd[cnt], ft_strlen(cmd[cnt]));
		if (cmd[cnt + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (strcmp(cmd[1], "-n"))
		write(STDOUT_FILENO, "\n", 1);
	all()->end_code = 0;
}