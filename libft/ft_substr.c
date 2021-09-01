/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 22:18:23 by hekang            #+#    #+#             */
/*   Updated: 2021/09/01 16:21:12 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	cnt;
	char	*result;

	if (s == 0)
		return (NULL);
	cnt = 0;
	result = (char *)ft_calloc(len + 1, sizeof(char));
	while ((cnt < len) && (cnt + start < ft_strlen(s)))
	{
		result[cnt] = s[cnt + start];
		cnt++;
	}
	result[cnt] = '\0';
	return (result);
}
