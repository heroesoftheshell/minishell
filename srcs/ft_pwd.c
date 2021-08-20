/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:36:22 by hekang            #+#    #+#             */
/*   Updated: 2021/08/20 09:51:18 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd()
{
	char	buf[255];
	
	getcwd(buf, 255);
	write(STDOUT_FILENO, buf, ft_strlen(buf));
	write(STDOUT_FILENO, "\n", 1);
	// exit(0);
}