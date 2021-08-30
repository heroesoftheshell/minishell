/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirect_expression.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:44:28 by ghong             #+#    #+#             */
/*   Updated: 2021/08/30 16:40:05 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_newlne_syntax_err(char c)
{
	if (c == '\0')
	{
		print_err_msg(NEWLINE_SYNTAX_ERR, "newline", 0);
		return (true);
	}
	return (false);
}

static int	validate_included_space(const char **str)
{
	skip_space(str);
	if (is_newlne_syntax_err(**str))
		return (NEWLINE_SYNTAX_ERR);
	if (is_redirect_sign(**str))
	{
		print_err_msg(REDIRECT_SYNTAX_ERR, NULL, **str);
		return (REDIRECT_SYNTAX_ERR);
	}
	else if (ft_isprint(**str))
		return (SUCCESS);
	print_err_msg(FAIL, "invalid file name", 0);
	return (FAIL);
}

static int	validate_next_expression(const char **str)
{
	(*str)++;
	if (is_newlne_syntax_err(**str))
		return (NEWLINE_SYNTAX_ERR);
	else if (ft_isspace(**str))
		return (validate_included_space(str));
	return (SUCCESS);
}

int	validate_redirect_expression(const char **str, char start_c)
{
	if (validate_next_expression(str) != SUCCESS)
		return (FAIL);
	if (is_redirect_sign(**str) && start_c != **str)
	{
		print_err_msg(REDIRECT_SYNTAX_ERR, NULL, **str);
		return (REDIRECT_SYNTAX_ERR);
	}
	else if (is_redirect_sign(**str) && start_c == **str)
	{
		if (validate_next_expression(str) != SUCCESS)
			return (FAIL);
		if (is_redirect_sign(**str))
		{
			print_err_msg(REDIRECT_SYNTAX_ERR, NULL, **str);
			return (REDIRECT_SYNTAX_ERR);
		}
		else if (ft_isprint(**str))
			return (SUCCESS);
	}
	else if (ft_isprint(**str))
		return (SUCCESS);
	return (FAIL);
}
