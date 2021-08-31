/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 14:16:38 by hekang            #+#    #+#             */
/*   Updated: 2021/08/31 17:14:13 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	custom_rl_getc_fuction(FILE *stream)
{
	int				result;
	unsigned char	c;

	(void)stream;
	while (1)
	{
		result = read(rl_instream->_file, &c, sizeof(unsigned char));
		if (c == 4 && *rl_line_buffer == '\0')
		{
			rl_on_new_line();
			write(1, "exit", 4);
		}
		if (result == sizeof(unsigned char))
			return (c);
		if (result == 0)
			return (EOF);
	}
}
