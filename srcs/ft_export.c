/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:25:07 by hekang            #+#    #+#             */
/*   Updated: 2021/08/19 16:02:55 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_declare(void)
{
	
}

void	ft_export(char **cmd)
{
	// setenv(cmd[1], cmd[2], 1);
	// exit(0);

	if (cmd[1] == NULL)
	{
		export_declare();
	}
	else
	{
		ft_lstadd_back(&(all()->envp), ft_lstnew(cmd[1]));
	}
	
}