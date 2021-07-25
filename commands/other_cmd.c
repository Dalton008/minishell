/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:43:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 23:22:25 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check(t_all *all)
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

void	other_cmd(char **cmd, t_env *envi, t_all *all)
{
	int		status;
	pid_t	pid;
	char	**tmp;

	status = 0;
	tmp = malloc((ft_splitlen(cmd) + 1) * sizeof(char *));
	tmp[ft_splitlen(cmd)] = NULL;
	cut_array(cmd, all, tmp);
	get_path(envi, all);
	if (check(all))
		return ;
	search_path(all, tmp[0]);
	signal_init_for_child();
	printf("%s\n", all->parse->pt_cmd);
	printf("%s\n", tmp[0]);
	if (check(all))
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (check(all))
			exit(g_exit_status);
		execve(all->parse->pt_cmd, tmp, set_env(envi));
	}
	free(tmp);
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	g_exit_status = WEXITSTATUS(status);
}
