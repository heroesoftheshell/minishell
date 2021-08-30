/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:30:19 by hekang            #+#    #+#             */
/*   Updated: 2021/08/30 16:30:56 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	push_value(char *key, char *value, t_list *temp)
{
	if (value)
	{
		free(temp->content);
		temp->content = ft_strjoin3(key, "=", value);
	}
	return (1);
}

int	get_key_value(char *cmd, char *key, char *value)
{
	char	**split;

	split = ft_split(cmd, '=');
	if (!(split[1] == NULL))
	{
		key = strdup(split[0]);
		value = strdup(split[1]);
	}
	else
		key = strdup(cmd);
	free(split);
}

int	check_env_key(char *cmd)
{
	t_list	*temp;
	int		cnt;
	char	**split;
	char	*value;
	char	*key;

	cnt = -1;
	value = 0;
	temp = all()->envp;
	get_key_value(cmd, &key, &value);
	while (++cnt < ft_lstsize(all()->envp))
	{
		split = ft_split(temp->content, '=');
		if (!ft_strcmp(split[0], key))
			return (push_value(key, value, temp));
		temp = temp->next;
		free(split);
	}
	return (0);
}
