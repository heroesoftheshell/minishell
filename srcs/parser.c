/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:24:08 by ghong             #+#    #+#             */
/*   Updated: 2021/08/22 05:49:34 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_redirect_expression(const char **str, char start_c)
{
	bool	contain_space;

	contain_space = false;
	// FIXME: duplicated logic
	(*str)++;
	if (ft_isspace(**str))
	{
		contain_space = true;
		skip_space(str);
		if (**str == 0)
		{
			print_err_msg(NEWLINE_SYNTAX_ERR, "newline", 0);
			return (NEWLINE_SYNTAX_ERR);
		}
	}
	if (contain_space)
	{
		if (is_redirect_sign(**str))
		{
			print_err_msg(REDIRECT_SYNTAX_ERR, NULL, **str);
			return (REDIRECT_SYNTAX_ERR);
		}
		return (SUCCESS);
	}
	if (**str == 0)
	{
		print_err_msg(NEWLINE_SYNTAX_ERR, "newline", 0);
		return (NEWLINE_SYNTAX_ERR);
	}
	else if (is_redirect_sign(**str) && start_c != **str)
	{
		print_err_msg(REDIRECT_SYNTAX_ERR, NULL, **str);
		return (REDIRECT_SYNTAX_ERR);
	}
	else if (is_redirect_sign(**str) && start_c == **str)
	{
		// FIXME: duplicated logic
		(*str)++;
		if (**str == 0)
		{
			print_err_msg(NEWLINE_SYNTAX_ERR, "newline", 0);
			return (NEWLINE_SYNTAX_ERR);
		}
		else if (ft_isspace(**str))
		{
			skip_space(str);
			if (**str == 0)
			{
				print_err_msg(NEWLINE_SYNTAX_ERR, "newline", 0);
				return (NEWLINE_SYNTAX_ERR);
			}
			else if (!is_redirect_sign(**str) && ft_isprint(**str))
				return (SUCCESS);
		}
	}
	return (SUCCESS);
}

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

char		**line_parse(const char *line)
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

static char	*conv_env_var(const char **src, int str_idx, int *char_idx)
{
	// const char	*src_start;
	char			*env_key;
	char			*env_value;
	size_t			str_len;
	unsigned int	start_char_idx;

	// (*src)++;
	// src_start = *src;
	start_char_idx = *char_idx + 1;
	str_len = 0;
	while (src[str_idx][++(*char_idx)])
	{
		if (src[str_idx][*char_idx] == '"' ||\
			ft_isspace(src[str_idx][*char_idx]))
		{
			if (str_len == 0)
				return (ft_strdup("$"));
			env_key = ft_substr(src[str_idx], start_char_idx, str_len);
			env_value = get_env_variable((const char *)env_key);
			if (env_key)
				free(env_key);
			return (env_value);
		}
		else if (src[str_idx][*char_idx] == '\0')
		{
			print_err_msg(QUOTE_EXIT_ERR, "quote exit error", 0);
			return (NULL);
		}
		str_len++;
		// (*src)++;
	}
	return (NULL);
}

static char	*parse_quote_str(const char **src, char quote_char, int str_idx,\
				int *char_idx)
{
	char			*value;
	// const char	*src_start;
	char			*env_value;
	char			*temp;
	char			*substr;
	int				str_len;
	unsigned int	start_char_idx;

	value = NULL;
	// (*src)++;
	// src_start = *src;
	start_char_idx = *char_idx + 1;
	str_len = 0;
	while (src[str_idx][++(*char_idx)])
	{
		if (src[str_idx][*char_idx] == '$' && quote_char == '"')
		{
			env_value = conv_env_var(src, str_idx, char_idx);
			printf("env_value : %s\n", env_value);
			if (env_value != NULL)
			{
				if (value == NULL)
				{
					value = ft_substr(src[str_idx], start_char_idx, str_len);
					temp = ft_strjoin(value, env_value);
				}
				else
				{
					substr = ft_substr(src[str_idx], start_char_idx, str_len);
					temp = ft_strjoin(value, substr);
					free(value);
					free(substr);
					value = temp;
					temp = ft_strjoin(value, env_value);
				}
				free(value);
				value = temp;
				// free(env_value);
				// src_start = *src;
			}
			start_char_idx = *char_idx;
			str_len = 0;
			if (src[str_idx][*char_idx] == '\0')
				return (NULL);
		}
		if (src[str_idx][*char_idx] == '\0')
		{
			print_err_msg(QUOTE_EXIT_ERR, "quote exit error", 0);
			return (NULL);
		}
		else if (src[str_idx][*char_idx] == quote_char)
		{
			if (value == NULL)
				value = ft_substr(src[str_idx], start_char_idx, str_len);
			else
			{
				substr = ft_substr(src[str_idx], start_char_idx, str_len);
				temp = ft_strjoin(value, substr);
				free(value);
				free(substr);
				value = temp;
			}
			return (value);
		}
		str_len++;
		// (*src)++;
	}
	return (NULL);
}

// int		insert_str_to_parsed_data(char **parsed_data, char *str, int curr_parse_order)
// {
// 	if (curr_parse_order == COMMAND)
// 		parsed_data[COMMAND] = str;
// 	// else if (curr_parse_order == OPTION)
// 	return (0);
// }

// int		validate_option(char *str, int curr_parse_order)
// {
// 	return (0);
// }

// // TODO : parse redirect file name and skip space after file name
// char	**parse_redirect(const char **chunk, char **parsed_datas)
// {

// }

int			switch_str_to_handled_quote_str(char **splitted_data,\
				int str_idx)
{
	// FIXME: string variables should change structure type
	char	*converted_str;
	char	*prev_str;
	char	*next_str;
	char	*joined_str;
	char	*tmp_str;
	int		start_idx;
	int		char_idx;

	converted_str = NULL;
	prev_str = NULL;
	joined_str = NULL;
	start_idx = 0;
	char_idx = -1;
	while (splitted_data[str_idx][++char_idx])
	{
		if (is_quote(splitted_data[str_idx][char_idx]))
		{
			if (char_idx - start_idx > 0)
				prev_str = ft_substr(splitted_data[str_idx], start_idx,\
					char_idx - start_idx);
			converted_str = parse_quote_str((const char **)splitted_data,\
				splitted_data[str_idx][char_idx], str_idx, &char_idx);
			printf("parse_quote_str : %s\n", converted_str);
			start_idx = char_idx + 1;
			if (converted_str == NULL)
			{
				print_err_msg(QUOTE_EXIT_ERR, "quote exit error", 0);
				return (QUOTE_EXIT_ERR);
			}
			if (prev_str)
			{
				if (joined_str == NULL)
				{
					joined_str = ft_strjoin(prev_str, converted_str);
					free(prev_str);
					free(converted_str);
					prev_str = NULL;
					converted_str = NULL;
				}
				else
				{
					tmp_str = ft_strjoin(joined_str, prev_str);
					free(joined_str);
					free(prev_str);
					prev_str = NULL;
					joined_str = tmp_str;
					tmp_str = ft_strjoin(joined_str, converted_str);
					free(joined_str);
					free(converted_str);
					converted_str = NULL;
					joined_str = tmp_str;
				}
			}
			else
			{
				if (joined_str == NULL)
				{
					joined_str = converted_str;
				}
				else
				{
					tmp_str = ft_strjoin(joined_str, converted_str);
					free(joined_str);
					free(converted_str);
					converted_str = NULL;
					joined_str = tmp_str;
				}
			}
		}
		else if (splitted_data[str_idx][char_idx] == '$')
		{
			//TODO
			converted_str = conv_env_var((const char **)splitted_data, str_idx, &char_idx);
		}
	}
	if (joined_str)
	{
		if (char_idx - start_idx > 0)
		{
			next_str = ft_substr(splitted_data[str_idx], start_idx,\
						char_idx - start_idx);
			tmp_str = ft_strjoin(joined_str, next_str);
			free(joined_str);
			free(next_str);
			joined_str = tmp_str;
		}
		free(splitted_data[str_idx]);
		splitted_data[str_idx] = joined_str;
	}
	return (SUCCESS);
}

char		**cmd_chunk_parse(const char *chunk)
{
	// validate
	// 1. command path or name
	// 2. command arg
	// 3. redirect file exist
	char	**splitted_data;
	int		sd_idx;
	// char	**parsed_data;
	// int		curr_parse_order;

	// curr_parse_order = COMMAND;
	skip_space(&chunk);
	splitted_data = cmdline_split(chunk, " ");
	if (splitted_data == NULL)
		return (NULL);
	sd_idx = -1;
	while (splitted_data[++sd_idx])
	{
		switch_str_to_handled_quote_str(splitted_data, sd_idx);
	}
	return (splitted_data);
}

// char	*handle_quote(const char * line)
// {
// 	char	*quote_replaced_str;
// }

// parsed_chunk_data[0] : redirection set
// parsed_chunk_data[1] : cmd name
// parsed_chunk_data[2] : opt or arg
// parsed_chunk_data[~] : args