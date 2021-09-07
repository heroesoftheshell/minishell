/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_env_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 12:19:44 by hekang            #+#    #+#             */
/*   Updated: 2021/09/07 22:12:12 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int free2(char *s1, char *s2, int ret)
{
	free(s1);
	free(s2);
	return (ret);
}

int	validate_env_key(char *cmd, int unset_key)
{
	int		cnt;
	char	*key;
	char	*value;

	cnt = 0;
	get_key_value(cmd, &key, &value);
	if (ft_isalpha(key[0]) || key[0] == '_')
	{
		while (key[++cnt])
		{
			if (unset_key)
			{
				if (!(ft_isalpha(key[cnt]) || ft_isdigit(key[cnt]) \
				|| key[cnt] == '_'))
					return free2(key, value, 0);
			}
			else
				if (!(ft_isalpha(key[cnt]) || ft_isdigit(key[cnt]) \
				|| key[cnt] == '_' || key[cnt] == '='))
					return free2(key, value, 0);
		}
		return free2(key, value, 1);
	}
	return free2(key, value, 0);
}
