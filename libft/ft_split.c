/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:23:51 by hekang            #+#    #+#             */
/*   Updated: 2021/09/01 17:02:02 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnum(char *s, char c)
{
	size_t	i;
	size_t	num;

	num = 0;
	i = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			num++;
		}
		else
			i++;
	}
	return (num);
}

void	str_malloc_copy(char *s, char c, size_t num, char **res)
{
	size_t	x;
	size_t	i;
	size_t	len;

	i = 0;
	x = 0;
	while (s[i] && x < num)
	{
		len = 0;
		if (s[i] != c)
		{
			while (s[i + len] != c && s[i + len])
				len++;
			res[x] = ft_calloc(sizeof(char), len + 1);
			ft_strlcpy(res[x++], s + i, len + 1);
		}
		if (len == 0)
			len++;
		i += len;
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	num;
	char	**res;

	if (s == 0)
		return (0);
	num = ft_strnum((char *)s, c);
	res = ft_calloc(sizeof(char *), num + 1);
	if (res == 0)
		return (0);
	str_malloc_copy((char *)s, c, num, res);
	res[num] = 0;
	return (res);
}
