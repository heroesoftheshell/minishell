/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline_split_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 21:20:43 by ghong             #+#    #+#             */
/*   Updated: 2021/09/07 11:55:47 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	naive_skip_quote(char *s, int *ci)
{
	char	quote_char;

	if (is_quote(s[*ci]))
	{
		quote_char = s[*ci];
		(*ci)++;
		while (s[*ci] != '\0' && quote_char != s[*ci])
			(*ci)++;
		if (s[*ci] == quote_char)
			(*ci)++;
	}
}

void	skip_quote(char const *s, size_t *str_idx, size_t *word_len)
{
	if (is_quote(s[*str_idx]))
	{
		(*str_idx)++;
		if (word_len)
			(*word_len)++;
		while (s[*str_idx] != '\0' && !is_quote(s[*str_idx]))
		{
			(*str_idx)++;
			if (word_len)
				(*word_len)++;
		}
	}
}
