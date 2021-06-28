/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 18:23:52 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/28 19:08:03 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_cd(t_env *envi, char *str)
{
	char	*oldpwd;
	t_env	*head;
	int		n;
	int		i;

	n = 3;
	i = 0;
	head = envi;
	while (envi)
	{
		if (ft_strncmp(envi->value, "OLDPWD", 5) == 0)
		{
			oldpwd = ft_strdup(envi->value + 5);
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
	}
}
