/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_env_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 12:19:44 by hekang            #+#    #+#             */
/*   Updated: 2021/09/02 16:10:23 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
					return (0);
			}
			else
				if (!(ft_isalpha(key[cnt]) || ft_isdigit(key[cnt]) \
				|| key[cnt] == '_' || key[cnt] == '='))
					return (0);
		}
		return (1);
	}
	return (0);
}
