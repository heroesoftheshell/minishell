/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 22:31:24 by hekang            #+#    #+#             */
/*   Updated: 2021/07/29 17:37:52 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cnt;

	if (s1 == NULL && s2 == NULL)
		return (0);
	cnt = 0;
	while ((s1[cnt] || s2[cnt]) && cnt < n)
	{
		if (s1[cnt] != s2[cnt])
			return ((unsigned char)s1[cnt] - (unsigned char)s2[cnt]);
		cnt++;
	}
	return (0);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;
	// size_t	n;

	// n = ft_strlen(s1) + 1;
	if (s1 == NULL && s2 == NULL)
		return (0);
	while (1)
	{
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2)
			return ((unsigned char)c1 - (unsigned char)c2);
		if (!c1)
			break ;
	}
	return (0);
}
