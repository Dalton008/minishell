/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:52:31 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/28 19:24:15 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_pwd(t_env *envi)
{
	while (envi)
	{
		if (ft_strncmp(envi->value, "PWD", 3) == 0)
		{
			printf("%s\n", envi->value + 4);
			break ;
		}
		envi = envi->next;
	}
}
