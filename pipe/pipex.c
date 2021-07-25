/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 20:05:08 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/25 20:22:05 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check(t_all *all)
{
	if (all->paths == NULL)
	{
		printf("\e[38;5;202mminishell: " "\033[0m%s: \
No such file or directory\n", all->parse->split2[0]);
		g_exit_status = 127;
		return (1);
	}
	if (all->parse->fd_for_open == -1 && !all->absol)
	{
		g_exit_status = 127;
		printf("\e[38;5;202mminishell: " "\033[0m%s: \
command not found\n", all->parse->split2[0]);
		return (1);
	}
	return (0);
}

void	child(t_all *all, t_env *envi, char **tmp, char **env)
{
	if (all->fd_iter == 0)
	{
		close(all->pfd[all->fd_iter][0]);
		dup2(all->pfd[all->fd_iter][1], 1);
	}
	else if (all->fd_iter < all->count_pipe)
	{
		close(all->pfd[all->fd_iter - 1][1]);
		dup2(all->pfd[all->fd_iter - 1][0], 0);
		close(all->pfd[all->fd_iter][0]);
		dup2(all->pfd[all->fd_iter][1], 1);
	}
	else
	{
		close(all->pfd[all->fd_iter - 1][1]);
		dup2(all->pfd[all->fd_iter - 1][0], 0);
	}
	if (check_cmd(all, envi))
		exit(0);
	execve(all->parse->pt_cmd, tmp, env);
}

void	fd_child_or_parent(t_all *all, t_env *envi, char **tmp, char **env)
{
	all->pid[all->fd_iter] = fork();
	if (all->pid[all->fd_iter] == 0)
		child(all, envi, tmp, env);
	else
	{
		close(all->pfd[all->fd_iter][1]);
	}
	if (all->parse->count_r > 0)
	{
		close(all->redirfd[0][0]);
		close(all->redirfd[0][1]);
	}
	all->fd_iter++;
}

int	work_with_pipe(t_all *all, char **tmp, t_env *envi, char **env)
{
	if (!precheck(tmp[0]))
	{
		search_path(all, tmp[0]);
		if (check(all))
			return (1);
	}
	dup_for_redir(all);
	fd_child_or_parent(all, envi, tmp, env);
	if (all->parse->count_r > 0)
		close_fd2(all);
	if (all->parse->next)
		free(tmp);
	return (0);
}

void	pipex(t_all *all, t_env *envi)
{
	char	**tmp;
	char	**env;
	int		i;

	i = 0;
	get_path(envi, all);
	env = set_env(envi);
	while (all->parse)
	{
		tmp = malloc((ft_splitlen(all->parse->split2) + 1) * sizeof(char *));
		if (check(all))
			break ;
		cut_array(all->parse->split2, all, tmp);
		if (work_with_pipe(all, tmp, envi, env))
			break ;
		all->parse = all->parse->next;
	}
	wait_and_close(all);
	free_array(tmp);
	free_array(env);
}
