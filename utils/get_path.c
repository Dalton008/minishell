/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:05:27 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/13 14:05:52 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(t_env *envi)
{
	char	**path;

	while (envi)
	{
		if ((ft_strncmp(envi->value, "PATH=", 5)) == 0)
			path = ft_split(envi->value + 5, ':');
		envi = envi->next;
	}
	return (path);
}
