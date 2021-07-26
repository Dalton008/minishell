/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:44:47 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/26 16:44:41 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	without_pipes(char *line, t_all *all, t_env *envi)
{
	int	x;

	x = 1;
	while (x < all->parse->count_r)
	{
		all->fd_iter_redir++;
		x++;
	}
	if (all->parse->count_r > 0)
		dup_fd2(all);
	if (!check_cmd(all, envi))
	{
		if (ft_strcmp(all->parse->split2[0], "<<") == 0)
			double_reverse_redir(line, all);
		else if (ft_strcmp(all->parse->split[0], "$?") == 0)
		{
			printf("mminishell: %d: command not found\n", g_exit_status);
			all->parse->flag = 1;
			g_exit_status = 127;
		}
		else
			other_cmd(all->parse->split2, envi, all);
	}
	if (all->parse->count_r > 0)
		close_fd2(all);
}

int	check_error(char *line)
{
	if (line == NULL)
		ctrl_d_hook();
	if (main_preparser(line))
	{
		add_history(line);
		free(line);
		return (1);
	}
	if ((line && line[0] == '\0') || ft_strcmp(line, "	") == 0 \
		|| check_space(line))
	{
		free(line);
		return (1);
	}
	return (0);
}

void	if_have_pipes(t_all *all, t_env *envi)
{
	int		fd_copy[2];

	fd_copy[0] = dup(0);
	fd_copy[1] = dup(1);
	pipex(all, envi);
	dup2(fd_copy[0], 0);
	dup2(fd_copy[1], 1);
}

static void	main_parse(t_all *all, t_env *envi)
{
	t_all	*ha;
	t_parse	*head;

	ha = all;
	head = all->parse;
	add_history(all->readline);
	rl_redisplay();
	parse_redir_pipe(all, all->readline);
	all->parse = head;
	quot(all, envi);
	all->parse = head;
	parse_fd(all->readline, all);
	all = ha;
	all->pid = malloc(sizeof(pid_t) * (all->count_pipe + 1));
	if (all->count_pipe != 0)
		if_have_pipes(all, envi);
	else
		without_pipes(all->readline, all, envi);
}

int	main(int argc, char **argv, char **env)
{
	t_all	*all;
	t_parse	*par;
	t_env	*envi;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	all = malloc(sizeof(t_all));
	par = new_node();
	all->parse = par;
	init_env(&envi, env);
	while (42)
	{
		signal_init();
		init_all(all);
		all->readline = readline("\e[38;5;202mminishell🦊 \033[0m");
		if (check_error(all->readline))
			continue ;
		main_parse(all, envi);
		all->parse = par;
		free(all->readline);
	}
	return (g_exit_status);
}
