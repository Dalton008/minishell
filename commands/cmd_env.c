/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:26:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/29 12:17:59 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_env(t_env *envi)
{
	while (envi)
	{
		if (ft_strchr(envi->value, '='))
			printf("%s\n", envi->value);
		envi = envi->next;
	}
}
