/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:31:36 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/22 16:21:43 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_sigint(int val)
{
	(void)val;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_d_hook(void)
{
	ft_putstr_fd("\e[1A\e[12C" "exit\n", 1);
	exit (g_exit_status);
}

void	signal_init(void)
{
	signal(SIGINT, my_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

static void	my_new(int val)
{
	(void)val;
	g_exit_status = 130;
	printf("\n");
}

static void	my_new2(int val)
{
	(void)val;
	g_exit_status = 131;
	printf("Quit: 3\n");
}

void	signal_init_for_child(void)
{
	signal(SIGINT, my_new);
	signal(SIGQUIT, my_new2);
	signal(SIGTSTP, SIG_IGN);
}
