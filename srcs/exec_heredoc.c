/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghong <ghong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:47:39 by ghong             #+#    #+#             */
/*   Updated: 2021/09/01 17:03:30 by ghong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc(char *joined_str, int fd)
{
	write(fd, joined_str, ft_strlen(joined_str));
	if (joined_str)
	{
		write(fd, "\n", 1);
		free(joined_str);
	}
}

int	exec_heredoc(int fd, const char *delimiter, int stdin_fd)
{
	char	*input;
	char	*joined_str;

	joined_str = NULL;
	dup2(stdin_fd, STDIN_FILENO);
	while (1)
	{
		input = readline("\033[1;4;34;47m>\033[0m ");
		if (ft_strcmp(input, delimiter) == 0)
		{
			write_heredoc(joined_str, fd);
			free(input);
			break ;
		}
		else
		{
			if (joined_str)
				joined_str = substr_join3(joined_str, ft_strdup("\n"), input);
			else
				joined_str = input;
		}
	}
	return (SUCCESS);
}
