/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 00:39:26 by hekang            #+#    #+#             */
/*   Updated: 2021/03/18 11:26:37 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *str;

	if (!(str = (void *)malloc(count * size)))
	{
		write(1, "Error\n ** Malloc Error **\n", 26);
		exit(EXIT_SUCCESS);
	}
	if (str == 0)
		return (0);
	ft_memset(str, 0, count * size);
	return (str);
}
