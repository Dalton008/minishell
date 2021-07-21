/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 11:21:49 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/21 17:26:33 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*get_file_name(t_all *all)
{
	t_parse	*head;
	char	*fname;

	head = all->parse;
	if (head->files_name[all->f] != NULL)
	{
		fname = head->files_name[all->f];
		all->f++;
	}
	else
	{
		if (head->next != NULL)
		{
			while (head->files_name[all->f] == NULL)
			{
				head = head->next;
			}
			fname = head->files_name[all->f];
			all->f++;
		}
	}
	return (fname);
}

void	work_with_fd(char *line, t_all *all)
{
	int		i;
	int		n;
	int		z;
	int		q;
	int		mfd[2];
	int		fd;
	t_parse	*head;
	char	*fname;

	i = 0;
	n = 0;
	z = 0;
	fd = 0;
	q = 1;
	all->f = 0;
	head = all->parse;
	while (line[i])
	{
		if (line[i] == '"')
			q++;
		fname = NULL;
		if (line[i] == '|' && q % 2 != 0)
		{
			pipe(all->pfd[n]);
			n++;
		}
		if (line[i] == '>' && q % 2 != 0)
		{
			fname = get_file_name(all);	
			if (line[i + 1] == '>')
			{
				fd = open(fname, O_CREAT | O_RDWR | O_APPEND, 0777);
				all->redirfd[z][1] = fd;
				i++;
				z++;
			}
			else
			{
				fd = open(fname, O_CREAT | O_RDWR | O_TRUNC, 0777);
				all->redirfd[z][1] = fd;
				z++;
			}
		}
		if (line[i] == '<' && q % 2 != 0)
		{
			if (line[i + 1] == '<')
			{
				i = i + 2;
				continue ;
			}
			fname = get_file_name(all);
			fd = open(fname, O_CREAT | O_RDWR, 0777);
			all->redirfd[z][0] = fd;
			z++;
		}
		i++;
	}
}

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
