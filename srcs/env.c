/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:15:19 by hekang            #+#    #+#             */
/*   Updated: 2021/07/06 17:33:14 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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