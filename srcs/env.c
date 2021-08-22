/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:15:19 by hekang            #+#    #+#             */
/*   Updated: 2021/08/20 16:53:09 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(char **envp)
{
	int	cnt;

	cnt = -1;

	while (envp[++cnt])
	{
		// envp[cnt][ft_strlen(envp[cnt])] = 0;
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
	// printf("%s\n", (char *)(temp->content));
	// printf("strnstr: %s\n", ft_strnstr((char *)temp->content, "=", ft_strlen((char *)temp->content)));
		if (ft_strnstr((char *)temp->content, "=", ft_strlen((char *)temp->content)))
			ft_putendl_fd((char *)(temp->content), STDOUT_FILENO);
		// write(STDOUT_FILENO, (char *)(temp->content), )
		temp = temp->next;
	}
	// exit(0);
}

char	*get_env_path(void)
{
		char		*path;

		path = getenv("PATH");
		return (path);
}

char	*get_env_variable(const char *env_key)
{
	char		*env_value;

	if (env_key == NULL)
		return (NULL);
	env_value = getenv(env_key);
	return (env_value);
}