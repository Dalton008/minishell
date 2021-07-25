/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:05:27 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 22:52:11 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_path(t_env *envi, t_all *all)
{
	while (envi)
	{
		if ((ft_strncmp(envi->value, "PATH=", 5)) == 0)
		{
			all->paths = ft_split(envi->value + 5, ':');
			break ;
		}
		envi = envi->next;
	}
}
