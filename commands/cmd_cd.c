/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 18:23:52 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/29 18:45:51 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_cd(t_env *envi, char *str)
{
	char	*oldpwd;
	t_env	*head;
	int		n;
	int		i;
	DIR		*dir;

	n = 4;
	i = 0;
	head = envi;
	dir = opendir(str);
	if (dir == 0)
	{
		printf("No such file or directory\n");
		return ;
	}
	else
	{
		closedir(dir);
		while (envi)
		{
			if (ft_strncmp(envi->value, "OLDPWD", 6) == 0)
			{
				oldpwd = ft_strdup(envi->value + 7);
				break ;
			}
			envi = envi->next;
		}
		envi = head;
		while (envi)
		{
			if (ft_strncmp(envi->value, "PWD", 3) == 0)
			{
				while (str[i])
				{
					envi->value[n] = str[i];
					i++;
					n++;
				}
				envi->value[n] = '\0';
			}
			envi = envi->next;
		}
	}
}
