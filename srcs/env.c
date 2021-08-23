/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:15:19 by hekang            #+#    #+#             */
/*   Updated: 2021/08/23 16:27:43 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(char **envp)
{
	int	cnt;

	cnt = -1;

	while (envp[++cnt])
	{
		if (cnt == 0)
			all()->envp = ft_lstnew(envp[cnt]);
		else
			if (envp[cnt][0])
				ft_lstadd_back(&(all()->envp), ft_lstnew(envp[cnt]));
	}
}

void	ft_env(void)
{
	t_list		*temp;

	temp = (all()->envp);
	while (temp)
	{
		if (ft_strnstr((char *)temp->content, "=", ft_strlen((char *)temp->content)))
			ft_putendl_fd((char *)(temp->content), STDOUT_FILENO);
		temp = temp->next;
	}
}

char	*get_env_path(void)
{
	t_list		*current;
	char		**split;

	current = all()->envp;
	while (current)
	{
		split = ft_split(current->content, '=');
		if (!split[0])
			return (NULL);
		if (ft_strcmp("path", split[0]))
			return split[1];
		current = current->next;
	}
	return (NULL);
}

char	*get_env_variable(const char *env_key)
{
	t_list		*current;
	char		**split;

	if (env_key == NULL)
		return (NULL);
	current = all()->envp;
	while (current)
	{
		split = ft_split(current->content, '=');
		if (!split[0])
			return (NULL);
		if (ft_strcmp(env_key, split[0]))
			return split[1];
		current = current->next;
	}
	return (NULL);
}
