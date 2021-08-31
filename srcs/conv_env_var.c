/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 17:32:23 by ghong             #+#    #+#             */
/*   Updated: 2021/08/31 17:43:41 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_converting_str(char const *str, unsigned int start, size_t len)
{
	char			*env_key;
	char			*env_value;

	if (len == 0)
		return (ft_strdup("$"));
	env_key = ft_substr(str, start, len);
	env_value = get_env_variable((const char *)env_key);
	if (env_key)
		free(env_key);
	return (env_value);
}

char	*conv_env_var(const char **src, int str_idx, int *char_idx, \
	bool is_inside_quote)
{
	size_t			str_len;
	unsigned int	start_char_idx;

	start_char_idx = *char_idx + 1;
	str_len = 0;
	while (src[str_idx][++(*char_idx)])
	{
		if (is_quote(src[str_idx][*char_idx]) || \
			ft_isspace(src[str_idx][*char_idx]))
		{
			if (!is_inside_quote)
				--(*char_idx);
			return (get_converting_str(src[str_idx], start_char_idx, str_len));
		}
		str_len++;
	}
	if (is_inside_quote)
		return (NULL);
	else
		return (get_converting_str(src[str_idx], start_char_idx, str_len));
	return (NULL);
}
