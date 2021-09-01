/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_str_to_handled_quote_str.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:08:49 by ghong             #+#    #+#             */
/*   Updated: 2021/09/01 16:28:24 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quote(char **converted_str, char *substr, char *quote_str)
{
	if (quote_str == NULL)
	{
		free(substr);
		if (*converted_str)
			free(*converted_str);
		print_err_msg(QUOTE_EXIT_ERR, "quote exit error", 0);
		return (QUOTE_EXIT_ERR);
	}
	*converted_str = substr_join3(*converted_str, substr, quote_str);
	return (SUCCESS);
}

static int	switch_str(char	*converted_str, char **sp_data, int si, \
				unsigned int fci)
{
	if (converted_str)
	{
		converted_str = substr_join(converted_str, \
			ft_substr(sp_data[si], fci, ft_strlen(&(sp_data[si][fci]))));
		free(sp_data[si]);
		sp_data[si] = converted_str;
	}
	return (SUCCESS);
}

static int	check_str_expanding(char **sp_data, char **converted_str, \
				int si, unsigned int *fci)
{
	int		ci;
	char	*substr;

	ci = -1;
	while (sp_data[si][++ci])
	{
		if (is_quote(sp_data[si][ci]))
		{
			substr = ft_substr(sp_data[si], *fci, ci - *fci);
			if (handle_quote(converted_str, substr, \
					parse_quote_str((const char **)sp_data, \
					sp_data[si][ci], si, &ci)) != SUCCESS)
				return (QUOTE_EXIT_ERR);
			*fci = ci + 1;
		}
		else if (sp_data[si][ci] == '$')
		{
			substr = ft_substr(sp_data[si], *fci, ci - *fci);
			*converted_str = substr_join3(*converted_str, substr, \
				conv_env_var((const char **)sp_data, si, &ci, false));
			*fci = ci + 1;
		}
	}
	return (SUCCESS);
}

int	switch_str_to_handled_quote_str(char **sp_data, int si)
{
	char			*converted_str;
	unsigned int	fci;
	int				err_chk;

	converted_str = NULL;
	fci = 0;
	err_chk = check_str_expanding(sp_data, &converted_str, si, &fci);
	if (err_chk != SUCCESS)
		return (FAIL);
	return (switch_str(converted_str, sp_data, si, fci));
}
