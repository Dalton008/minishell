/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 22:12:19 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 22:33:16 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	for_preparser1(char *commands, int *i, int *flag)
{
	while (commands[(*i)] == ' ')
		(*i)++;
	if (!commands[(*i)])
	{
		*flag = 1;
		ft_putstr_fd("minishell: .: filename argument required\n \
.: usage: . filename [arguments]\n", 1);
	}
}

void	preparser1(char *commands, int *flag)
{
	int	i;

	i = 0;
	while (commands[i] == ' ' || commands[i] == '\'' || commands[i] == '\"')
		i++;
	if (commands[i] == '|' && commands[i + 1] == '|')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 1);
	}
	else if (commands[i] == '|')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 1);
	}
	if (commands[i] == '.' && ++i)
		for_preparser1(commands, &i, flag);
}

int	preparser(char *commands)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	preparser1(commands, &flag);
	while (commands[i] && flag == 0)
	{
		if (commands[i] == '|')
			preparse_pipes(commands, i, &flag);
		if (commands[i] == '>')
			preparse_outredirect(commands, i, &flag);
		if (commands[i] == '<')
			preparse_inredirect(commands, i, &flag);
		i++;
	}
	if (flag == 0)
		return (0);
	return (1);
}

int	main_preparser(char *commands)
{
	if (!preparser(commands))
		return (0);
	else
		g_exit_status = 258;
	return (1);
}
