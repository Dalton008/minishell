/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_outder_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:45:13 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 22:31:26 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	for_prep_outred1(char *commands, int i, int *flag)
{
	if (commands[i] == '|' && commands[i + 1] == '|' \
									&& commands[i + 2] == '|')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 1);
	}
	else if (commands[i] == '|' && commands[i + 1] == '|')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 1);
	}
}

void	preparse_outredirect1(char *commands, int i, int *flag)
{
	if (!commands[i])
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token\
 `newline'\n", 1);
	}
	else if (commands[i] == '|' && !commands[i + 1])
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token\
`newline'\n", 1);
	}
	else if (commands[i] == '|' && commands[i + 1] == '>')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 1);
	}
	else if (commands[i] == '|' && commands[i + 1] == '<')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 1);
	}
	if (*flag == 0)
		for_prep_outred1(commands, i, flag);
}

void	for_prep_outred2(char *commands, int i, int *flag)
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
