/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:12:25 by ghong             #+#    #+#             */
/*   Updated: 2021/07/29 15:14:32 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_split_strs(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	skip_space(const char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}

int		is_redirect_sign(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int		is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int		is_hyphen(char c)
{
	if (c == '-')
		return (1);
	return (0);
}