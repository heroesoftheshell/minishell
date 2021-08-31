/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:30:52 by hekang            #+#    #+#             */
/*   Updated: 2021/08/31 17:12:47 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_std(int pipe, int pipe2)
{
	dup2(pipe, STDIN_FILENO);
	dup2(pipe2, STDOUT_FILENO);
}

void	close_both(int pipefd, int pipefd2)
{
	close(pipefd);
	close(pipefd2);
}
