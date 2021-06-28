/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:37:25 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/28 14:52:51 by mjammie          ###   ########.fr       */
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
			free(envi->value);
			envi->value = NULL;
			temp = envi->next;
			envi = pred;
			envi->next = temp;
			free(temp);
		}
		pred = envi;
		envi = envi->next;
	}
}
