/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:43:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/16 19:24:00 by mjammie          ###   ########.fr       */
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
	int		len;
	int		len_new_absolut;

	i = 0;
	n = 0;
	len = 0;
	len_new_absolut = 0;
	tmp = malloc(ft_splitlen(cmd) * sizeof(char *) + 1);
	tmp[ft_splitlen(cmd)] = NULL;
	while (cmd[i])
	{
		if (!ft_strchr("<>", cmd[i][0]))
		{
			if (ft_strchr(cmd[i], '/'))
			{
				len = ft_strlen(cmd[i]);
				while (cmd[i][len] != '/')
				{
					len_new_absolut++;
					len--;
				}
				len = ft_strlen(cmd[i]);
				tmp[n] = malloc(len_new_absolut + 1);
				tmp[n][len_new_absolut] = 0;
				while (len_new_absolut)
				{
					tmp[n][len_new_absolut - 1] = cmd[i][len];
					len--;
					len_new_absolut--;
				}
			}
			else
			{
				tmp[n] = cmd[i];
			}
			n++;
		}
		i++;
	}
	tmp[n] = NULL;
	i = 0;
	paths = get_path(envi);
	while (paths[i])
	{
		path = join_path_to_file(paths[i], cmd[0], all);
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
	all->fd_iter--;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		dup_fd(all);
		if (op == -1 && !all->absol)
		{
			// all->error = 127;
			printf("minishell: %s: command not found\n", all->parse->split2[0]);
			// strerror(127);
			exit(127);
		}
			// perror("Invalid command!\n");
		close_fd(all);
		execve(path, tmp, NULL);
	}
	wait(&all->error);
	// waitpid(0, 0, 0);
}
