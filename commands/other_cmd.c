/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:43:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/22 14:33:14 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_env(t_env *envi)
{
	char	**res;
	t_env	*head;
	int		i;

	i = 0;
	head = envi;
	while (envi)
	{
		i++;
		envi = envi->next;
	}
	envi = head;
	res = malloc(sizeof(char*) * (i + 1));
	res[i] = NULL;
	i = 0; 
	while (envi)
	{
		res[i] = ft_strdup(envi->value);
		i++;
		envi = envi->next;
	}
	return (res);
}

void	other_cmd(char **cmd, t_env *envi, t_all *all)
{
	char	*path;
	int		status;
	int		i;
	int		op;
	pid_t	pid;
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
		else
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
	all->paths = get_path(envi);
	if (all->paths == NULL)
	{
		printf("\e[38;5;202mminishell: " "\033[0m%s: No such file or directory\n", all->parse->split2[0]);
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
	signal_init_for_child();
	if (op == -1 && !all->absol)
	{
		g_exit_status = 127;
		printf("\e[38;5;202mminishell: " "\033[0m%s: command not found\n", all->parse->split2[0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (op == -1 && !all->absol)
		{
			g_exit_status = 127;
			printf("\e[38;5;202mminishell: " "\033[0m%s: command not found\n", all->parse->split2[0]);
			exit(g_exit_status);
		}
		execve(path, tmp, set_env(envi));
	}
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	g_exit_status = WEXITSTATUS(status);
}
