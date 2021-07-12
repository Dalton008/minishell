/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:44:47 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/12 11:30:44 by mjammie          ###   ########.fr       */
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
	init_env(&envi, env);
	signal_init();
	while (42)
	{
		all->count_fd = 0;
		all->count_pipe = 0;
		line = readline("minishell> ");
		if (line == NULL)
			ctrl_d_hook();
		split = NULL;
		add_history(line);
		rl_redisplay();
		parse_redir_pipe(all, line);
		work_with_fd(line, all);
		print_struct(all);
		// if (all->parse->pipe != 0)
		// {
		// 	split = ft_split(line, '|');
		// 	len_split = ft_splitlen(split);
		// 	pipex(len_split, split, env);
		// 	break ;
		// }
		// PIPEX
		
		// split = ft_split(line, '|');
		// len_split = ft_splitlen(split);
		// if (par->pipe != 0)
		// {
		// 	// pipex(par->pipe, split, env);
		// 	pipex(len_split, split, env);
		// 	break ;
		// }
		// PIPEX
		
		// while (split[i])
		// {
		// 	printf("%s\n", split[i]);
		// 	i++;
		// }
		// else
		// {
		// 	split = ft_split(line, ' ');
		// 	len_split = ft_splitlen(split);
		// while (all->parse)
		// {
			// if (ft_strcmp(split[0], "pwd") == 0)
			// 	cmd_pwd(envi);
			// else if (ft_strcmp(split[0], "echo") == 0)
			// 	cmd_echo(len_split, split, envi);
			// else if (ft_strcmp(split[0], "cd") == 0)
			// 	cmd_cd(envi, split[1]);
			// else if (ft_strcmp(split[0], "env") == 0)
			// 	cmd_env(envi);
			// else if (ft_strcmp(split[0], "export") == 0)
			// 	cmd_export(envi, split, len_split);
			// else if (ft_strcmp(split[0], "unset") == 0)
			// 	cmd_unset(envi, split[1]);
			// else if (ft_strcmp(split[0], "exit") == 0)
			// 	cmd_exit(envi);
			// else
			// {
			// 	other_cmd(split, envi, env);
			// 	wait(0);
			// }
			// if (ft_strcmp(all->parse->cmd, "pwd") == 0)
			// 	cmd_pwd(envi);
			// else if (ft_strcmp(all->parse->cmd, "echo") == 0)
			// 	cmd_echo(ft_splitlen(all->parse->split), all->parse->split, envi);
			// else if (ft_strcmp(all->parse->cmd, "cd") == 0)
			// 	cmd_cd(envi, all->parse->split[1]);
			// else if (ft_strcmp(all->parse->cmd, "env") == 0)
			// 	cmd_env(envi);
			// else if (ft_strcmp(all->parse->cmd, "export") == 0)
			// 	cmd_export(envi, split, ft_splitlen(all->parse->split));
			// else if (ft_strcmp(all->parse->cmd, "unset") == 0)
			// 	cmd_unset(envi, all->parse->split[1]);
			// else if (ft_strcmp(all->parse->cmd, "exit") == 0)
			// 	cmd_exit(envi);
			// else
			// {
			// 	other_cmd(all->parse->split, envi, env);
			// 	wait(0);
			// }
		// 	all->parse = all->parse->next;
		// }
		// }
		// all->parse = par;
		// free(all->parse); // доработать фри
		// all->parse = NULL;
	}
}
