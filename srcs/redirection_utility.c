/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utility.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:03:10 by ghong             #+#    #+#             */
/*   Updated: 2021/09/08 17:25:50 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_heredoc(char *str)
{
	if (str == NULL)
		return (false);
	return (str[0] == '<' && str[1] == '<');
}

static void	handle_heredoc(char *delimiter, t_parse_data *p_data)
{
	int	fd;

	fd = open("./temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	exec_heredoc(fd, delimiter, all()->pipefd_backup[0]);
	close(fd);
	fd = open("./temp", O_RDONLY, 0644);
	if (ft_strcmp(p_data->last_in_fname, delimiter) == 0)
		dup2(fd, STDIN_FILENO);
	close(fd);
	clear_temp(true);
}

void	catch_heredoc(char **sp_data, t_parse_data *p_data)
{
	int	idx;

	idx = -1;
	while (sp_data[++idx])
	{
		if (is_heredoc(sp_data[idx]))
			handle_heredoc(&sp_data[idx][2], p_data);
	}
}
