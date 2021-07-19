/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:26:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/19 16:35:01 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_env(t_env *envi, t_all *all)
{
	int	i;

	i = 1;
	if (!all->paths)
	{
		printf("minishell: env: No such file or directory\n");
		return ;
	}
	while (i < all->parse->count_r)
	{
		all->fd_iter++;
		i++;
	}
	dup_fd(all);
	while (envi)
	{
		if (ft_strchr(envi->value, '='))
			printf("%s\n", envi->value);
		envi = envi->next;
	}
	close_fd(all);
	g_exit_status = 0;
}
