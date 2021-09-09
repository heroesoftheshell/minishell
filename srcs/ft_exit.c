/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 15:27:17 by hekang            #+#    #+#             */
/*   Updated: 2021/09/09 10:56:56 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **chunk)
{
	int		code;
	char	*exit_code;

	exit_code = chunk[1];
	code = 0;
	if (str_count(chunk) > 2)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("\033[1;4;34;47mHOS\033[0m: exit: \
too many arguments", STDERR_FILENO);
		all()->end_code = 1;
		return ;
	}
	if (exit_code)
		code = ft_atoi(exit_code);
	all()->end_code = code;
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(code);
}
