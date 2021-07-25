/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_len_with_q.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 12:16:55 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/25 17:39:41 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	if_in_quotes(char *line, t_iter *iter)
{
	iter->x = iter->i;
	iter->x++;
	while (line[iter->x] && (line[iter->x] != '"' || line[iter->i] == '\''))
		iter->x++;
	if (line[iter->x + 1] && line[iter->x + 1] != ' ')
	{
		iter->x++;
		while (line[iter->x] && line[iter->x] != ' ')
			iter->x++;
		iter->i = iter->x + 1;
	}
	else
		iter->i = iter->x + 1;
	iter->q++;
}

int	count_with_quotes(char *line)
{
	t_iter	iter;
	int		count;

	count = 0;
	iter.i = 0;
	iter.q = 1;
	iter.x = 0;
	while (line[iter.i] && line[iter.i] != '|')
	{
		if (line[iter.i] == ' ')
			iter.i++;
		if (line[iter.i] && (line[iter.i] == '"' || line[iter.i] == '\''))
			iter.q++;
		if (iter.q % 2 != 0)
		{
			iter.x = iter.i;
			while (line[iter.x] && line[iter.x++] != ' ')
				iter.x++;
			iter.i = iter.x;
		}
		else
			if_in_quotes(line, &iter);
		count++;
	}
	return (count);
}
