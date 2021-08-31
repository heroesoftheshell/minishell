/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:33:14 by ghong             #+#    #+#             */
/*   Updated: 2021/08/31 17:44:44 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*convert_env_str(const char **src, int str_idx, \
							unsigned int *start_char_idx, int *char_idx)
{
	char	*env_value;
	char	*converted_str;

	converted_str = NULL;
	if (*char_idx - *start_char_idx > 0)
	{
		converted_str = substr_join(converted_str, \
			ft_substr(src[str_idx], *start_char_idx, \
			*char_idx - *start_char_idx));
	}
	env_value = conv_env_var(src, str_idx, char_idx, true);
	if (env_value != NULL)
		converted_str = substr_join(converted_str, env_value);
	*start_char_idx = *char_idx;
	if (src[str_idx][*char_idx] == '\0')
		return (NULL);
	return (converted_str);
}

char	*parse_quote_str(const char **src, char quote_char, int str_idx, \
			int *char_idx)
{
	int				str_len;
	unsigned int	start_char_idx;
	char			*converted_str;

	start_char_idx = *char_idx + 1;
	str_len = 0;
	while (src[str_idx][++(*char_idx)])
	{
		if (src[str_idx][*char_idx] == '$' && quote_char == '"')
			converted_str = convert_env_str(src, str_idx, &start_char_idx, \
				char_idx);
		if (src[str_idx][*char_idx] == '\0')
			return (NULL);
		else if (src[str_idx][*char_idx] == quote_char)
		{
			converted_str = substr_join(converted_str, \
				ft_substr(src[str_idx], start_char_idx, \
				*char_idx - start_char_idx));
			return (converted_str);
		}
		str_len++;
	}
	return (NULL);
}
