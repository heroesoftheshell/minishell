/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_extension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:23:30 by ghong             #+#    #+#             */
/*   Updated: 2021/09/01 16:21:03 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substr_join(char *prev_str, char *substr)
{
	char	*joined_str;

	joined_str = NULL;
	if (prev_str == NULL)
		return (substr);
	else if (substr == NULL)
		return (prev_str);
	else
	{
		joined_str = ft_strjoin(prev_str, substr);
		free(prev_str);
		free(substr);
		return (joined_str);
	}
}

char	*substr_join3(char *prefix, char *mid_str, char *postfix)
{
	char	*joined_str;

	if (mid_str == NULL)
		return (substr_join(prefix, postfix));
	else
	{
		if (prefix == NULL)
			return (substr_join(mid_str, postfix));
		else if (postfix == NULL)
			return (substr_join(prefix, mid_str));
		else
		{
			joined_str = ft_strjoin3(prefix, mid_str, postfix);
			free(prefix);
			free(mid_str);
			free(postfix);
			return (joined_str);
		}
	}
}
