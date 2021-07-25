/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 17:11:23 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/23 20:06:44 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	without_n(char **argv)
{
	int		i;

	i = 0;
	i = 2;
	while (argv[i] && !ft_strchr("<>", argv[i][0]))
	{
		if (ft_strcmp(argv[i], "-n") != 0)
			printf("%s", argv[i]);
		if (argv[i + 1] != 0 && !ft_strchr("<>", argv[i + 1][0]) \
			&& ft_strcmp(argv[i], "-n") != 0)
			printf(" ");
		i++;
	}
}

void	cmd_echo(int argc, char **argv)
{
	int		i;

	i = 0;
	if (argc == 1)
		printf("\n");
	else
	{
		if (ft_strcmp(argv[1], "-n") == 0)
			without_n(argv);
		else
		{
			i = 1;
			while (argv[i] && !ft_strchr("<>", argv[i][0]))
			{
				printf("%s ", argv[i]);
				i++;
			}
			printf("\n");
		}
	}
	g_exit_status = 0;
}
