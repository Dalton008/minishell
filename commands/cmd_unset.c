/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:37:25 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 19:26:43 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_unset(t_env *envi, char *key)
{
	t_env	*temp;
	t_env	*pred;
	int		i;

	i = 0;
	while (envi)
	{
		i = 0;
		while (envi->value[i] != '=')
			i++;
		if (ft_strncmp(envi->value, key, i) == 0)
		{
			temp = envi;
			envi = envi->next;
			pred->next = envi;
			free(temp->value);
			free(temp);
			break ;
		}
		pred = envi;
		envi = envi->next;
	}
	g_exit_status = 0;
}
