/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 22:31:24 by hekang            #+#    #+#             */
/*   Updated: 2021/08/30 11:04:08 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
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

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;

	if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 == NULL || s2 == NULL)
		return (1);
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
