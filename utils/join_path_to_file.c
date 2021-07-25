/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_path_to_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:06:41 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/25 20:25:56 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_path_to_file(char *path, char *cmd, t_all *all)
{
	char	*result;
	char	*ff;

	result = NULL;
	if (ft_strchr(cmd, '/'))
	{
		all->absol = 1;
		return (cmd);
	}
	ff = ft_strjoin("/", cmd);
	result = ft_strjoin(path, ff);
	free(ff);
	return (result);
}
