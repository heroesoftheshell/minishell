/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:35:45 by hekang            #+#    #+#             */
/*   Updated: 2021/07/05 15:37:55 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_readline();

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	while (1)
	{
		ft_readline();
	}
}