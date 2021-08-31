/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_str_to_handled_quote_str.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:08:49 by ghong             #+#    #+#             */
/*   Updated: 2021/08/31 17:20:35 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quote(char **splitted_data, int str_idx, int start_idx, \
				int char_idx)
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

// int	switch_str_to_handled_quote_str(char **splitted_data, \
// 				int str_idx)
// {
// 	// FIXME: string variables should change structure type
// 	char	*converted_str;
// 	char	*quote_str;
// 	char	*substr;
// 	char	*joined_str;
// 	int		start_idx;
// 	int		char_idx;

// 	converted_str = NULL;
// 	joined_str = NULL;
// 	start_idx = 0;
// 	char_idx = -1;
// 	while (splitted_data[str_idx][++char_idx])
// 	{
// 		if (is_quote(splitted_data[str_idx][char_idx]))
// 		{
// 			substr = ft_substr(splitted_data[str_idx], start_idx, \
// 						char_idx - start_idx);
// 			quote_str = parse_quote_str((const char **)splitted_data, \
// 					splitted_data[str_idx][char_idx], str_idx, &char_idx);
// 			if (quote_str == NULL)
// 			{
// 				free(substr);
// 				if (converted_str)
// 					free(converted_str);
// 				print_err_msg(QUOTE_EXIT_ERR, "quote exit error", 0);
// 				return (QUOTE_EXIT_ERR);
// 			}
// 			if (converted_str == NULL)
// 				converted_str = ft_strjoin(substr, quote_str);
// 			else
// 			{
// 				joined_str = ft_strjoin(converted_str, substr);
// 				free(converted_str);
// 				free(substr);
// 				converted_str = ft_strjoin(joined_str, quote_str);
// 				free(joined_str);
// 				free(quote_str);
// 			}
// 			start_idx = char_idx + 1;
// 		}
// 		else if (splitted_data[str_idx][char_idx] == '$')
// 		{
// 			substr = ft_substr(splitted_data[str_idx], start_idx, \
// 					char_idx - start_idx);
// 			if (converted_str)
// 			{
// 				joined_str = ft_strjoin(converted_str, substr);
// 				free(converted_str);
// 				free(substr);
// 				substr = conv_env_var((const char **)splitted_data, \
// 					str_idx, &char_idx, false);
// 				if (substr)
// 				{
// 					converted_str = ft_strjoin(joined_str, substr);
// 					free(joined_str);
// 					free(substr);
// 				}
// 				else
// 				{
// 					converted_str = joined_str;
// 				}
// 			}
// 			else
// 			{
// 				converted_str = conv_env_var((const char **)splitted_data, \
// 					str_idx, &char_idx, false);
// 				if (converted_str == NULL)
// 					converted_str = ft_strdup("\0");
// 				joined_str = ft_strjoin(substr, converted_str);
// 				free(substr);
// 				free(converted_str);
// 				converted_str = joined_str;
// 			}
// 			start_idx = char_idx + 1;
// 		}
// 	}
// 	if (converted_str)
// 	{
// 		substr = ft_substr(splitted_data[str_idx], start_idx, \
// 				char_idx - start_idx);
// 		joined_str = ft_strjoin(converted_str, substr);
// 		free(converted_str);
// 		free(substr);
// 		free(splitted_data[str_idx]);
// 		splitted_data[str_idx] = joined_str;
// 	}
// 	return (SUCCESS);
// }