/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 19:32:02 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/25 19:41:56 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	precheck(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	check_cmd(t_all *all, t_env *envi)
{
	if (ft_strcmp(all->parse->split2[0], "pwd") == 0)
		cmd_pwd();
	else if (ft_strcmp(all->parse->split2[0], "echo") == 0)
		cmd_echo(ft_splitlen(all->parse->split2), all->parse->split2);
	else if (ft_strcmp(all->parse->split2[0], "cd") == 0)
		cmd_cd(envi, all->parse->split[1]);
	else if (ft_strcmp(all->parse->split2[0], "env") == 0)
		cmd_env(envi, all);
	else if (ft_strcmp(all->parse->split2[0], "export") == 0)
		cmd_export(envi, all->parse->split2, \
			ft_splitlen(all->parse->split), all);
	else if (ft_strcmp(all->parse->split2[0], "unset") == 0)
		cmd_unset(envi, all->parse->split[1]);
	else if (ft_strcmp(all->parse->split2[0], "exit") == 0)
		cmd_exit(all->parse->split2);
	if (precheck(all->parse->split2[0]))
		return (1);
	return (0);
}
