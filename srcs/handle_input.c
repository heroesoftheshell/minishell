/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:36:28 by hekang            #+#    #+#             */
/*   Updated: 2021/09/09 11:11:52 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input(char *input)
{
	char			**cmd_chunks;
	int				chunk_idx;
	t_parse_data	*parsed_data;
	int				is_pipe;
	int				pipefd[2];

	ft_bzero(all()->pid_list, BUFSIZ);
	all()->pid_list[0] = 1;
	signal(SIGINT, catch_function_in);
	cmd_chunks = line_parse((const char *)input);
	chunk_idx = -1;
	is_pipe = 0;
	while (cmd_chunks && cmd_chunks[++chunk_idx] != NULL)
	{
		parsed_data = cmd_chunk_parse((const char *)cmd_chunks[chunk_idx]);
		if (parsed_data != NULL)
			handle_parsed_data(parsed_data, cmd_chunks[chunk_idx + 1], \
			&is_pipe, pipefd);
	}
	delete_split_strs(cmd_chunks);
	if (input[0])
		add_history(input);
	signal(SIGINT, catch_function);
	free(input);
}
