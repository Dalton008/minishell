/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:17:27 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/23 20:06:47 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_nums(char *str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		if (!ft_isdigit(str[n]))
		{
			printf("\e[38;5;202mminishell: " "\x1b[0mexit: %s:" \
				"\x1b[0m numeric argument required\n", str);
			g_exit_status = 255;
			exit(g_exit_status);
		}
		n++;
	}
}

void	cmd_exit(char **split)
{
	int	n;

	n = 0;
	ft_putstr_fd("exit\n", 1);
	if (ft_splitlen(split) > 1)
		check_nums(split[1]);
	if (ft_splitlen(split) > 2)
	{
		printf("\e[38;5;202mminishell: " "\x1b[0mexit: too many arguments\n");
		g_exit_status = 1;
		return ;
	}
	if (split[1])
		g_exit_status = ft_atoi(split[1]);
	exit(g_exit_status);
}
