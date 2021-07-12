/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 11:21:49 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/11 19:17:15 by mjammie          ###   ########.fr       */
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
				all->f = 0;
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
	int		mfd[2];
	int		fd;
	t_parse	*head;
	char	*fname;

	i = 0;
	fd = 0;
	all->f = 0;
	head = all->parse;
	while (line[i])
	{
		fname = NULL;
		if (line[i] == '|')
		{
			pipe(mfd);
			all->pfd[i][1] = mfd[1];
			all->pfd[i + 1][0] = mfd[0];
		}
		if (line[i] == '>')
		{
			fname = get_file_name(all);
			if (line[i + 1] == '>')
			{
				fd = open(fname, O_CREAT | O_RDWR | O_APPEND, 0777);
				all->pfd[i][1] = fd;
				i++;
			}
			else
			{
				fd = open(fname, O_CREAT | O_RDWR | O_TRUNC, 0777);
				all->pfd[i][1] = fd;
			}
		}
		if (line[i] == '<')
		{
			fname = get_file_name(all);
			fd = open(fname, O_CREAT | O_RDWR, 0777);
			all->pfd[i][0] = fd;
		}
		i++;
	}
}
