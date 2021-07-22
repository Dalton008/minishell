/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 11:21:49 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/22 15:05:20 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_file_name(t_all *all)
{
	t_parse	*head;
	char	*fname;

	fname = NULL;
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

void	parse_fd(char *line, t_all *all)
{
	int		i;
	int		n;
	int		z;
	int		q;
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
