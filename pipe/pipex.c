/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 20:05:08 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/30 20:45:28 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**get_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], "PATH=", 5)) == 0)
			path = ft_split(env[i] + 5, ':');
		i++;
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

void	child(int *pfd, char **argv, char **env)
{
	t_pipe	pipe;

	pipe.i = 0;
	pipe.path = get_path(env);
	pipe.cmd = ft_split(argv[2], ' ');
	while (pipe.path[pipe.i])
	{
		pipe.pt = join_path_to_file(pipe.path[pipe.i], pipe.cmd[0]);
		pipe.op = open(pipe.pt, O_RDONLY);
		if (pipe.op != -1)
			break ;
		pipe.i++;
	}
	if (pipe.op == -1)
		perror("Invalid command!\n");
	close(pfd[0]);
	dup2(pfd[1], 1);
	close(pfd[1]);
	dup2(pipe.file, 0);
	execve(pipe.pt, pipe.cmd, env);
	pipe.file = open(argv[1], O_RDONLY, 0777);
	close(pipe.op);
}

void	parent(int *pfd, char **argv, char **env)
{
	t_pipe	pipe;

	pipe.i = 0;
	pipe.file = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	pipe.path = get_path(env);
	pipe.cmd = ft_split(argv[3], ' ');
	while (pipe.path[pipe.i])
	{
		pipe.pt = join_path_to_file(pipe.path[pipe.i], pipe.cmd[0]);
		pipe.op = open(pipe.pt, O_RDONLY);
		if (pipe.op != -1)
			break ;
		pipe.i++;
	}
	if (pipe.op == -1)
		perror("Invalid command!\n");
	close(pfd[1]);
	dup2(pfd[0], 0);
	close(pfd[0]);
	dup2(pipe.file, 1);
	execve(pipe.pt, pipe.cmd, env);
	close(pipe.op);
}

int	pipex(int argc, char **argv, char **env)
{
	int		pfd[2];
	pid_t	pid;

	if (pipe(pfd) == -1)
	{
		perror("Error!");
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		child(pfd, argv, env);
	}
	else
	{
		parent(pfd, argv, env);
	}
	return (0);
}
