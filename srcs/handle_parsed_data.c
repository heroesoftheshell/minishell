/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsed_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:26:35 by hekang            #+#    #+#             */
/*   Updated: 2021/08/31 17:19:14 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parsed_data(t_parse_data *parsed_data, char *next_chunk, \
		int *is_pipe, int *pipefd)
{
	if (next_chunk != NULL && *is_pipe != 1)
	{
		*is_pipe = 1;
		pipe(pipefd);
		first_pipe(parsed_data, all()->pid_list, pipefd);
	}
	else if (next_chunk != NULL && *is_pipe == 1)
		middle_pipe(parsed_data, all()->pid_list, pipefd);
	else if (*is_pipe)
	{
		last_pipe(parsed_data, all()->pid_list, pipefd);
		*is_pipe = 0;
	}
	else
		none_pipe(parsed_data);
	delete_parsed_data(parsed_data);
}
