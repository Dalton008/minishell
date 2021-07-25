/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:28:13 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 11:45:51 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	init_env(t_env	**envi, char **env)
{
	int		size_env;
	int		i;
	t_env	*head;

	i = 0;
	size_env = env_size(env);
	(*envi) = malloc(sizeof(t_env));
	head = (*envi);
	while (env[i])
	{
		(*envi)->value = ft_strdup(env[i]);
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			(*envi)->value[6] = (*envi)->value[6] + 1;
		}
		(*envi)->next = NULL;
		i++;
		if (env[i])
		{
			(*envi)->next = malloc(sizeof(t_env));
			(*envi) = (*envi)->next;
		}
	}
	(*envi) = head;
}
