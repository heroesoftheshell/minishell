/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:07:28 by ghong             #+#    #+#             */
/*   Updated: 2021/07/06 13:35:14 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parse_err(int err_type, char c)
{
	write(STDERR_FILENO, "hosh: ", 7);
	if (err_type == PIPE_SYNTAX_ERR || err_type == REDIRECT_SYNTAX_ERR)
		printf("hosh: syntax error near unexpected token `%c'\n", c);
	else if (err_type == NEWLINE_SYNTAX_ERR)
		printf("hosh: syntax error near unexpected token `newline'\n");
}

void	print_syntax_err(int err_type, char *buf)
{
	write(STDERR_FILENO, "hosh: syntax error near unexpected token", 41);
	if (err_type == PIPE_SYNTAX_ERR)
		write(STDERR_FILENO, "`|'\n", 5);
	else if (err_type == REDIRECT_SYNTAX_ERR)
		write(STDERR_FILENO, buf, 5);
	else if (err_type == NEWLINE_SYNTAX_ERR)
		write(STDERR_FILENO, "`newline'\n", 11);
}