/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 15:08:18 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/25 18:03:37 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_fd2(t_all *all)
{
	all->tm_fd1 = dup(1);
	all->tm_fd0 = dup(0);
	dup2(all->redirfd[all->fd_iter_redir][0], 0);
	dup2(all->redirfd[all->fd_iter_redir][1], 1);
}

void	close_fd2(t_all *all)
{
	if (all->redirfd[all->fd_iter_redir][0] != 0)
	{
		close(all->redirfd[all->fd_iter_redir][0]);
	}
	if (all->redirfd[all->fd_iter_redir][1] != 1)
	{
		close(all->redirfd[all->fd_iter_redir][1]);
	}
	dup2(all->tm_fd1, 1);
	dup2(all->tm_fd0, 0);
}

void	dup_fd(t_all *all)
{
	all->tm_fd1 = dup(1);
	all->tm_fd0 = dup(0);
	dup2(all->pfd[all->fd_iter][0], 0);
	dup2(all->pfd[all->fd_iter][1], 1);
}

void	close_fd(t_all *all)
{
	if (all->pfd[all->fd_iter][0] != 0)
	{
		close(all->pfd[all->fd_iter][0]);
	}
	if (all->pfd[all->fd_iter][1] != 1)
	{
		close(all->pfd[all->fd_iter][1]);
	}
	dup2(all->tm_fd1, 1);
	dup2(all->tm_fd0, 0);
}
