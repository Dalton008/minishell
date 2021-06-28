/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 17:11:23 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/28 21:26:56 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cmd_echo(int argc, char **argv, t_env *envi)
{
	t_env	*head;
	int		i;
	int		key_len;

	i = 0;
	head = envi;
	key_len = 0;
	if (argc == 1)
		printf("\n");
	else if (argc == 2)
	{
		if (argv[1][0] == '$')
		{
			while (envi)
			{
				key_len = ft_strlen(argv[1] + 1);
				if (ft_strncmp((argv[1] + 1), envi->value, key_len) == 0)
				{
					printf("%s\n", envi->value + key_len + 1);
					break ;
				}
				envi = envi->next;
			}
			if (!envi)
				printf("\n");
		}
		else
			printf("%s\n", argv[1]);
	}
	else if (argc >= 3)
	{
		if (ft_strcmp(argv[1], "-n") == 0)
		{
			printf("%s", argv[2]);
		}
		else
		{
			i = 1;
			while (argv[i])
			{
				if (argv[i][0] == '$')
				{
					while (envi)
					{
						key_len = ft_strlen(argv[1] + 1);
						if (ft_strncmp((argv[1] + 1), envi->value, key_len) == 0)
						{
							printf("%s\n", envi->value + key_len + 1);
							break ;
						}
						envi = envi->next;
					}
					if (!envi)
						printf("%s ", argv[i++]);
				}
			}
		}
	}
	return (0);
}
