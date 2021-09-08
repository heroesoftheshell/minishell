/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:33:24 by ghong             #+#    #+#             */
/*   Updated: 2021/09/08 18:47:22 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_last_redirection_filename(t_parse_data *p_data, char *str, \
			char prev_redir)
{
	if (str == NULL)
		return ;
	if (str[0] == '>')
	{
		if (p_data->last_out_fname)
			free(p_data->last_out_fname);
		if (str[1] == '>')
			p_data->last_out_fname = ft_substr(str + 2, 0, ft_strlen(str));
		else
			p_data->last_out_fname = ft_substr(str + 1, 0, ft_strlen(str));
	}
	else if (str[0] == '<')
	{
		if (p_data->last_in_fname)
			free(p_data->last_in_fname);
		if (str[1] == '<')
			p_data->last_in_fname = ft_substr(str + 2, 0, ft_strlen(str));
		else
			p_data->last_in_fname = ft_substr(str + 1, 0, ft_strlen(str));
	}
	else
		set_str_for_prev_redir(p_data, str, prev_redir);
}

static void	set_redirections(const char *str, int s_ci, int ci, \
				t_parse_data *p_data)
{
	char	*substr;
	size_t	strlen;

	substr = ft_substr(str, s_ci, ci - s_ci);
	if (substr && is_redirect_sign(substr[0]) && \
			is_include_filename_in_redirect(substr))
		set_last_redirection_filename(p_data, substr, '\0');
	if (p_data->redirections)
	{
		strlen = ft_strlen(p_data->redirections);
		if (is_redirect_sign((p_data->redirections)[strlen - 1]))
		{
			set_last_redirection_filename(p_data, substr, \
				(p_data->redirections)[strlen - 1]);
			p_data->redirections = substr_join(p_data->redirections, substr);
		}
		else
			p_data->redirections = substr_join3(p_data->redirections, \
				ft_strdup(","), substr);
	}
	else
		p_data->redirections = substr;
}

static void	pick_redirection(char **sp_data, int *si, int *ci, \
				t_parse_data *p_data)
{
	int		s_ci;

	s_ci = *ci;
	if (!is_include_filename_in_redirect(&sp_data[*si][*ci]))
	{
		set_redirections(sp_data[*si], s_ci, ft_strlen(sp_data[*si]), p_data);
		++(*si);
		*ci = -1;
		s_ci = 0;
	}
	else if (is_redirect_sign(sp_data[*si][*ci + 1]))
		++(*ci);
	while (sp_data[*si][++(*ci)])
	{
		if (is_redirect_sign(sp_data[*si][*ci]))
		{
			set_redirections(sp_data[*si], s_ci, *ci, p_data);
			--(*ci);
			return ;
		}
	}
	set_redirections(sp_data[*si], s_ci, *ci, p_data);
	--(*ci);
}

static void	pick_command(bool *is_exist_redir, char *str, int ci, \
				t_parse_data *p_data)
{
	if (ci != 0 && !*is_exist_redir)
	{
		(p_data->cmd)[p_data->cmd_count] = ft_substr(str, 0, ci);
		*is_exist_redir = true;
		(p_data->cmd_count)++;
	}
	*is_exist_redir = true;
}

void	divide_redirection(char **sp_data, t_parse_data *p_data)
{
	int		si;
	int		ci;
	bool	is_exist_redir;

	si = -1;
	p_data->cmd_count = 0;
	while (sp_data[++si])
	{
		ci = -1;
		is_exist_redir = false;
		while (sp_data[si][++ci])
		{
			naive_skip_quote(sp_data[si], &ci);
			if (is_redirect_sign(sp_data[si][ci]))
			{
				pick_command(&is_exist_redir, sp_data[si], ci, p_data);
				pick_redirection(sp_data, &si, &ci, p_data);
			}
		}
		if (!is_exist_redir)
			(p_data->cmd)[(p_data->cmd_count)++] = ft_strdup(sp_data[si]);
	}
	(p_data->cmd)[(p_data->cmd_count)++] = NULL;
}
