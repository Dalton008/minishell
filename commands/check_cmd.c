/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:43:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/30 20:06:41 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**get_path(t_env *envi)
{
	char	**path;

	while (envi)
	{
		if ((ft_strncmp(envi->value, "PATH=", 5)) == 0)
			path = ft_split(envi->value + 5, ':');
		envi = envi->next;
	}
	return (path);
}

static char	*join_path_to_file(char *path, char *cmd)
{
	char	*result;
	char	*for_free;

	for_free = cmd;
	cmd = ft_strjoin("/", cmd);
	result = ft_strjoin(path, cmd);
	free(cmd);
	return (result);
}

void	check_cmd(char **cmd, t_env *envi, char **env)
{
	char	**paths;
	char	*path;
	char	**c;
	int		i;
	int		op;

	i = 0;
	c = ft_split(cmd[0], ' ');
	paths = get_path(envi);
	while (paths[i])
	{
		path = join_path_to_file(paths[i], c[0]);
		op = open(path, O_RDONLY);
		if (op != -1)
			break ;
		i++;
	}
	if (op == -1)
		perror("Invalid command!\n");
	execve(path, c, env);
}
