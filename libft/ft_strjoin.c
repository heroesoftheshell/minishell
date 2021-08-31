/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 22:25:07 by hekang            #+#    #+#             */
/*   Updated: 2021/08/31 12:17:26 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_a(char *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*str;

	if (s1 == 0 || s2 == 0)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!str)
		return (0);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2 + 1);
	free(s1);
	return (str);
}

static void	handle_free(char *s1, char *s2, int free_mode)
{
	if (free_mode == FREE_ALL)
	{
		free(s1);
		free(s2);
	}
	else if (free_mode == FREE_FIRST_ARG)
		free(s1);
	else if (free_mode == FREE_SECOND_ARG)
		free(s2);
}

char	*ft_strjoin_with_free(char *s1, char *s2, int free_mode)
{
	int		len1;
	int		len2;
	char	*str;

	if (s1 == 0 || s2 == 0)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!str)
		return (0);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2 + 1);
	handle_free(s1, s2, free_mode);
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*str;

	if (s1 == 0 || s2 == 0)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!str)
		return (0);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2 + 1);
	return (str);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	int		len1;
	int		len2;
	int		len3;
	char	*str;

	if (s1 == 0 || s2 == 0 || s3 == 0)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	str = ft_calloc(len1 + len2 + len3 + 1, sizeof(char));
	if (!str)
		return (0);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	ft_memcpy(str + len1 + len2, s3, len3 + 1);
	return (str);
}
