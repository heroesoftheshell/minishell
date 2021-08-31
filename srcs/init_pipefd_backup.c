/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipefd_backup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 12:09:09 by hekang            #+#    #+#             */
/*   Updated: 2021/08/31 17:15:45 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipefd_backup(int *pipefd_backup)
{
	pipefd_backup[0] = dup(STDIN_FILENO);
	pipefd_backup[1] = dup(STDOUT_FILENO);
}
