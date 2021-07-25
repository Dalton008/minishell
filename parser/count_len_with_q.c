/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_len_with_q.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 12:16:55 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 14:59:05 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	if_in_quotes(char *line, int *x, int *i, int *q)
{
	(*x) = (*i);
	(*x)++;
	while (line[(*x)] && (line[(*x)] != '"' || line[(*i)] == '\''))
		(*x)++;
	if (line[(*x) + 1] && line[(*x) + 1] != ' ')
	{
		(*x)++;
		while (line[(*x)] && line[(*x)] != ' ')
			(*x)++;
		(*i) = (*x) + 1;
	}
	else
		(*i) = (*x) + 1;
	(*q)++;
}

int	count_with_quotes(char *line)
{
	int	count;
	int	i;
	int	x;
	int	q;

	count = 0;
	i = 0;
	q = 1;
	while (line[i] && line[i] != '|')
	{
		if (line[i] == ' ')
			i++;
		if (line[i] == '"' || line[i] == '\'')
			q++;
		if (q % 2 != 0)
		{
			x = i;
			while (line[x] && line[x++] != ' ')
				x++;
			i = x;
		}
		else
			if_in_quotes(line, &x, &i, &q);
		count++;
	}
	return (count);
}
