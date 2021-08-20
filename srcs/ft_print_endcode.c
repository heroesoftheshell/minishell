/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_endcode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 15:02:07 by hekang            #+#    #+#             */
/*   Updated: 2021/08/20 15:06:14 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_print_endcode(void)
{
	ft_putstr_fd("\033[1;4;34;47mHOS\033[0m: ", STDOUT_FILENO);
	ft_putnbr_fd(all()->end_code, STDOUT_FILENO);
	ft_putstr_fd(": command not found\n", STDOUT_FILENO);
}