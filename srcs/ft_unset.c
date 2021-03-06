/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 09:54:55 by hekang            #+#    #+#             */
/*   Updated: 2021/09/02 10:48:16 by hekang           ###   ########.fr       */
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

int	del_unset_key(char *key)
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
			delete_split_strs(split);
			free(list_key);
			return (1);
		}
		delete_split_strs(split);
		free(list_key);
		prev = current;
		current = current->next;
	}
	return (0);
}

void	ft_unset(char **cmd)
{
	int		cnt;

	cnt = 0;
	while (cmd[++cnt])
	{
		if (!validate_env_key(cmd[cnt], 1))
			print_unset_error(cmd[cnt]);
		del_unset_key(cmd[cnt]);
	}
	all()->end_code = 0;
}
