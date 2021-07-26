/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:15:20 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/26 16:19:36 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	only_export(t_env *envi)
{
	int		i;
	int		k;
	char	**mas;

	i = 0;
	k = 0;
	mas = malloc(sizeof(char *) * (list_len(envi) + 1));
	mas[list_len(envi)] = NULL;
	create_array(envi, mas, i, k);
	printf("tut\n");
	sort_array(mas, list_len(envi));
	while (mas[i])
	{
		printf("declare -x %s\n", mas[i]);
		i++;
	}
	i = 0;
	while (mas[i])
	{
		free(mas[i]);
		i++;
	}
	free(mas);
	g_exit_status = 0;
}

int	check_key(t_env *envi, char	*str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	while (envi)
	{
		if (ft_strncmp(envi->value, str, len) == 0)
			return (1);
		envi = envi->next;
	}
	return (0);
}

void	last_item(t_env *envi, int k, char **argv)
{
	while (envi->next)
		envi = envi->next;
	envi->next = malloc(sizeof(t_env));
	envi = envi->next;
	envi->value = ft_strdup(argv[k]);
	envi->next = NULL;
}

void	work_with_equals(t_env *envi, char **split)
{
	int		len_value;
	t_iter	iter;

	len_value = 0;
	iter.i = 0;
	iter.n = 0;
	while (ft_strncmp(envi->value, split[0], ft_strlen(split[0])) != 0)
		envi = envi->next;
	if (ft_strchr(envi->value, '='))
		while (envi->value[iter.i++] != '=')
			;
	else
	{
		envi->value = ft_strjoin(envi->value, "=");
		iter.i++;
	}
	if (!split[1])
		envi->value[iter.i] = '\0';
	else
	{
		len_value = ft_strlen(split[1]);
		while (len_value--)
			envi->value[iter.i++] = split[1][iter.n++];
		envi->value[iter.i] = '\0';
	}
}

void	cmd_export(t_env *envi, char **argv, int argc, t_all *all)
{
	char	**split;
	int		k;

	k = 1;
	if (argc >= 2 && all->parse->count_r == 0)
	{
		while (k < argc)
		{
			if (ft_strchr(argv[k], '='))
			{
				split = ft_split(argv[k], '=');
				if (check_key(envi, split[0]))
					work_with_equals(envi, split);
				else
					last_item(envi, k, argv);
			}
			else if (!check_key(envi, argv[k]))
				last_item(envi, k, argv);
			k++;
		}
		free_array(split);
		g_exit_status = 0;
	}
	else if (argc == 1 || all->parse->count_r != 0)
		only_export(envi);
}
