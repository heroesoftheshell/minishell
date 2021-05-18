/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:44:51 by hekang            #+#    #+#             */
/*   Updated: 2021/05/18 15:26:43 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_list			*init_list(void)
{
	t_list		*result;

	result = (t_list *)ft_calloc(1, sizeof(t_list));
	result->content = NULL;
	result->next = NULL;
	return (result);
}

int				parse_cmd_type(char *string)
{
	int cnt;

	cnt = 0;
	while (string[cnt] == ' ')
		cnt++;

}

void			skip_space(char *string)
{
	while (string)
	{
		if (string != ' ')
			return ;
		string++;
	}
}

int				find_space(char *string)
{
	int			cnt;

	cnt = 0;
	while (string)
	{
		if (string == ' ')
			return (cnt);
		string++;
		cnt++;
	}

t_list			*parse(char *string)
{
	t_list		*cmd_rowdata;
	char		*redirection_block;
	char		*setence_rowdata;
	int			cmd_end_type;
	int			redirection_flag;
	char		*start;
	int			*string_len;

	redirection_flag = 0;
	cmd_rowdata = init_list();
	skip_space(string);
	if (string == '>' || string == '<')
	{
		start = string;
		if (string == '>' && string + 1 == '>')
			string++;
		string++;
		redirection_flag = 1;
	}
	if (redirection_flag)
	{
		skip_space(string);
		string_len = find_sapce(string);
		ft_strjoin(redirection_block, start);
	}
