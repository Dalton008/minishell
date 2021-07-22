/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:17:27 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/22 16:05:47 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_exit(char **split)
{
	int	n;

	n = 0;
	ft_putstr_fd("exit\n", 1);
	if (ft_splitlen(split) > 1)
	while (split[1][n])
	{
		if (!ft_isdigit(split[1][n]))
		{
			printf("\e[38;5;202mminishell: " "\x1b[0mexit: %s:"  "\x1b[0m numeric argument required\n", split[1]);
			g_exit_status = 255;
			exit(g_exit_status);
		}
		n++;
	}
	if (ft_splitlen(split) > 2)
	{
		printf("\e[38;5;202mminishell: "  "\x1b[0mexit: too many arguments\n");
		g_exit_status = 1;
		return ;
	}
	if (split[1])
		g_exit_status = ft_atoi(split[1]);
	exit(g_exit_status);
}
