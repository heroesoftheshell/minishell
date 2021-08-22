/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 21:00:26 by ghong             #+#    #+#             */
/*   Updated: 2021/08/23 08:41:23 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int		is_delimiter(char c, char *delimiter)
{
	if (ft_strchr((const char *)delimiter, c) == NULL)
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

static size_t	count_word(char	const *s, char *delimeter)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] != '\0' && is_delimiter(s[i], delimeter))
			i++;
		if (s[i] == '\0')
			return (count);
		count++;
		while (s[i] != '\0' && !is_delimiter(s[i], delimeter))
		{
			skip_quote(s, &i, NULL);
			i++;
		}
	}
	return (count);
}

static void		delete_words(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_bzero(arr[i], ft_strlen(arr[i]));
		free(arr[i]);
		i++;
	}
}

static int		insert_words(char **arr, char const *s, char *c)
{
	size_t	word_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	word_len = 0;
	while (s[i])
	{
		while (s[i] != '\0' && is_delimiter(s[i], c))
			i++;
		if (s[i] == '\0')
			return (1);
		while (s[i] != '\0' && !is_delimiter(s[i], c))
		{
			skip_quote(s, &i, &word_len);
			word_len++;
			i++;
		}
		if ((arr[j++] = ft_substr(s, i - word_len, word_len)) == NULL)
			return (0);
		word_len = 0;
	}
	return (1);
}

char			**cmdline_split(char const *s, char *delimeter)
{
	char	**split_arr;
	size_t	words_count;

	if (s == NULL)
		return (NULL);
	words_count = count_word(s, delimeter);
	split_arr = (char **)ft_calloc(words_count + 1, sizeof(char *));
	if (split_arr == NULL)
		return (NULL);
	if (words_count == 0)
	{
		*split_arr = NULL;
		return (split_arr);
	}
	if (insert_words(split_arr, s, delimeter) == 0)
	{
		delete_words(split_arr);
		free(split_arr);
		return (NULL);
	}
	split_arr[words_count] = NULL;
	return (split_arr);
}
