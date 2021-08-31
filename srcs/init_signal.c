/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekang <hekang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 09:30:46 by hekang            #+#    #+#             */
/*   Updated: 2021/08/31 17:15:29 by hekang           ###   ########.fr       */
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
