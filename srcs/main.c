/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:22:47 by hekang            #+#    #+#             */
/*   Updated: 2021/07/06 12:42:31 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define READ 0
#define WRITE 1

int			main(void)
{
	char	*input;
	char	**line;
	int		cnt;
	pid_t	pid;
	int		pipefd[2];
	int		status;

	rl_bind_key('\t', rl_complete);
	pipe(pipefd);
	while (1)
	{
        input = readline("\033[1;4;34;47mHOS >\033[0m ");
		line = ft_split(input, '|');
		cnt = -1;
		while (line[++cnt])
		{
			pid = fork();
			// if (pid == 0) // child
			// {
			// 	// pipefd[2] = get_fd(line); //stdin stdout 관리
			// 	// execve() 명령어 실행
			// }
			wait(&status);
		}
	}
}