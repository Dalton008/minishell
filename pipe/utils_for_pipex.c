/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_pipex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 20:02:55 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/25 13:34:42 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_for_redir(t_all *all)
{
	int	m;

	m = 1;
	while (m < all->parse->count_r)
	{
		all->fd_iter_redir++;
		m++;
	}
	if (all->parse->count_r > 0)
		dup_fd2(all);
}

void	wait_and_close(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->count_pipe + 1)
	{
		waitpid(all->pid[i], NULL, 0);
		i++;
	}
	close(all->pfd[0][0]);
	close(all->pfd[0][1]);
	close(all->pfd[1][0]);
	close(all->pfd[1][1]);
}
