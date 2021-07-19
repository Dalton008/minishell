/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:43:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/19 17:52:07 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	other_cmd(char **cmd, t_env *envi, t_all *all)
{
	char	**paths;
	char	*path;
	int		status;
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
	status = 0;
	len = 0;
	len_new_absolut = 0;
	tmp = malloc(ft_splitlen(cmd) * sizeof(char *) + 1);
	tmp[ft_splitlen(cmd)] = NULL;
	while (cmd[i])
	{
		if (ft_strchr("<>", cmd[i][0]))
			break ;
		else /*(!ft_strchr("<>", cmd[i][0]))*/
		{
			if (ft_strchr(cmd[i], '/'))
			{
				// printf("{%s}\n", cmd[i]);
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
	// while (tmp[i])
	// 	printf("%s\n", tmp[i++]);
	i = 0;
	all->paths = get_path(envi);
	if (all->paths == NULL)
	{
		printf("minishell: %s: No such file or directory\n", all->parse->split2[0]);
		g_exit_status = 127;
		return ;
	}
	while (all->paths[i])
	{
		path = join_path_to_file(all->paths[i], cmd[0], all);
		op = open(path, O_RDONLY);
		if (op != -1)
			break ;
		i++;
	}
	z = 1;
	while (z < all->parse->count_r)
	{
		all->fd_iter++;
		z++;
	}
	signal_init_for_child();
	if (op == -1 && !all->absol)
	{
		g_exit_status = 127;
		printf("minishell: %s: command not found\n", all->parse->split2[0]);
		// exit(g_exit_status);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		dup_fd(all);
		if (op == -1 && !all->absol)
		{
			g_exit_status = 127;
			printf("minishell: %s: command not found\n", all->parse->split2[0]);
			exit(g_exit_status);
		}
		execve(path, tmp, NULL);
	}
	else if (all->parse->count_r > 0)
		close(all->pfd[0][1]);
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	g_exit_status = WEXITSTATUS(status);
}
