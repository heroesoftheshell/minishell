/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:24:08 by ghong             #+#    #+#             */
/*   Updated: 2021/08/23 08:45:41 by ghong            ###   ########.fr       */
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

static char	*conv_env_var(const char **src, int str_idx, int *char_idx,\
	bool is_inside_quote)
{
	char			*env_key;
	char			*env_value;
	size_t			str_len;
	unsigned int	start_char_idx;

	start_char_idx = *char_idx + 1;
	str_len = 0;
	// FIXME: LOGIC ERROR
	while (src[str_idx][++(*char_idx)])
	{
		if (is_inside_quote)
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
		}
		else
		{
			if (ft_isspace(src[str_idx][*char_idx]) ||\
				src[str_idx][*char_idx] == '\0')
			{
				if (str_len == 0)
					return (ft_strdup("$"));
				env_key = ft_substr(src[str_idx], start_char_idx, str_len);
				env_value = get_env_variable((const char *)env_key);
				if (env_key)
					free(env_key);
				return (env_value);
			}
		}
		str_len++;
	}
	return (NULL);
}

static char	*parse_quote_str(const char **src, char quote_char, int str_idx,\
				int *char_idx)
{
	char			*converted_str;
	char			*env_value;
	char			*substr;
	char			*joined_str;
	int				str_len;
	unsigned int	start_char_idx;

	converted_str = NULL;
	joined_str = NULL;
	start_char_idx = *char_idx + 1;
	str_len = 0;
	while (src[str_idx][++(*char_idx)])
	{
		if (src[str_idx][*char_idx] == '$' && quote_char == '"')
		{
			if (*char_idx - start_char_idx > 0)
			{
				if (converted_str == NULL)
					converted_str = ft_substr(src[str_idx], start_char_idx,\
						*char_idx - start_char_idx);
				else
				{
					substr = ft_substr(src[str_idx], start_char_idx,\
						*char_idx - start_char_idx);
					joined_str = ft_strjoin(converted_str, substr);
					free(converted_str);
					free(substr);
					converted_str = joined_str;
					substr = NULL;
					joined_str = NULL;
				}
			}
			env_value = conv_env_var(src, str_idx, char_idx, true);
			// printf("converted_str : %s, env_value : %s\n", converted_str, env_value);
			if (env_value != NULL)
			{
				if (converted_str == NULL)
				{
					converted_str = env_value;
				}
				else
				{
					joined_str = ft_strjoin(converted_str, env_value);
					free(converted_str);
					free(env_value);
					converted_str = joined_str;
				}
			}
			start_char_idx = *char_idx;
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
			if (converted_str == NULL)
			{
				converted_str = ft_substr(src[str_idx], start_char_idx,\
					*char_idx - start_char_idx);
			}
			else
			{
				substr = ft_substr(src[str_idx], start_char_idx,\
					*char_idx - start_char_idx);
				joined_str = ft_strjoin(converted_str, substr);
				free(converted_str);
				free(substr);
				converted_str = joined_str;
			}
			return (converted_str);
		}
		str_len++;
	}
	return (NULL);
}

int			switch_str_to_handled_quote_str(char **splitted_data,\
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
			substr = ft_substr(splitted_data[str_idx], start_idx,\
						char_idx - start_idx);
			quote_str = parse_quote_str((const char **)splitted_data,\
					splitted_data[str_idx][char_idx], str_idx, &char_idx);
			if (quote_str == NULL)
			{
				free(substr);
				if (converted_str)
					free(converted_str);
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
			substr = ft_substr(splitted_data[str_idx], start_idx,\
					char_idx - start_idx);
			if (converted_str)
			{
				joined_str = ft_strjoin(converted_str, substr);
				free(converted_str);
				free(substr);
				substr = conv_env_var((const char **)splitted_data, str_idx, &char_idx, false);
				if (substr)
				{
					converted_str = ft_strjoin(joined_str, substr);
					free(joined_str);
					free(substr);
				}
			}
			else
			{
				converted_str = conv_env_var((const char **)splitted_data, str_idx, &char_idx, false);
				printf("%s\n", converted_str);
				if (converted_str == NULL)
					converted_str = ft_strdup("\0");
			}
			start_idx = char_idx;
		}
	}
	if (converted_str)
	{
		substr = ft_substr(splitted_data[str_idx], start_idx,\
				char_idx - start_idx);
		joined_str = ft_strjoin(converted_str, substr);
		free(converted_str);
		free(substr);
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

// parsed_chunk_data[0] : redirection set
// parsed_chunk_data[1] : cmd name
// parsed_chunk_data[2] : opt or arg
// parsed_chunk_data[~] : args