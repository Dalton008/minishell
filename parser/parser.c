/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 12:13:52 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/25 17:41:09 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quotes_closed(t_all *all)
{
	int	i;
	int	count1;
	int	count2;

	i = 0;
	count1 = 0;
	count2 = 0;
	while (all->parse->line1[i])
	{
		if (all->parse->line1[i] == '\'')
			count1++;
		if (all->parse->line1[i] == '\"')
			count2++;
		i++;
	}
	if ((count1 % 2 != 0) || (count2 % 2 != 0))
		return (0);
	return (1);
}

void	for_quotes(t_all *all, t_env *envi)
{
	if (all->parse->line1[all->parse->i_1] == '\'' || \
						all->parse->line1[all->parse->i_1] == '\"' \
							|| all->parse->line1[all->parse->i_1] == '$')
	{
		if (all->parse->line1[all->parse->i_1] == '\'')
			do_simple_quotes(&all);
		else if (all->parse->line1[all->parse->i_1] == '\"')
			do_two_quotes(&all, envi);
		else if (all->parse->line1[all->parse->i_1] == '$' && \
					!ft_check(all->parse->line1[all->parse->i_1 + 1], "\'\""))
			do_dollar(&all, envi);
		else if (all->parse->line1[all->parse->i_1] == '$' \
				&& ft_check(all->parse->line1[all->parse->i_1 + 1], "\'\""))
			all->parse->i_1++;
	}
	else
		all->parse->line2[all->parse->i_2++] = \
					all->parse->line1[all->parse->i_1++];
}

void	init_quotes(t_all *all, int i)
{
	all->parse->i_1 = 0;
	all->parse->i_2 = 0;
	all->parse->line1 = all->parse->split[i];
	all->parse->line2 = (char *)ft_calloc(1000, sizeof(char));
}

void	quotes(t_all *all, t_env *envi)
{
	int		i;
	char	*for_free;

	i = -1;
	for_free = all->parse->split[0];
	all->parse->split[0] = ft_strtrim(all->parse->split[0], " ");
	free(for_free);
	while (all->parse->split[++i])
	{
		init_quotes(all, i);
		while (all->parse->line1[all->parse->i_1])
		{
			if (quotes_closed(all))
				for_quotes(all, envi);
			else
			{
				printf("\e[38;5;202mminishell: "\
"\033[0m%s: not enought quotes\n", all->parse->line1);
				break ;
			}
		}
		all->parse->line2[all->parse->i_2] = '\0';
		all->parse->split2[i] = all->parse->line2;
	}
	all->parse->split2[i] = NULL;
}

void	quot(t_all *all, t_env *envi)
{
	while (all->parse)
	{
		all->parse->split2 = malloc(sizeof(char *) \
						* (ft_splitlen(all->parse->split) + 1));
		quotes(all, envi);
		all->parse = all->parse->next;
	}
}
