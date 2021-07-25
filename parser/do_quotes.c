/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 17:41:03 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/25 17:41:04 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_simple_quotes(t_all **all)
{
	(*all)->parse->i_1++;
	while ((*all)->parse->line1[(*all)->parse->i_1] && \
			(*all)->parse->line1[(*all)->parse->i_1] != '\'')
	{
		(*all)->parse->line2[(*all)->parse->i_2++] = \
					(*all)->parse->line1[(*all)->parse->i_1++];
	}
	(*all)->parse->i_1++;
}

void	do_two_quotes(t_all **all, t_env *envi)
{
	(*all)->parse->i_1++;
	while ((*all)->parse->line1[(*all)->parse->i_1] && \
				(*all)->parse->line1[(*all)->parse->i_1] != '\"')
	{
		if ((*all)->parse->line1[(*all)->parse->i_1] == '$' \
				&& (*all)->parse->line1[(*all)->parse->i_1 + 1])
			do_dollar(all, envi);
		else
			(*all)->parse->line2[(*all)->parse->i_2++] = \
					(*all)->parse->line1[(*all)->parse->i_1++];
	}
	(*all)->parse->i_1++;
}
