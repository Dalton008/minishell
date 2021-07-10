/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 20:05:08 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/07 15:40:18 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_path(char **env, t_pipe *pipes)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], "PATH=", 5)) == 0)
		{
			pipes->path = ft_split(env[i] + 5, ':');
			return ;
		}
		i++;
	}
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

void	create_pipes(t_pipe *pipes, int	count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pipe(pipes->pfd[i]);
		i++;
	}
}

void	execute_dup(t_pipe *pipes, int pipe_num)
{
	if (pipes->i == 0)
	{
		dup2(pipes->pfd[0][1], 1);
	}
	else if (pipes->i < pipe_num - 1)
	{
		if (pipes->i != 1)
			close(pipes->pfd[pipes->i - 1][1]);
		dup2(pipes->pfd[pipes->i - 1][0], 0);
		close(pipes->pfd[pipes->i][0]);
		dup2(pipes->pfd[pipes->i][1], 1);
	}
	else
	{
		close(pipes->pfd[pipes->i - 1][1]);
		dup2(pipes->pfd[pipes->i - 1][0], 0);
		close(pipes->pfd[pipes->i - 1][0]);
	}
}

void	execute_cmd(t_pipe *pipes, char **env, char *cmd, int pipe_num)
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
	pid = fork();
	if (pid == 0)
	{
		execute_dup(pipes, pipe_num);
		e = execve(pipes->pt, split_cmd, env);
		if (e == -1)
			perror("ERROR on execve");
		exit (1);
	}
}

int	check_cmd(char **split, t_pipe	pipes)
{
	if (ft_strcmp(split[pipes.i], "pwd") == 0)
		return (1);
	else if (ft_strcmp(split[pipes.i], "echo") == 0)
		return (1);
	else if (ft_strcmp(split[pipes.i], "cd") == 0)
		return (1);
	else if (ft_strcmp(split[pipes.i], "env") == 0)
		return (1);
	else if (ft_strcmp(split[pipes.i], "export") == 0)
		return (1);
	else if (ft_strcmp(split[pipes.i], "unset") == 0)
		return (1);
	else if (ft_strcmp(split[pipes.i], "exit") == 0)
		return (1);
	return (0);
}

void	buildins_cmd(char *cmd)
{

}

int	pipex(int count_pipes, char **split, char **env)
{
	t_pipe	pipes;
	int		*pfd;
	pid_t	pid;
	int fd_copy[2];

	fd_copy[0] = dup(0);
	fd_copy[1] = dup(1);
	create_pipes(&pipes, count_pipes);
	get_path(env, &pipes);
	pipes.i = 0;
	dup2(pipes.pfd[0][0], 0);
	while (pipes.i < count_pipes)
	{
		if (check_cmd(split, pipes))
			buildins_cmd()
		else
			execute_cmd(&pipes, env, split[pipes.i], count_pipes);
		pipes.i++;
	}
	dup2(fd_copy[1], pipes.pfd[count_pipes][1]);
	dup2(fd_copy[0], pipes.pfd[count_pipes][0]);
	close(pipes.pfd[0][0]);
	waitpid(0, 0, 0);
	return (0);
}
