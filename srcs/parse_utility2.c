/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utility2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:40:19 by ghong             #+#    #+#             */
/*   Updated: 2021/09/07 20:39:08 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_include_filename_in_redirect(const char *str)
{
	if (is_redirect_sign(str[1]))
		return (str[2] != '\0');
	else
		return (str[1] != '\0');
}

void	delete_parsed_data(t_parse_data *p_data)
{
	int	idx;

	free(p_data->redirections);
	idx = -1;
	while ((p_data->cmd)[++idx])
	{
		free((p_data->cmd)[idx]);
	}
	free(p_data->cmd);
	free(p_data->last_in_fname);
	free(p_data->last_out_fname);
	free(p_data);
}

void	convert_env_execption(const char *env_key, char **ret)
{
	char	*itoa_result;

	if (!ft_strncmp("?", env_key, 1))
	{
		itoa_result = ft_itoa(all()->end_code);
		*ret = ft_strjoin(itoa_result, &env_key[1]);
		free(itoa_result);
		return ;
	}
	if (!validate_env_key((char *)env_key, 0))
		*ret = ft_strjoin("$", env_key);
}

int	str_count(char **str)
{
	int	count;

	if (str == NULL)
		return (0);
	count = 0;
	while (str[count])
		count++;
	return (count);
}

void	set_str_for_prev_redir(t_parse_data *p_data, char *str, char prev_redir)
{
	if (prev_redir == '\0')
		return ;
	if (prev_redir == '>')
	{
		if (p_data->last_out_fname)
			free(p_data->last_out_fname);
		p_data->last_out_fname = ft_strdup((const char *)str);
	}
	else if (prev_redir == '<')
	{
		if (p_data->last_in_fname)
			free(p_data->last_in_fname);
		p_data->last_in_fname = ft_strdup((const char *)str);
	}
}
