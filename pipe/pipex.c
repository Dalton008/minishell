// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 20:05:08 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/14 16:27:22 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_cmd(t_all *all, t_env *envi)
{
	if (ft_strcmp(all->parse->split2[0], "pwd") == 0)
	{
		cmd_pwd(envi, all);
		return (1);
	}
	else if (ft_strcmp(all->parse->split2[0], "echo") == 0)
	{
		cmd_echo(ft_splitlen(all->parse->split2), all->parse->split2, envi, all);
		return (1);
	}
	else if (ft_strcmp(all->parse->split2[0], "cd") == 0)
	{
		cmd_cd(envi, all->parse->split[1]);
		return (1);
	}
	else if (ft_strcmp(all->parse->split2[0], "env") == 0)
	{
		cmd_env(envi, all);
		return (1);
	}
	else if (ft_strcmp(all->parse->split2[0], "export") == 0)
	{
		cmd_export(envi, all->parse->split2, ft_splitlen(all->parse->split), all);
		return (1);
	}
	else if (ft_strcmp(all->parse->split2[0], "unset") == 0)
	{
		cmd_unset(envi, all->parse->split[1]);
		return (1);
	}
	else if (ft_strcmp(all->parse->split2[0], "exit") == 0)
	{
		cmd_exit(envi);
		return (1);
	}
	return (0);
}

int	pipex(int count_pipes, char **split, char **env, t_all *all, t_env *envi)
{
	t_pipe	pipes;
	pid_t	*pid;
	int		i;
	int		n;
	char	**split_cmd;
	int		fdtmp;
	int m;

	i = 0;
	all->paths = get_path(envi);
	fdtmp = dup(0);
	pid = malloc(sizeof(pid_t) * all->count_pipe);
	while (all->parse)
	{
		m = 1;
		while (m < all->parse->count_r)
		{
			all->fd_iter_redir++;
			m++;
		}
		if (all->parse->count_r > 0)
			dup_fd2(all);
		n = 0;
		split_cmd = ft_split(all->parse->cmd, ' ');
		if (all->paths == NULL)
		{
			printf("\e[38;5;202mminishell: " "\033[0m%s: No such file or directory\n", all->parse->split2[0]);
			g_exit_status = 127;
			return (1);
		}
		while (all->paths[n])
		{
			pipes.pt = join_path_to_file(all->paths[n], all->parse->split2[0], all);
			pipes.op = open(pipes.pt, O_RDONLY);
			if (pipes.op != -1)
				break ;
			n++;
		}
		if (pipes.op == -1)
		{
			g_exit_status = 127;
			printf("\e[38;5;202mminishell: " "\033[0m%s: command not found\n", split_cmd[0]);
			break ;
		}
		pid[i] = fork();
		if (pid[i] == 0)
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
			execve(pipes.pt, all->parse->split2, env);
		}
		else
			close(all->pfd[all->fd_iter][1]);
		if (all->parse->count_r > 0)
		{
			close(all->redirfd[0][0]);
			close(all->redirfd[0][1]);
		}
		i++;
		all->fd_iter++;
		all->parse = all->parse->next;
	}
	i = 0;
	while (i < all->count_pipe + 1)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	close(all->pfd[0][0]);
	close(all->pfd[0][1]);
	close(all->pfd[1][0]);
	close(all->pfd[1][1]);
	return (0);
}
//env | grep USER | wc -l