/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:44:47 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/06 21:33:42 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	preparse(t_parse *parse, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
			parse->pipe++;
		i++;
	}
}

int	ft_splitlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// void	ctrlc(int val)
// {
	// int	pid;
	// int	status;

	// pid = waitpid(0, &status, WNOHANG);
	// if (val == SIGINT)
	// {
	// 	write(1, "\n", 1);
	// 	if (pid)
	// 		write(1, "minishell> ", 11);
	// }
	// return ;
// }

int	main(int argc, char **argv, char **env)
{
	t_parse	*par;
	char	*line;
	char	**split;
	t_env	*envi;
	int		i;
	int		len_split;
	int		z;

	z = 0;
	(void)argc;
	(void)argv;
	par = malloc(sizeof(t_parse));
	par->pipe = 0;
	init_env(&envi, env);
	signal_init();
	while (42)
	{
		// signal(SIGINT, ctrlc);
		i = 0;
		line = readline("minishell> ");
		split = NULL;
		add_history(line);
		rl_redisplay();
		// //PIPEX
		
		// preparse(par, line);
		// split = ft_split(line, '|');
		// len_split = ft_splitlen(split);
		// if (par->pipe != 0)
		// {
		// 	// pipex(par->pipe, split, env);
		// 	pipex(len_split, split, env);
		// }
		// // break ;

		// // PIPEX

		split = ft_split(line, ' ');
		len_split = ft_splitlen(split);
		// while (split[i])
		// {
		// 	printf("%s\n", split[i]);
		// 	i++;
		// }
		// signal_cheker();
		if (ft_strcmp(split[0], "pwd") == 0)
			cmd_pwd(envi);
		else if (ft_strcmp(split[0], "echo") == 0)
			cmd_echo(len_split, split, envi);
		else if (ft_strcmp(split[0], "cd") == 0)
			cmd_cd(envi, split[1]);
		else if (ft_strcmp(split[0], "env") == 0)
			cmd_env(envi);
		else if (ft_strcmp(split[0], "export") == 0)
			cmd_export(envi, split, len_split);
		else if (ft_strcmp(split[0], "unset") == 0)
			cmd_unset(envi, split[1]);
		else if (ft_strcmp(split[0], "exit") == 0)
			cmd_exit(envi);
		else
		{
			other_cmd(split, envi, env);
			wait(0);
		}
	}
}
