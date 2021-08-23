/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_endcode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 15:02:07 by hekang            #+#    #+#             */
/*   Updated: 2021/08/20 15:03:49 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_print_endcode(void)
{
	ft_putnbr_fd(all()->end_code, STDERR_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}