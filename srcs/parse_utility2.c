/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utility2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:40:19 by ghong             #+#    #+#             */
/*   Updated: 2021/09/01 16:59:55 by ghong            ###   ########.fr       */
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
	}
	if (!validate_env_key((char *)env_key, 0))
		*ret = ft_strjoin("$", env_key);
}
