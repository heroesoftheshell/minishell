/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:24:08 by ghong             #+#    #+#             */
/*   Updated: 2021/07/29 15:10:35 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		validate_redirect_expression(const char **str, char start_c)
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

int		validate_cmd_chunk(const char *chunk)
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
		free((void *)line);
		exit(258);
	}
	// FIXME: parser should consider pipe sign in quote
	pipe_cmd_chunk = ft_split(line, '|');
	str_index = 0;
	while (pipe_cmd_chunk[str_index])
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

// int		set_parse_data(const char *chunk, char **alloc_space, int curr_parse_order)
// {
// 	return (SUCCESS);
// }

char	*conv_env_var(const char **src)
{
	const char	*src_start;
	char		*env_key;
	char		*env_value;
	size_t		str_len;

	(*src)++;
	src_start = *src;
	str_len = 0;
	while (**src)
	{
		if (**src == '"' || ft_isspace(**src))
		{
			env_key = ft_substr(src_start, 0, str_len);
			env_value = get_env_variable((const char *)env_key);
			if (env_key)
				free(env_key);
			return (env_value);
		}
		else if (**src == '\0')
		{
			print_err_msg(QUOTE_EXIT_ERR, "quote exit error", 0);
			return (NULL);
		}
		str_len++;
		(*src)++;
	}
	return (NULL);
}

char	*parse_quote_str(const char **src, char quote_char)
{
	char		*value;
	const char	*src_start;
	char		*env_value;
	char		*temp;
	char		*substr;
	int			str_len;

	value = NULL;
	(*src)++;
	src_start = *src;
	str_len = 0;
	while (**src)
	{
		if (**src == '$' && quote_char == '"')
		{
			env_value = conv_env_var(src);
			if (env_value != NULL)
			{
				if (value == NULL)
				{
					value = ft_substr(src_start, 0, str_len);
					temp = ft_strjoin(value, env_value);
				}
				else
				{
					substr = ft_substr(src_start, 0, str_len);
					temp = ft_strjoin(value, substr);
					free(value);
					free(substr);
					value = temp;
					temp = ft_strjoin(value, env_value);
				}
				free(value);
				value = temp;
				// free(env_value);
				src_start = *src;
				str_len = 0;
			}
			if (**src == '\0')
				return (NULL);
		}
		if (**src == '\0')
		{
			print_err_msg(QUOTE_EXIT_ERR, "quote exit error", 0);
			return (NULL);
		}
		else if (**src == quote_char)
		{
			if (value == NULL)
				value = ft_substr(src_start, 0, str_len);
			else
			{
				substr = ft_substr(src_start, 0, str_len);
				temp = ft_strjoin(value, substr);
				free(value);
				free(substr);
				value = temp;
			}
			return (value);
		}
		str_len++;
		(*src)++;
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

// int		parse_cmd(const char **str, char **parsed_datas)
// {
// 	const char	*src_start;
// 	char		*quote_str;
// 	char		*substr;
// 	char		*temp;
// 	int			str_len;

// 	src_start = *str;
// 	quote_str = NULL;
// 	substr = NULL;
// 	temp = NULL;
// 	str_len = 0;
// 	while(**str)
// 	{
// 		if (is_redirect_sign(**str))
// 		{
// 			parse_redirect(str, parsed_datas);
// 			if (str_len > 0)
// 				parsed_datas[COMMAND] = ft_substr(src_start, 0, str_len);
// 			else if (str_len == 0)
// 			{
// 				src_start = *str;
// 				str_len = 0;
// 			}
// 			continue;
// 		}
// 		else if (is_quote(**str))
// 		{
// 			quote_str = parse_quote_str(str, **str);
// 			if (str_len > 0)
// 			{
// 				substr = ft_substr(src_start, 0, str_len);
// 				if (parsed_datas[COMMAND] == NULL)
// 					parsed_datas[COMMAND] = ft_strjoin(substr, quote_str);
// 				else
// 				{
// 					ft_strjoin(temp, substr);
// 				}
// 				free(substr);
// 				free(quote_str);
// 				substr = NULL;
// 				quote_str = NULL;
// 				src_start = *str;
// 				str_len = 0;
// 				continue;
// 			}
// 		}
// 		else if (ft_isspace(**str))
// 		{

// 		}
// 		(*str)++;
// 		str_len++;
// 	}
// 	if (**str == '\0' && str_len > 0)
// 	{
// 		if (temp)
// 		{

// 		}
// 		else
// 		{

// 		}
// 	}
// }

// char	*parse_option(const char **chunk, char **parsed_datas)
// {

// }

// char	**parse_argv(const char **chunk, char **parsed_datas)
// {

// }

// // TODO : parse redirect file name and skip space after file name
// char	**parse_redirect(const char **chunk, char **parsed_datas)
// {

// }

char	**cmd_chunk_parse(const char *chunk)
{
	// validate
	// 1. command path or name
	// 2. command arg
	// 3. redirect file exist
	char	**parsed_data;
	char	*str_for_test;
	// int		curr_parse_order;

	parsed_data = (char **)ft_calloc(4, sizeof(char *));
	// curr_parse_order = COMMAND;
	if (parsed_data == NULL)
		return (NULL);
	skip_space(&chunk);
	while (*chunk)
	{
		// printf("%c\n", *chunk);
		if (is_quote(*chunk))
		{
			// TODO: handle quote(with space)
			str_for_test = parse_quote_str(&chunk, *chunk);
			if (str_for_test == NULL)
			{
				print_err_msg(QUOTE_EXIT_ERR, "quote exit error", 0);
				return (NULL);
			}
			printf("%s", str_for_test);
		}
		else if (is_hyphen(*chunk))
		{
			// TODO: parse option with cmd existance check
		}
		else if (is_redirect_sign(*chunk))
		{
			// TODO: join all redirects
		}
		else if (ft_isspace(*chunk))
		{
			// FIXME: arg order should not pass
			chunk++;
			continue;
		}
		//TODO: parse command or arg
		chunk++;
	}
	return (parsed_data);
}


int 	main()
{
	char	*line;
	char	**cmd_chunks;
	char	**parsed_chunk_data;
	int		chunk_idx;

	while (1)
	{
		line = readline("hosh$ ");
		cmd_chunks = line_parse((const char *)line);
		chunk_idx = 0;
		while (cmd_chunks[chunk_idx] != NULL)
		{
			// printf("%s\n", cmd_chunks[chunk_idx]);
			parsed_chunk_data = cmd_chunk_parse((const char *)cmd_chunks[chunk_idx]);
			if (parsed_chunk_data == NULL)
			{
				// perror("hosh: ");
				delete_split_strs(cmd_chunks);
				break ;
			}
			// TODO: process excute
			// ex 1) exec_func(const char ** parsed_chunk_data, char *envp);
			// ex 2) exec_func(const char *cmd, const char *arg, const char *redir, char *envp)
			delete_split_strs(parsed_chunk_data);
			chunk_idx++;
		}
		free(line);
	}
}
