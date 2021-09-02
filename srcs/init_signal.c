/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 09:30:46 by hekang            #+#    #+#             */
/*   Updated: 2021/09/02 11:46:13 by hekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_function(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	catch_function_in(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	do_nothing(int signo)
{
	(void)signo;
}

void	init_signal(void)
{
	rl_getc_function = custom_rl_getc_fuction;
	rl_catch_signals = 0;
	signal(SIGINT, catch_function);
	signal(SIGQUIT, do_nothing);
}

void	handle_exit_status(int exit_status)
{
	int	sig_num;

	sig_num = 0;
	if (WTERMSIG(exit_status) == SIGINT || WTERMSIG(exit_status) == SIGQUIT)
		sig_num = WTERMSIG(exit_status);
	if (sig_num == SIGINT)
		all()->end_code = 130;
	else if (sig_num == SIGQUIT)
	{
		write(1, "QUIT: 3\n", 8);
		all()->end_code = 131;
	}
	if (!WTERMSIG(exit_status))
		all()->end_code = WEXITSTATUS(exit_status);
}