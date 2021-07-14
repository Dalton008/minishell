/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:43:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/14 12:46:09 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	other_cmd(char **cmd, t_env *envi, t_all *all)
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
		close(op);
	}
	z = 0;
	while (z < all->parse->count_r)
	{
		all->fd_iter++;
		z++;
	}
	pid = fork();
	if (pid == 0)
	{
		dup_fd(all);
		if (op == -1)
			perror("Invalid command!\n");
		execve(path, tmp, NULL);
		close_fd(all);
	}
	waitpid(0, 0, 0);
}
