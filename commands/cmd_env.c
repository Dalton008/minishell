/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:26:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/21 17:53:29 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_env(t_env *envi, t_all *all)
{
	int	i;

	i = 1;
	if (!all->paths)
	{
		printf("\e[38;5;202mminishell :" "\033[0menv: No such file or directory\n");
		return ;
	}
	// while (i < all->parse->count_r)
	// {
	// 	all->fd_iter_redir++;
	// 	i++;
	// }
	// dup_fd2(all);
	while (envi)
	{
		if (ft_strchr(envi->value, '='))
			printf("%s\n", envi->value);
		envi = envi->next;
	}
	// close(all->redirfd[0][1]);
	// close_fd2(all);
	g_exit_status = 0;
}
