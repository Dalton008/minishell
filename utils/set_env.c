/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 16:35:32 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/25 18:05:21 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_env(t_env *envi)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (list_len(envi) + 1));
	res[list_len(envi)] = NULL;
	i = 0;
	while (envi)
	{
		res[i] = ft_strdup(envi->value);
		i++;
		envi = envi->next;
	}
	return (res);
}
