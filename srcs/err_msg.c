/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:07:28 by ghong             #+#    #+#             */
/*   Updated: 2021/09/01 16:40:56 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err_msg(int err_type, const char *str, char c)
{
	if (err_type == PIPE_SYNTAX_ERR || err_type == REDIRECT_SYNTAX_ERR || \
		err_type == NEWLINE_SYNTAX_ERR)
	{
		ft_putstr_fd(SYNTAX_ERR_MSG_HEADER, STDERR_FILENO);
		if (err_type == REDIRECT_SYNTAX_ERR)
			ft_putchar_fd(c, STDERR_FILENO);
		else
			ft_putstr_fd((char *)str, STDERR_FILENO);
		ft_putendl_fd(SYNTAX_ERR_MSG_TAIL, STDERR_FILENO);
	}
	else
		ft_putendl_fd((char *)str, STDERR_FILENO);
}

void	print_system_err(const char *str)
{
	write(STDERR_FILENO, "hosh: ", 6);
	perror(str);
}
