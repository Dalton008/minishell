/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:43:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/26 16:38:54 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check(t_all *all, char **tmp)
{
	if (all->paths == NULL)
	{
		printf("\e[38;5;202mminishell: " "\033[0m%s: \
No such file or directory\n", all->parse->split2[0]);
		g_exit_status = 127;
		free_array(tmp);
		return (1);
	}
	if (all->parse->fd_for_open == -1)
	{
		g_exit_status = 127;
		printf("\e[38;5;202mminishell: " "\033[0m%s: \
command not found\n", all->parse->split2[0]);
		free_array(tmp);
		return (1);
	}
	return (0);
}

static void	child(t_all *all, char **tmp, t_env *envi)
{
	if (check(all, tmp))
		exit(g_exit_status);
	execve(all->parse->pt_cmd, tmp, set_env(envi));
}

void	other_cmd(char **cmd, t_env *envi, t_all *all)
{
	int		status;
	pid_t	pid;
	char	**tmp;

	status = 0;
	tmp = malloc((ft_splitlen(cmd) + 1) * sizeof(char *));
	tmp[ft_splitlen(cmd)] = NULL;
	all->paths = NULL;
	get_path(envi, all);
	cut_array(cmd, all, tmp);
	if (check(all, tmp))
		return ;
	search_path(all, cmd[0]);
	signal_init_for_child();
	if (check(all, tmp))
		return ;
	pid = fork();
	if (pid == 0)
		child(all, tmp, envi);
	free_array(tmp);
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	g_exit_status = WEXITSTATUS(status);
}
