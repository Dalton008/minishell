/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:44:47 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/22 12:54:49 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_all	*all;
	pid_t	pid;
	t_parse	*par;
	char	*line;
	char	**split;
	t_env	*envi;
	int		len_split;
	t_parse *head;
	int fd_copy[2];
	int x;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	all = malloc(sizeof(t_all));
	par = new_node();
	all->parse = par;
	head = all->parse;
	init_env(&envi, env);
	all->paths = get_path(envi);
	while (42)
	{
		signal_init();
		all->parse->flag = 0;
		all->count_fd = 0;
		all->count_pipe = 0;
		all->fd_iter = 0;
		all->fd_iter_redir = 0;
		all->tm_fd0 = 0;
		all->tm_fd1 = 1;
		all->f = 0;
		all->parse->count_r = 0;
		all->absol = 0;
		line = readline("\e[38;5;202mminishell🦊 \033[0m");
		if (line == NULL)
			ctrl_d_hook();
		if ((line && line[0] == '\0') || ft_strcmp(line, "	") == 0 || check_space(line))
		{
      		free(line);
			continue ;
    	}
		split = NULL;
		add_history(line);
		rl_redisplay();
		parse_redir_pipe(all, line);
		quot(all, envi);
		all->parse = head;
		work_with_fd(line, all);
		all->pid = malloc(sizeof(pid_t) * (all->count_pipe + 1));
		// print_struct(all);
		if (all->count_pipe != 0)
		{
			len_split = ft_splitlen(all->parse->split2);
			fd_copy[0] = dup(0);
			fd_copy[1] = dup(1);
			pipex(len_split, all->parse->split2, env, all, envi);
			dup2(fd_copy[0], 0);
			dup2(fd_copy[1], 1);
		}
		else
		{
			x = 1;
			while (x < all->parse->count_r)
			{
				all->fd_iter_redir++;
				x++;
			}
			if (all->parse->count_r > 0)
				dup_fd2(all);
			if (ft_strcmp(all->parse->split2[0], "pwd") == 0)
				cmd_pwd(envi, all);
			else if (ft_strcmp(all->parse->split2[0], "echo") == 0)
				cmd_echo(ft_splitlen(all->parse->split2), all->parse->split2, envi, all);
			else if (ft_strcmp(all->parse->split2[0], "cd") == 0)
				cmd_cd(envi, all->parse->split[1]);
			else if (ft_strcmp(all->parse->split2[0], "env") == 0)
				cmd_env(envi, all);
			else if (ft_strcmp(all->parse->split2[0], "export") == 0)
				cmd_export(envi, all->parse->split2, ft_splitlen(all->parse->split), all);
			else if (ft_strcmp(all->parse->split2[0], "unset") == 0)
				cmd_unset(envi, all->parse->split[1]);
			else if (ft_strcmp(all->parse->split2[0], "exit") == 0)
				cmd_exit(envi);
			else if (ft_strcmp(all->parse->split2[0], "<<") == 0)
			{
				if (!all->parse->split[1])
				{
					printf("\e[38;5;202mminishell:" "\x1b[0msyntax error near unexpected token `newline'\n");
					all->parse = par;
					free(line);
					line = NULL;
					continue ;
				}
				while (42)
				{
					line = readline("> ");
					if (line == NULL)
						break ;
					if (ft_strcmp(line, all->parse->split[1]) == 0)
						break ;
					rl_on_new_line();
				}
			}
			else if (ft_strcmp(all->parse->split[0], "$?") == 0)
			{
				printf("\e[38;5;202mminishell: " "\x1b[0m%d: command not found\n", g_exit_status);
				all->parse->flag = 1;
				g_exit_status = 127;
			}
			else if (ft_strcmp(line, "работяги") == 0)
			{
				printf("\x1b[32m░░░░░░░░░░░░░░░░░░░░\n");
				printf("\x1b[32m░░░░░""\x1b[0mЗАПУСКАЕМ""\x1b[32m░░░░░░\n");
				printf("\x1b[32m░""\x1b[0mГУСЯ""\x1b[32m░" "\e[1;95m▄▀▀▀▄" "\x1b[0m""\x1b[32m░""\e[38;5;196mРАБОТЯГИ\n");
				printf("\e[1;95m▄███▀░""\e[38;5;196m◐""\e[1;95m░░░▌""\x1b[32m░░░░░░░░░\n");
				printf("\x1b[32m░░░░""\e[1;95m▌░░░░░▐""\x1b[32m░░░░░░░░░\n");
				printf("\x1b[32m░░░░""\e[1;95m▐░░░░░▐""\x1b[32m░░░░░░░░░\n");
				printf("\x1b[32m░░░░""\e[1;95m▌░░░░░▐▄▄""\x1b[32m░░░░░░░\n");
				printf("\x1b[32m░░░░""\e[1;95m▌░░░░▄▀\e[38;5;200m▒▒""\e[1;95m▀▀▀▀▄""\x1b[32m\n");
				printf("\x1b[32m░░░""\e[1;95m▐░░░░▐\e[38;5;200m▒▒▒▒▒▒▒▒""\e[1;95m▀▀▄""\x1b[32m\n");
				printf("\x1b[32m░░░""\e[1;95m▐░░░░▐▄\e[38;5;200m▒▒▒▒▒▒▒▒▒▒""\e[1;95m▀""\x1b[32m\n");
				printf("\x1b[32m░░░░""\e[1;95m▀▄░░░░▀▄\e[38;5;200m▒▒▒▒▒▒▒▒▒▒""\e[1;95m▀▄""\x1b[32m\n");
				printf("\x1b[32m░░░░░░""\e[1;95m▀▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▀▄""\x1b[32m\n");
				printf("\x1b[32m░░░░░░░░░░░""\e[1;95m▌▌""\x1b[32m░""\e[1;95m▌▌""\x1b[32m░░░░░\n");
				printf("\x1b[32m░░░░░░░░░░░""\e[1;95m▌▌""\x1b[32m░""\e[1;95m▌▌""\x1b[32m░░░░░\n");
				printf("\x1b[32m░░░░░░░░░""\e[1;95m▄▄▌▌▄▌▌""\x1b[32m░░░░░\n");
			}
			else
			{
				fd_copy[0] = dup(0);
				fd_copy[1] = dup(1);
				other_cmd(all->parse->split2, envi, all);
				dup2(fd_copy[0], 0);
				dup2(fd_copy[1], 1);
			}
			if (all->parse->count_r > 0)
				close_fd2(all);
		}
		all->parse = par;
		free(line);
		line = NULL;
	}
	return (g_exit_status);
}
