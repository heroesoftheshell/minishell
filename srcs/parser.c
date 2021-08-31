/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:24:08 by ghong             #+#    #+#             */
/*   Updated: 2021/08/31 17:13:48 by ghong            ###   ########.fr       */
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

int	switch_str_to_handled_quote_str(char **splitted_data, \
				int str_idx)
{
	// FIXME: string variables should change structure type
	char	*converted_str;
	char	*quote_str;
	char	*substr;
	char	*joined_str;
	int		start_idx;
	int		char_idx;

	converted_str = NULL;
	joined_str = NULL;
	start_idx = 0;
	char_idx = -1;
	while (splitted_data[str_idx][++char_idx])
	{
		if (is_quote(splitted_data[str_idx][char_idx]))
		{
			substr = ft_substr(splitted_data[str_idx], start_idx, \
						char_idx - start_idx);
			quote_str = parse_quote_str((const char **)splitted_data, \
					splitted_data[str_idx][char_idx], str_idx, &char_idx);
			if (quote_str == NULL)
			{
				free(substr);
				if (converted_str)
					free(converted_str);
				print_err_msg(QUOTE_EXIT_ERR, "quote exit error", 0);
				return (QUOTE_EXIT_ERR);
			}
			if (converted_str == NULL)
				converted_str = ft_strjoin(substr, quote_str);
			else
			{
				joined_str = ft_strjoin(converted_str, substr);
				free(converted_str);
				free(substr);
				converted_str = ft_strjoin(joined_str, quote_str);
				free(joined_str);
				free(quote_str);
			}
			start_idx = char_idx + 1;
		}
		else if (splitted_data[str_idx][char_idx] == '$')
		{
			substr = ft_substr(splitted_data[str_idx], start_idx, \
					char_idx - start_idx);
			if (converted_str)
			{
				joined_str = ft_strjoin(converted_str, substr);
				free(converted_str);
				free(substr);
				substr = conv_env_var((const char **)splitted_data, \
					str_idx, &char_idx, false);
				if (substr)
				{
					converted_str = ft_strjoin(joined_str, substr);
					free(joined_str);
					free(substr);
				}
				else
				{
					converted_str = joined_str;
				}
			}
			else
			{
				converted_str = conv_env_var((const char **)splitted_data, \
					str_idx, &char_idx, false);
				if (converted_str == NULL)
					converted_str = ft_strdup("\0");
				joined_str = ft_strjoin(substr, converted_str);
				free(substr);
				free(converted_str);
				converted_str = joined_str;
			}
			start_idx = char_idx + 1;
		}
	}
	if (converted_str)
	{
		substr = ft_substr(splitted_data[str_idx], start_idx, \
				char_idx - start_idx);
		joined_str = ft_strjoin(converted_str, substr);
		free(converted_str);
		free(substr);
		free(splitted_data[str_idx]);
		splitted_data[str_idx] = joined_str;
	}
	return (SUCCESS);
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
	while (splitted_data[++sd_idx])
	{
		err_chk = switch_str_to_handled_quote_str(splitted_data, sd_idx);
		if (err_chk != SUCCESS)
			return (NULL);
	}
	parsed_data = (t_parse_data *)ft_calloc(1, sizeof(t_parse_data));
	divide_redirection((const char **)splitted_data, parsed_data);
	delete_split_strs(splitted_data);
	return (parsed_data);
}
