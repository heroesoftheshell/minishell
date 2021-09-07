/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:24:08 by ghong             #+#    #+#             */
/*   Updated: 2021/09/07 20:37:35 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_cmd_chunk(const char *chunk)
{
	int		err_chk;

	while (*chunk)
	{
		if (is_redirect_sign(*chunk))
		{
			err_chk = validate_redirect_expression(&chunk, *chunk);
			if (err_chk != SUCCESS)
				return (err_chk);
		}
		chunk++;
	}
	return (SUCCESS);
}

char	**line_parse(const char *line)
{
	char	**pipe_cmd_chunk;
	int		str_index;

	if (*line == '|')
	{
		print_err_msg(PIPE_SYNTAX_ERR, "|", 0);
		return (NULL);
	}
	skip_space(&line);
	pipe_cmd_chunk = cmdline_split(line, "|");
	str_index = 0;
	while (pipe_cmd_chunk && pipe_cmd_chunk[str_index])
	{
		if (validate_cmd_chunk(pipe_cmd_chunk[str_index]) != SUCCESS)
		{
			delete_split_strs(pipe_cmd_chunk);
			return (NULL);
		}
		str_index++;
	}
	return (pipe_cmd_chunk);
}

t_parse_data	*cmd_chunk_parse(const char *chunk)
{
	t_parse_data	*parsed_data;
	char			**splitted_data;
	int				sd_idx;
	int				err_chk;

	skip_space(&chunk);
	splitted_data = cmdline_split(chunk, " ");
	if (splitted_data == NULL)
		return (NULL);
	sd_idx = -1;
	parsed_data = (t_parse_data *)ft_calloc(1, sizeof(t_parse_data));
	parsed_data->cmd = (char **)ft_calloc(str_count(splitted_data) + 1, \
		sizeof(char *));
	divide_redirection(splitted_data, parsed_data);
	sd_idx = -1;
	while ((parsed_data->cmd)[++sd_idx])
	{
		err_chk = switch_str_to_handled_quote_str(parsed_data->cmd, sd_idx);
		if (err_chk != SUCCESS)
			return (NULL);
	}
	if (parsed_data->redirections)
		switch_str_to_handled_quote_str(&parsed_data->redirections, 0);
	delete_split_strs(splitted_data);
	return (parsed_data);
}
