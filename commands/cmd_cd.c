/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 18:23:52 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/26 16:43:22 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_oldpwd(t_env **envi, char *oldpwd)
{
	char	*ff;

	ff = NULL;
	(*envi)->value[0] = 0;
	ff = (*envi)->value;
	(*envi)->value = ft_strjoin((*envi)->value, "OLDPWD=");
	free(ff);
	ff = (*envi)->value;
	(*envi)->value = ft_strjoin((*envi)->value, oldpwd);
	free(ff);
}

void	change_pwd(t_env **envi, char *pwd)
{
	char	*ff;

	ff = NULL;
	(*envi)->value[0] = 0;
	ff = (*envi)->value;
	(*envi)->value = ft_strjoin((*envi)->value, "PWD=");
	free(ff);
	ff = (*envi)->value;
	(*envi)->value = ft_strjoin((*envi)->value, pwd);
	free(ff);
}

void	set_pwd(t_env **envi, char *oldpwd, char *pwd, t_env *head)
{
	while (envi)
	{
		if (ft_strncmp((*envi)->value, "OLDPWD", 6) == 0)
		{
			change_oldpwd(envi, oldpwd);
			break ;
		}
		(*envi) = (*envi)->next;
	}
	(*envi) = head;
	while ((*envi))
	{
		if (ft_strncmp((*envi)->value, "PWD", 3) == 0)
		{
			change_pwd(envi, pwd);
			break ;
		}
		(*envi) = (*envi)->next;
	}
	g_exit_status = 0;
}

void	free_pwd(char *buf, char *pwd, char *oldpwd)
{
	free(buf);
	free(pwd);
	free(oldpwd);
}

void	cmd_cd(t_env *envi, char *str)
{
	char	*oldpwd;
	t_env	*head;
	int		dir;
	char	*buf;
	char	*pwd;

	buf = NULL;
	head = envi;
	oldpwd = getcwd(buf, 0);
	dir = chdir(str);
	pwd = getcwd(buf, 0);
	if (dir == -1)
	{
		free_pwd(buf, pwd, oldpwd);
		printf("No such file or directory\n");
		g_exit_status = 1;
		return ;
	}
	else
		set_pwd(&envi, oldpwd, pwd, head);
	g_exit_status = 0;
	free_pwd(buf, pwd, oldpwd);
}
