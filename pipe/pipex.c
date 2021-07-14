/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 20:05:08 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/13 20:45:57 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	create_pipes(t_pipe *pipes, int	count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		pipe(pipes->pfd[i]);
// 		i++;
// 	}
// }

// void	execute_dup(t_pipe *pipes, int pipe_num)
// {
// 	printf("pi=%d, pipe_num=%d\n", pipes->i, pipe_num);
// 	if (pipes->i == 0)
// 	{
// 		// close(pipes->pfd[0][0]);
// 		dup2(pipes->pfd[0][1], 1);
// 	}
// 	else if (pipes->i < pipe_num - 1)
// 	{
// 		if (pipes->i != 1)
// 			close(pipes->pfd[pipes->i - 1][1]);
// 		dup2(pipes->pfd[pipes->i - 1][0], 0);
// 		close(pipes->pfd[pipes->i][0]);
// 		dup2(pipes->pfd[pipes->i][1], 1);
// 	}
// 	else
// 	{
// 		close(pipes->pfd[pipes->i - 1][1]);
// 		dup2(pipes->pfd[pipes->i - 1][0], 0);
// 		close(pipes->pfd[pipes->i - 1][0]);
// 	}
// }

void	execute_cmd(t_pipe *pipes, /*char **env,*/ char *cmd, int pipe_num, t_all *all)
{
	pid_t	pid;
	int		e;
	char	**split_cmd;
	int		i;

	i = 0;
	split_cmd = ft_split(cmd, ' ');
	while (pipes->path[i])
	{
		pipes->pt = join_path_to_file(pipes->path[i], split_cmd[0]);
		pipes->op = open(pipes->pt, O_RDONLY);
		if (pipes->op != -1)
			break ;
		i++;
	}
	all->fd_iter++;
	pid = fork();
	if (pid == 0)
	{
		dup_fd(all);
		// execute_dup(pipes, pipe_num);
		close_fd(all);
		e = execve(pipes->pt, split_cmd, NULL);
		if (e == -1)
			printf("ERROR on execve\n");
		exit (0);
	}
	close_fd(all);
	waitpid(0, 0, 0);
}

int	pipex(int count_pipes, char **split, /*char **env, */t_all *all, t_env *envi)
{
	t_pipe	pipes;
	// int		*pfd;
	// int fd_copy[2];
	// int		i;

	// i = 0;
	// fd_copy[0] = dup(0);
	// fd_copy[1] = dup(1);
	// create_pipes(&pipes, count_pipes);

	pipes.path = get_path(envi);
	// get_path(env, &pipes);
	// pipes.i = 0;
	// dup2(pipes.pfd[0][0], 0);

	// while (pipes.i < count_pipes)
	// {
	// 	execute_cmd(&pipes, env, split[pipes.i], count_pipes, all);
	// 	pipes.i++;
	// }

	while (all->parse)
	{
		execute_cmd(&pipes,/* env, */all->parse->cmd, count_pipes, all);
		// pipes.i++;
		all->parse = all->parse->next;
	}

	// dup2(fd_copy[1], pipes.pfd[count_pipes][1]);
	// dup2(fd_copy[0], pipes.pfd[count_pipes][0]);
	// close(pipes.pfd[0][0]);
	// wait(0);
	// waitpid(0, 0, 0);
	return (0);
}
