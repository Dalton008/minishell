/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 17:11:23 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/29 18:40:10 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cmd_echo(int argc, char **argv, t_env *envi)
{
	t_env	*head;
	int		i;
	int		n;
	int		key_len;
	int		cmd_not_found;

	i = 0;
	head = envi;
	key_len = 0;
	if (argc == 1)
		printf("\n");
	else
	{
		if (ft_strcmp(argv[1], "-n") == 0)
		{
			i = 2;
			while (argv[i])
			{
				envi = head;
				if (argv[i][0] == '$')
				{
					if (!argv[i][1])
					{
						printf("$");
					}
					else
					{
						while (envi)
						{
							key_len = ft_strlen(argv[i] + 1);
							if (ft_strncmp((argv[i] + 1), envi->value, key_len) == 0)
							{
								printf("%s", envi->value + key_len + 1);
								if (argv[i + 1] != 0)
									printf(" ");
							}
							envi = envi->next;
						}
					}
				}
				else
				{
					printf("%s", argv[i]);
					if (argv[i + 1] != 0)
						printf(" ");
				}
				i++;
			}
		}
		else
		{
			i = 1;
			while (argv[i])
			{
				envi = head;
				if (argv[i][0] == '$')
				{
					if (!argv[i][1])
					{
						printf("$\n");
					}
					else
					{
						cmd_not_found = 1;
						while (envi)
						{
							key_len = ft_strlen(argv[i] + 1);
							if (ft_strncmp((argv[i] + 1), envi->value, key_len) == 0)
							{
								cmd_not_found = 0;
								printf("%s\n", envi->value + key_len + 1);
							}
							envi = envi->next;
						}
						if (cmd_not_found)
							printf("\n");
					}
				}
				else
				{
					printf("%s\n", argv[i]);
				}
				i++;
			}
		}
	}
	return (0);
}
