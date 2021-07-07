/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:24:08 by ghong             #+#    #+#             */
/*   Updated: 2021/07/06 17:55:46 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_split_strs(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	skip_space(const char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}

int		is_redirect_sign(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

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
			print_parse_err(NEWLINE_SYNTAX_ERR, 0);
			return (NEWLINE_SYNTAX_ERR);
		}
	}
	if (contain_space)
	{
		if (is_redirect_sign(**str))
		{
			print_parse_err(REDIRECT_SYNTAX_ERR, **str);
			return (REDIRECT_SYNTAX_ERR);
		}
		return (SUCCESS);
	}
	if (**str == 0)
	{
		print_parse_err(NEWLINE_SYNTAX_ERR, 0);
		return (NEWLINE_SYNTAX_ERR);
	}
	else if (is_redirect_sign(**str) && start_c != **str)
	{
		print_parse_err(REDIRECT_SYNTAX_ERR, **str);
		return (REDIRECT_SYNTAX_ERR);
	}
	else if (is_redirect_sign(**str) && start_c == **str)
	{
		// FIXME: duplicated logic
		(*str)++;
		if (**str == 0)
		{
			print_parse_err(NEWLINE_SYNTAX_ERR, 0);
			return (NEWLINE_SYNTAX_ERR);
		}
		else if (ft_isspace(**str))
		{
			skip_space(str);
			if (**str == 0)
			{
				print_parse_err(NEWLINE_SYNTAX_ERR, 0);
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
		print_parse_err(PIPE_SYNTAX_ERR, *line);
		free((void *)line);
		exit(258);
	}
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

int		is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int		is_hyphen(char c)
{
	if (c == '-')
		return (1);
	return (0);
}

// int		set_parse_data(const char *chunk, char **alloc_space, int curr_parse_order)
// {
// 	return (SUCCESS);
// }

char	**cmd_chunk_parse(const char *chunk)
{
	// validate
	// 1. command path or name
	// 2. command arg
	// 3. redirect file exist
	char	**parsed_data;
	// int		curr_parse_order;

	parsed_data = (char **)ft_calloc(4, sizeof(char *));
	// curr_parse_order = COMMAND;
	if (parsed_data == NULL)
		return (NULL);
	while (*chunk)
	{
		// printf("%c\n", *chunk);
		if (is_quote(*chunk))
		{
			// TODO: handle quote(with space)
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
	return (SUCCESS);
}

int 	main()
{
	char	*line;
	char	**cmd_chunks;

	while (1)
	{
		line = readline("hosh$ ");
		cmd_chunks = line_parse((const char *)line);
		while (cmd_chunks != NULL)
		{
			// excute
			printf("%s\n", *cmd_chunks);
			cmd_chunk_parse((const char *)*cmd_chunks);
			// delete_split_strs(cmd_chunks);
			cmd_chunks++;
		}
		free(line);
	}
}
