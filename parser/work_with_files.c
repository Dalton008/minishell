/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 14:26:30 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 14:32:19 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_redir(t_all *all)
{
	int		all_redir;

	all_redir = 0;
	while (all->parse)
	{
		all_redir = all_redir + all->parse->count_r;
		all->parse = all->parse->next;
	}
	return (all_redir);
}

void	work_with_files(t_all *all)
{
	int		i;
	int		n;
	int		all_redir;
	t_parse	*head;

	head = all->parse;
	all_redir = count_redir(all);
	all->parse = head;
	all->files_name = malloc(sizeof(char *) * (all_redir + 1));
	all->files_name[all_redir] = NULL;
	while (all->parse)
	{
		n = 0;
		i = 0;
		while (all->parse->split[i] && all->parse->split[i + 1])
		{
			if (ft_strchr("<>", all->parse->split[i][0]))
			{
				all->files_name[n] = ft_strdup(all->parse->split[i + 1]);
				n++;
			}
			i++;
		}
		all->parse = all->parse->next;
	}
}
