/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser_inder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:39:40 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 22:31:50 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	preparse_inredirect3(char *commands, int i, int *flag)
{
	if (commands[i] == '>' && commands[i + 1] == '>')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token '>'\n", 1);
	}
	else if (commands[i] == '>')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token\
`newline'\n", 1);
	}
	else if (commands[i] == '|' && commands[i + 1] == '>')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 1);
	}
}

void	preparse_inredirect6(char *commands, int i, int *flag)
{
	if (commands[i] == '<' && commands[i + 1] == '<')
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

void	preparse_inredirect5(char *commands, int i, int *flag)
{
	if (commands[i] == '>')
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
		preparse_inredirect6(commands, i, flag);
}

void	preparse_inredirect4(char *commands, int i, int *flag)
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
	else if (commands[i] == '>' && commands[i + 1] == '>')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token '>>'\n", 1);
	}
	if (*flag == 0)
		preparse_inredirect5(commands, i, flag);
}

int	preparse_inredirect(char *commands, int i, int *flag)
{
	i++;
	while (commands[i] == ' ' || commands[i] == '\'' || commands[i] == '\"')
		i++;
	preparse_inredirect1(commands, i, flag);
	if (*flag == 0 && ((commands[i] == '<' || commands[i] == '>')))
	{
		preparse_inredirect2(commands, i, flag);
		if (*flag == 0)
			preparse_inredirect3(commands, i, flag);
	}
	else if (*flag == 0 && (commands[i] == ' ' || \
			(commands[i] == '|' && commands[i + 1] == ' ')))
	{
		while (commands[i] == ' ')
			i++;
		preparse_inredirect4(commands, i, flag);
	}
	return (0);
}
