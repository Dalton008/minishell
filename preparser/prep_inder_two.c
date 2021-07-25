/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_inder_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:42:15 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 22:35:15 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	for_intder_prep_1(char *commands, int i, int *flag)
{
	if ((commands[i] == '|' && commands[i + 1] == '<') \
		|| (commands[i] == '|' && commands[i + 1] == '>'))
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 1);
	}
}

void	preparse_inredirect1(char *commands, int i, int *flag)
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
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 1);
	}
	else if (commands[i] == '|' && commands[i + 1] == '|')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 1);
	}
	else if (commands[i] == '|' && commands[i + 1] == '|' \
										&& commands[i + 2] == '|')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 1);
	}
	if (*flag == 0)
		for_intder_prep_1(commands, i, flag);
}

void	preparse_inredirect2(char *commands, int i, int *flag)
{
	if (commands[i] == '<' && commands[i + 1] == '<' \
									&& commands[i + 2] == '<')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 1);
	}
	else if (commands[i] == '<' && commands[i + 1] == '<')
	{
		*flag = 1;
		ft_putstr_fd("minishell: syntax error near unexpected token\
`newline'\n", 56);
	}
}
