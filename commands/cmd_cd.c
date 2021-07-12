/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 18:23:52 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/12 11:45:05 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_cd(t_env *envi, char *str)
{
	char	*oldpwd;
	t_env	*head;
	int		dir;
	char	*buf;
	char 	*pwd;
	
	buf = NULL;
	head = envi;
	oldpwd = getcwd(buf, 0);
	dir = chdir(str);
	pwd = getcwd(buf, 0); //выделяет память!
	if (dir == -1)
	{
		printf("No such file or directory\n");
		return ;
	}
	else
	{
		while (envi)
		{
			if (ft_strncmp(envi->value, "OLDPWD", 6) == 0)
			{
				envi->value[0] = 0;
				envi->value = ft_strjoin(envi->value, "OLDPWD=");
				envi->value = ft_strjoin(envi->value, oldpwd);
				break ;
			}
			envi = envi->next;
		}
		envi = head;
		while (envi)
		{
			if (ft_strncmp(envi->value, "PWD", 3) == 0)
			{
				envi->value[0] = 0;
				envi->value = ft_strjoin(envi->value, "PWD=");
				envi->value = ft_strjoin(envi->value, pwd);
				break ;
			}
			envi = envi->next;
		}
	}
}
