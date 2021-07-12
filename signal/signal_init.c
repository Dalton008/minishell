/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:31:36 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/12 20:42:16 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_sigint(int val)
{
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
	exit (1);
}

void	signal_init(void)
{
	signal(SIGINT, my_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
