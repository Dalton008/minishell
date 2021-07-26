/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:46:29 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/26 16:31:02 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_file(char *line, int i, int q, t_all *all)
{
	if (line[i] == '>' && q % 2 != 0)
	{
		if (line[i + 1] == '>')
		{
			all->redirfd[all->f++][1] = open(all->files_name[all->f], \
				O_CREAT | O_RDWR | O_APPEND, 0777);
			i++;
		}
		else
			all->redirfd[all->f++][1] = open(all->files_name[all->f], \
				O_CREAT | O_RDWR | O_TRUNC, 0777);
	}
}

void	parse_fd(char *line, t_all *all)
{
	int		i;
	int		n;
	int		q;

	i = -1;
	n = 0;
	q = 1;
	while (line[++i])
	{
		if (line[i] == '"')
			q++;
		if (line[i] == '|' && q % 2 != 0)
			pipe(all->pfd[n++]);
		open_file(line, i, q, all);
		if (line[i] == '<' && q % 2 != 0)
		{
			if (line[i + 1] == '<')
			{
				i = i + 2;
				continue ;
			}
			all->redirfd[all->f++][0] = open(all->files_name[all->f], \
				O_CREAT | O_RDWR, 0777);
		}
	}
}
