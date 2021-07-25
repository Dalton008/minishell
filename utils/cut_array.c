/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 16:30:52 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/25 15:54:39 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	if_absolute_path(char **cmd, int *i, int *n, char **tmp)
{
	int	len_new_absolut;
	int	len;

	len_new_absolut = 0;
	len = ft_strlen(cmd[(*i)]);
	while (cmd[(*i)][len] != '/')
	{
		len_new_absolut++;
		len--;
	}
	len = ft_strlen(cmd[(*i)]);
	tmp[(*n)] = malloc(len_new_absolut + 1);
	tmp[(*n)][len_new_absolut] = 0;
	while (len_new_absolut)
	{
		tmp[(*n)][len_new_absolut - 1] = cmd[(*i)][len];
		len--;
		len_new_absolut--;
	}
}

void	cut_array(char **cmd, t_all *all, char **tmp)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (cmd[i])
	{
		if (ft_strchr("<>", cmd[i][0]) && !ft_strchr("\"", \
			all->parse->split[i][0]))
			break ;
		else
		{
			if (ft_strchr(cmd[i], '/'))
			{
				if_absolute_path(cmd, &i, &n, tmp);
			}
			else
				tmp[n] = cmd[i];
			n++;
		}
		i++;
	}
	tmp[n] = NULL;
}
