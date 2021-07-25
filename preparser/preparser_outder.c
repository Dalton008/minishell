/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser_outder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:43:39 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 22:32:12 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	preparse_outredirect2(char *commands, int i, int *flag)
{
	if (commands[i] == '>' && commands[i + 1] == '>' && commands[i + 2] == '>')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 1);
	}
	else if (commands[i] == '>' && commands[i + 1] == '>')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 1);
	}
	else if (commands[i] == '<' && commands[i + 1] == '>')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `<>'\n", 1);
	}
	else if (commands[i] == '<' && commands[i + 1] == '<' \
										&& commands[i + 2] == '<')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `<<<'\n", 1);
	}
	if (*flag == 0)
		for_prep_outred2(commands, i, flag);
}

void	for_prep_outred4(char *commands, int i, int *flag)
{
	if (commands[i] == '<' && commands[i + 1] == '>')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `<>'\n", 1);
	}
	else if (commands[i] == '>' && commands[i + 1] == '>')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 1);
	}
}

void	preparse_outredirect4(char *commands, int i, int *flag)
{
	if (!commands[i])
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token\
`newline'\n", 1);
	}
	else if (commands[i] == '|' && commands[i + 1] == '|')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 1);
	}
	else if (commands[i] == '|')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 1);
	}
	if (*flag == 0)
		for_prep_outred4(commands, i, flag);
}

void	preparse_outredirect5(char *commands, int i, int *flag)
{
	if (commands[i] == '>')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 1);
	}
	else if (commands[i] == '<' && commands[i + 1] == '<' \
										&& commands[i + 2] == '<')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `<<<'\n", 1);
	}
	else if (commands[i] == '<' && commands[i + 1] == '<')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 1);
	}
	else if (commands[i] == '<')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 1);
	}
}

int	preparse_outredirect(char *commands, int i, int *flag)
{
	i++;
	while (commands[i] == ' ' || commands[i] == '\'' || commands[i] == '\"')
		i++;
	preparse_outredirect1(commands, i, flag);
	if (*flag == 0 && ((commands[i] == '<' || commands[i] == '>')))
		preparse_outredirect2(commands, i, flag);
	else if (*flag == 0 && (commands[i] == ' ' || \
			(commands[i] == '|' && commands[i + 1] == ' ')))
	{
		while (commands[i] == ' ')
			i++;
		preparse_outredirect4(commands, i, flag);
		if (*flag == 0)
			preparse_outredirect5(commands, i, flag);
	}
	return (0);
}
