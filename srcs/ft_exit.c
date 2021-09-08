/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 15:27:17 by hekang            #+#    #+#             */
/*   Updated: 2021/09/09 08:46:24 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **chunk)
{
	int		code;
	char	*exit_code;

	exit_code = chunk[1];
	code = 0;
	if (chunk[2])
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return ;
	}
	if (exit_code)
		code = ft_atoi(exit_code);
	all()->end_code = code;
	exit(code);
}
