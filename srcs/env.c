/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:15:19 by hekang            #+#    #+#             */
/*   Updated: 2021/08/29 21:47:18 by ghong            ###   ########.fr       */
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
			all()->envp = ft_lstnew(ft_strdup(envp[cnt]));
		else
			if (envp[cnt][0])
				ft_lstadd_back(&(all()->envp), ft_lstnew(ft_strdup(envp[cnt])));
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
	char		*ret;

	current = all()->envp;
	while (current)
	{
		split = ft_split(current->content, '=');
		if (!split[0])
			return (NULL);
		if (!ft_strcmp("PATH", split[0]))
			ret = ft_strdup(split[1]);
		current = current->next;
	}
	delete_split_strs(split);
	return (ret);
}

void	set_env_variable(const char *env_key, const char *env_value)
{
	t_list		*current;
	char		**split;

	current = all()->envp;
	while (current)
	{
		split = ft_split(current->content, '=');
		if (!ft_strcmp(env_key, split[0]))
			current->content = ft_strjoin3(env_key, "=", env_value);
		current = current->next;
	}
	delete_split_strs(split);
}

char	*get_env_variable(const char *env_key)
{
	t_list		*current;
	char		**split;
	char		*ret;

	ret = NULL;
	if (env_key == NULL)
		return (NULL);
	if (!validate_env_key((char *)env_key, 0))
		return (ft_strjoin("$", env_key));
	current = all()->envp;
	while (current)
	{
		split = ft_split(current->content, '=');
		if (!split[0])
			return (NULL);
		if (!ft_strcmp(env_key, split[0]))
			ret = ft_strdup(split[1]);
		current = current->next;
	}
	delete_split_strs(split);
	return (ret);
}
