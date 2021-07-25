/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 18:00:18 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/25 18:06:41 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parse	*new_node(void)
{
	t_parse	*new;

	new = (struct s_parse *)malloc(sizeof(t_parse));
	new->count_r = 0;
	new->line = NULL;
	new->cmd = NULL;
	new->split = NULL;
	new->next = NULL;
	return (new);
}
