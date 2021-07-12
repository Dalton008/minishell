/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:43:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/12 18:15:33 by mjammie          ###   ########.fr       */
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

void	other_cmd(char **cmd, t_env *envi, char **env, t_all *all)
{
	char	**paths;
	char	*path;
	int		i;
	int		op;
	pid_t	pid;
	int		z;
	char	**tmp;
	int		n;

	i = 0;
	n = 0;
	tmp = malloc(ft_splitlen(cmd) * sizeof(char *));
	tmp[ft_splitlen(cmd)] = NULL;
	while (cmd[i])
	{
		if (!ft_strchr("<>", cmd[i][0]))
		{
			tmp[n] = cmd[i];
			n++;
		}
		i++;
	}
	i = 0;
	paths = get_path(envi);
	while (paths[i])
	{
		path = join_path_to_file(paths[i], cmd[0]);
		op = open(path, O_RDONLY);
		if (op != -1)
			break ;
		i++;
	}
	z = 0;
	while (z < all->parse->count_r)
	{
		all->fd_iter++;
		z++;
	}
		all->fd_iter++;
	pid = fork();
	if (pid == 0)
	{
		dup_fd(all);
		if (op == -1)
			perror("Invalid command!\n");
		execve(path, tmp, env);
		close_fd(all);
	}
	wait(0);
}
