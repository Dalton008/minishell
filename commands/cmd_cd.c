/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 18:23:52 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/02 18:02:54 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_cd(t_env *envi, char *str)
{
	char	*oldpwd;
	t_env	*head;
	int		n;
	int		i;
	int		dir;

	n = 4;
	i = 0;
	head = envi;
	dir = chdir(str);
	if (dir == -1)
	{
		printf("No such file or directory\n");
		return ;
	}
	else
	{
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
				envi->value = ft_strjoin(envi->value, "/");
				envi->value = ft_strjoin(envi->value, str);
				break ;
			}
			envi = envi->next;
		}
	}
}
