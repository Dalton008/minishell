/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:44:47 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/10 19:11:54 by mjammie          ###   ########.fr       */
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
		if (line[i] == '>')
			parse->redir++;
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

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
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
	par->redir = 0;
	init_env(&envi, env);
	signal_init();
	while (42)
	{
		i = 0;
		line = readline("minishell> ");
		split = NULL;
		add_history(line);
		rl_redisplay();
		preparse(par, line);
		if (par->pipe != 0)
		{
			split = ft_split(line, '|');
			len_split = ft_splitlen(split);
			pipex(len_split, split, env);
			break ;
		}
		//PIPEX
		
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
		else
		{
			split = ft_split(line, ' ');
			len_split = ft_splitlen(split);
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
}
