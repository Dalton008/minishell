/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_path_to_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:06:41 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/14 12:45:41 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_path_to_file(char *path, char *cmd)
{
	char	*result;
	char	*for_free;

	for_free = cmd;
	if (ft_strchr(cmd, '/'))
		return (cmd);
	cmd = ft_strjoin("/", cmd);
	result = ft_strjoin(path, cmd);
	free(cmd);
	return (result);
}
