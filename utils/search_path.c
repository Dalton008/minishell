/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 16:08:17 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 22:58:33 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	search_path(t_all *all, char *cmd)
{
	int		n;
	char	*ff;

	n = 0;
	ff = NULL;
	while (all->paths[n])
	{
		all->parse->pt_cmd = join_path_to_file(all->paths[n], cmd, all);
		ff = all->parse->pt_cmd;
		all->parse->fd_for_open = open(all->parse->pt_cmd, O_RDONLY);
		if (all->parse->fd_for_open != -1)
			break ;
		free(ff);
		n++;
	}
}
