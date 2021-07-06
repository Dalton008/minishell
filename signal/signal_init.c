/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:31:36 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/06 21:34:32 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrlc(int val)
{
	int	pid;
	int	status;

	pid = waitpid(0, &status, WNOHANG);
	if (val == SIGINT)
	{
		write(1, "\n", 1);
		if (pid)
			write(1, "minishell> ", 11);
	}
	// (void)val;
	// write(1, "\nminishell> ", 12);
}

void	ctrld(int val)
{
	write(1, "exit\n", 5);
	exit(0);
}

void	signal_init(void)
{
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, ctrld);
}
