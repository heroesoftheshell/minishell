/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 09:54:55 by hekang            #+#    #+#             */
/*   Updated: 2021/08/20 12:22:01 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_unset_error(char *key)
{
	char	*temp;
	char	*msg;

	temp = ft_strjoin("\033[1;4;34;47mHOS\033[0m: unset: `", key);
	msg = ft_strjoin(temp, "': not a valid identifier");
	free(temp);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
}

int		del_unset_key(char* key)
{
	t_list		*current;
	char		*list_key;
	char		**split;
	t_list		*prev;

	current = all()->envp;

	while (current)
	{
		split = ft_split(current->content, '=');
		list_key = ft_strdup(split[0]);
		if (!ft_strcmp(key, list_key))
		{
			prev->next = current->next;
			free(current->content);
			free(current);
			return (1);
		}
		free(split);
		free(list_key);
		prev = current;
		current = current->next;
	}
	return (0);
}

int			ft_unset(char **cmd)
{
	int		ret;

	ret = 0;

	if (!validate_env_key(cmd[1]))
		print_unset_error(cmd[1]);
	del_unset_key(cmd[1]);
	return (0);
}