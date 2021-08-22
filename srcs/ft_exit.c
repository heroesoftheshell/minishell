/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 15:27:17 by hekang            #+#    #+#             */
/*   Updated: 2021/08/20 15:32:50 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char *exit_code)
{
	int	code;

	code = 0;
	if (exit_code)
		code = ft_atoi(exit_code);
	all()->end_code = code;
	exit(code);
}