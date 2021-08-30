/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:42:52 by hekang            #+#    #+#             */
/*   Updated: 2021/08/30 11:09:50 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	checkminus(int n, char *str)
{
	if (n == 0)
		str[0] = '0';
	else if (n < 0)
		str[0] = '-';
}

long	returnvalue(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	long	value;
	int		len;
	char	*str;

	len = 0;
	if (n < 1)
		len = 1;
	value = returnvalue(n);
	while (value != 0)
	{
		value = value / 10;
		len++;
	}
	str = (char *)malloc((len + 1) * sizeof(char));
	str[len] = '\0';
	value = returnvalue(n);
	while (len > 0)
	{
		str[len - 1] = value % 10 + '0';
		value = value / 10;
		len--;
	}
	checkminus(n, str);
	return (str);
}
