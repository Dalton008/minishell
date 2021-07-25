/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:29:19 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/23 20:08:37 by mjammie          ###   ########.fr       */
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

void	ctrlc_in_other(int val)
{
	(void)val;
	g_exit_status = 130;
	printf("\n");
}

void	ctrlsl_in_other(int val)
{
	(void)val;
	g_exit_status = 131;
	printf("Quit: 3\n");
}
