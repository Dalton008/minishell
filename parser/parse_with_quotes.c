/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_with_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 13:13:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/25 17:39:47 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_t_iter(t_iter *iter)
{
	iter->q = 1;
	iter->i = 0;
	iter->n = 0;
	iter->x = 0;
	iter->len = 0;
	iter->i_sp = 0;
}

int	out_quotes(t_iter *iter, char *line, char **arr)
{
	iter->len = 0;
	if (line[iter->i] == ' ')
		iter->i++;
	if (line[iter->i] == '"' || line[iter->i] == '\'')
		iter->q++;
	if (iter->q % 2 != 0)
	{
		iter->x = iter->i;
		while (line[iter->x] && line[iter->x++] != ' ')
			iter->len++;
		arr[iter->i_sp] = (char *)malloc(iter->len + 1);
		arr[iter->i_sp][iter->len] = 0;
		iter->x = iter->i;
		iter->n = 0;
		while (iter->n < iter->len)
		{
			arr[iter->i_sp][iter->n] = line[iter->x];
			iter->n++;
			iter->x++;
		}
		iter->i = iter->x;
		return (1);
	}
	return (0);
}

void	work_without_space(t_iter *iter, char *line, char **arr)
{
	iter->x++;
	iter->len++;
	while (line[iter->x] && line[iter->x] != ' ')
	{
		iter->len++;
		iter->x++;
	}
	arr[iter->i_sp] = (char *)malloc(iter->len + 1);
	arr[iter->i_sp][iter->len] = 0;
	iter->x = iter->i;
	iter->n = 0;
	while (iter->n < iter->len)
	{
		arr[iter->i_sp][iter->n] = line[iter->x];
		iter->n++;
		iter->x++;
	}
	iter->i = iter->x + 1;
}

void	work_with_space(t_iter *iter, char *line, char **arr)
{
	iter->len++;
	arr[iter->i_sp] = (char *)malloc(iter->len);
	arr[iter->i_sp][iter->len] = 0;
	iter->x = iter->i;
	iter->n = 0;
	while (iter->n < iter->len)
	{
		arr[iter->i_sp][iter->n] = line[iter->x];
		iter->n++;
		iter->x++;
	}
	iter->i = iter->x + 1;
}

void	work_with_quotes(char *line, t_parse *parse)
{
	t_iter	iter;

	init_t_iter(&iter);
	parse->split = malloc(sizeof(char *) * (count_with_quotes(line) + 1));
	while (line[iter.i] && line[iter.i] != '|')
	{
		if (!out_quotes(&iter, line, parse->split))
		{
			iter.x = iter.i;
			iter.x++;
			iter.len++;
			while (line[iter.x] && (line[iter.x] != '"' || line[iter.i] == '\''))
			{
				iter.len++;
				iter.x++;
			}
			if (line[iter.x + 1] && line[iter.x + 1] != ' ')
				work_without_space(&iter, line, parse->split);
			else
				work_with_space(&iter, line, parse->split);
			iter.q++;
		}
		iter.i_sp++;
	}
	parse->split[count_with_quotes(line)] = NULL;
}
