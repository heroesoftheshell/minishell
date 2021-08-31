/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_extension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:23:30 by ghong             #+#    #+#             */
/*   Updated: 2021/08/31 16:52:45 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substr_join(char *prev_str, char *substr)
{
	char	*joined_str;

	joined_str = NULL;
	if (prev_str == NULL)
		return (substr);
	else
	{
		joined_str = ft_strjoin(prev_str, substr);
		free(prev_str);
		free(substr);
		return (joined_str);
	}
}

char	*substr_join3(char *prefix, const char *mid_str, char *postfix)
{
	char	*joined_str;

	if (mid_str == NULL)
		return (substr_join(prefix, postfix));
	else
	{
		if (prefix == NULL)
			return (postfix);
		else
		{
			joined_str = ft_strjoin3(prefix, mid_str, postfix);
			free(prefix);
			free(postfix);
			return (joined_str);
		}
	}
}
