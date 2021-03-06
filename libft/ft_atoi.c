/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 10:54:04 by hekang            #+#    #+#             */
/*   Updated: 2021/08/30 10:54:33 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_digit(const char *str)
{
	int	cnt;
	int	i;
	int	minus;

	cnt = 0;
	i = 0;
	minus = 1;
	while (str[cnt] == ' ' || str[cnt] == '\t' || str[cnt] == '\n' || \
			str[cnt] == '\v' || str[cnt] == '\f' || str[cnt] == '\r')
		cnt++;
	if (str[cnt] == '+' || str[cnt] == '-')
	{
		if (str[cnt] == '-')
			minus = -1;
		cnt++;
	}
	while (str[cnt + i])
	{
		if (str[cnt + i] >= '0' && str[cnt + i] <= '9')
			i++;
		else
			break ;
	}
	return (i * minus);
}

int	ft_atoi(const char *str)
{
	int					cnt;
	unsigned long int	result;
	int					minus;

	if (check_digit(str) >= 20 || check_digit(str) <= -20)
		return (-1);
	cnt = 0;
	minus = 1;
	result = 0;
	while (str[cnt] == ' ' || str[cnt] == '\t' || str[cnt] == '\n' || \
		str[cnt] == '\v' || str[cnt] == '\f' || str[cnt] == '\r')
		cnt++;
	if (str[cnt] == '+' || str[cnt] == '-')
	{
		if (str[cnt] == '-')
			minus = -1;
		cnt++;
	}
	while (str[cnt] >= '0' && str[cnt] <= '9')
	{
		result = result * 10 + str[cnt] - '0';
		cnt++;
	}
	return (result * minus);
}
