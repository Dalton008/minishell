/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:44:47 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/13 14:45:41 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_splitlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

	(void)argc;
	(void)argv;
	all = malloc(sizeof(t_all));
	par = new_node();
	all->parse = par;
	signal_init();
	init_env(&envi, env);
	while (42)
	{
		all->count_fd = 0;
		all->count_pipe = 0;
		all->fd_iter = -1;
		all->tm_fd0 = 0;
		all->tm_fd1 = 1;
		all->parse->count_r = 0;
		line = readline("minishell> ");
		if (line == NULL)
			ctrl_d_hook();
		if (line && line[0] == '\0')
		{
      		free(line);
      		continue ;
    	}
		split = NULL;
		add_history(line);
		rl_redisplay();
		parse_redir_pipe(all, line);
		work_with_fd(line, all);
		// print_struct(all);
		while (all->parse)
		{
			if (all->count_pipe != 0)
			{
				len_split = ft_splitlen(all->parse->split);
				pipex(len_split, all->parse->split, /*env,*/ all, envi);
				break ;
			}
			else
			{
				if (ft_strcmp(all->parse->split[0], "pwd") == 0)
					cmd_pwd(envi, all);
				else if (ft_strcmp(all->parse->split[0], "echo") == 0)
					cmd_echo(ft_splitlen(all->parse->split), all->parse->split, envi, all);
				else if (ft_strcmp(all->parse->split[0], "cd") == 0)
					cmd_cd(envi, all->parse->split[1]);
				else if (ft_strcmp(all->parse->split[0], "env") == 0)
					cmd_env(envi, all);
				else if (ft_strcmp(all->parse->split[0], "export") == 0)
					cmd_export(envi, split, ft_splitlen(all->parse->split), all);
				else if (ft_strcmp(all->parse->split[0], "unset") == 0)
					cmd_unset(envi, all->parse->split[1]);
				else if (ft_strcmp(all->parse->split[0], "exit") == 0)
					cmd_exit(envi);
				else if (ft_strcmp(all->parse->split[0], "<<") == 0)
				{
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
				else
				{
					other_cmd(all->parse->split, envi, all);
				}
			}
			all->parse = all->parse->next;
		}
		all->parse = par;
	}
}
