/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 20:11:31 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/26 16:19:59 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_all(t_all *all)
{
	all->fd_iter_redir = 0;
	all->parse->flag = 0;
	all->count_fd = 0;
	all->count_pipe = 0;
	all->fd_iter = 0;
	all->tm_fd0 = 0;
	all->tm_fd1 = 1;
	all->f = 0;
	all->parse->count_r = 0;
	all->absol = 0;
	all->parse->fd_for_open = 0;
}

void	double_reverse_redir(char *line, t_all *all)
{
	char	*ff;

	ff = NULL;
	while (42)
	{
		line = readline("> ");
		ff = line;
		if (line == NULL)
			break ;
		if (ft_strcmp(line, all->parse->split2[1]) == 0)
			break ;
		free(line);
	}
	free(ff);
}
