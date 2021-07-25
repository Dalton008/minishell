/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 20:05:08 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 20:01:46 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	precheck(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	check_cmd(t_all *all, t_env *envi)
{
	if (ft_strcmp(all->parse->split2[0], "pwd") == 0)
		cmd_pwd();
	else if (ft_strcmp(all->parse->split2[0], "echo") == 0)
		cmd_echo(ft_splitlen(all->parse->split2), all->parse->split2);
	else if (ft_strcmp(all->parse->split2[0], "cd") == 0)
		cmd_cd(envi, all->parse->split[1]);
	else if (ft_strcmp(all->parse->split2[0], "env") == 0)
		cmd_env(envi, all);
	else if (ft_strcmp(all->parse->split2[0], "export") == 0)
		cmd_export(envi, all->parse->split2, \
			ft_splitlen(all->parse->split), all);
	else if (ft_strcmp(all->parse->split2[0], "unset") == 0)
		cmd_unset(envi, all->parse->split[1]);
	else if (ft_strcmp(all->parse->split2[0], "exit") == 0)
		cmd_exit(all->parse->split2);
	if (precheck(all->parse->split2[0]))
		return (1);
	return (0);
}

void	child(t_all *all, t_env *envi, char **tmp)
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
	execve(all->parse->pt_cmd, tmp, set_env(envi));
}

void	fd_child_or_parent(t_all *all, t_env *envi, char **tmp)
{
	all->pid[all->fd_iter] = fork();
	if (all->pid[all->fd_iter] == 0)
		child(all, envi, tmp);
	else
		close(all->pfd[all->fd_iter][1]);
	if (all->parse->count_r > 0)
	{
		close(all->redirfd[0][0]);
		close(all->redirfd[0][1]);
	}
	all->fd_iter++;
}

void	pipex(t_all *all, t_env *envi)
{
	char	**tmp;
	int		y;

	get_path(envi, all);
	// all->pid = malloc(sizeof(pid_t) * all->count_pipe);
	while (all->parse)
	{
		dup_for_redir(all);
		if (check(all))
			break ;
		tmp = malloc((ft_splitlen(all->parse->split2) + 1) * sizeof(char *));
		tmp[ft_splitlen(all->parse->split2)] = NULL;
		cut_array(all->parse->split2, all, tmp);
		if (!precheck(tmp[0]))
		{
			search_path(all, tmp[0]);
			if (check(all))
				break ;
		}
		fd_child_or_parent(all, envi, tmp);
		all->parse = all->parse->next;
		y = 0;
		while (tmp[y])
			free(tmp[y++]);
		free(tmp);
	}
	wait_and_close(all);
}
