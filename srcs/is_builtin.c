/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:12:27 by hekang            #+#    #+#             */
/*   Updated: 2021/09/09 10:26:22 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd && cmd[0] == '\0')
		return (1);
	if (!ft_strcmp(cmd, "cd") || \
		!ft_strcmp(cmd, "echo") || \
		!ft_strcmp(cmd, "exit") || \
		!ft_strcmp(cmd, "env") || \
		!ft_strcmp(cmd, "export") || \
		!ft_strcmp(cmd, "unset") || \
		!ft_strcmp(cmd, "$?") || \
		!ft_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}
