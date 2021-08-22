/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:25:07 by hekang            #+#    #+#             */
/*   Updated: 2021/08/20 17:28:55 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_env_key(char *cmd)
{
	t_list	*temp;
	int		cnt;
	char	**split;
	char	*value;
	char	*key;

	cnt = 0;
	value = 0;
	temp = all()->envp;
	split = ft_split(cmd, '=');
	if (!(split[1] == NULL))
	{
		key = strdup(split[0]);
		value = strdup(split[1]);
	}
	else
		key = strdup(cmd);
	free(split);
	while (cnt < ft_lstsize(all()->envp))
	{
		split = ft_split(temp->content, '=');
		if (!ft_strcmp(split[0], key))
		{
			if (value)
			{
				free(temp->content);
				temp->content = ft_strjoin3(key , "=",value);
			}
			return (1);
		}
		cnt++;
		temp = temp->next;
		free(split);
	}
	return (0);
}

void	print_export_error(char *key)
{
	char	*temp;
	char	*msg;

	temp = ft_strjoin("\033[1;4;34;47mHOS\033[0m: export: `", key);
	msg = ft_strjoin(temp, "': not a valid identifier");
	free(temp);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
}

void	print_declare(char *str)
{
	char 	**env;
	char	*s;

	env = ft_split(str, '=');
	s = ft_strjoin("declare -x ", env[0]);
	if (env[1])
	{
		s = ft_strjoin(ft_strjoin(s, "=\""), ft_strjoin(env[1], "\""));
	}
	ft_putendl_fd(s, STDOUT_FILENO);
	free (s);
}

void	export_declare(void)
{
	int		index;
	t_list	*temp;
	t_list	*current;
	int		cnt;

	index = 0;
	cnt = 0;
	temp = all()->envp;
	while (cnt < ft_lstsize(all()->envp))
	{
		index = 0;
		current = all()->envp;
		while(current)
		{
			if (ft_strcmp(temp->content, current->content) > 0)
				index++;
			current = current->next;
		}
		if (index == cnt)
		{
			print_declare(temp->content);
			cnt++;
			temp = all()->envp;
		}
		else
			temp = temp->next;
	}
}

void	ft_export(char **cmd)
{
	int	cnt;

	cnt = 0;
	if (cmd[1] == NULL)
	{
		export_declare();
	}
	else
	{
		while (cmd[++cnt])
		{

			if (!validate_env_key(cmd[cnt], 0))
				print_export_error(cmd[cnt]);
			else
			{
				if (!check_env_key(cmd[cnt]))
					ft_lstadd_back(&(all()->envp), ft_lstnew(ft_strdup(cmd[cnt])));
			}
		}

	}
	all()->end_code = 0;
}