/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:15:20 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/12 17:40:55 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_envi(t_env *envi, t_all *all)
{
	int		i;
	int		n;
	int		k;
	int		z;
	char	**mas;
	char	*tmp;
	t_env	*head;
	int		flag;
	int		len_envi;
	int		len_value;

	i = 0;
	n = 0;
	k = 0;
	flag = 0;
	head = envi;
	len_envi = 0;
	len_value = 0;
	while (envi)
	{
		len_envi++;
		envi = envi->next;
	}
	envi = head;
	mas = malloc(sizeof(char *) * (len_envi + 1));
	mas[len_envi] = NULL;
	while (envi)
	{
		n = 0;
		k = 0;
		len_value = ft_strlen(envi->value);
		mas[i] = malloc(len_value + 3);
		mas[i][len_value + 2] = '\0';
		while (envi->value[n])
		{
			if (envi->value[n] == '=')
			{
				mas[i][k] = envi->value[n];
				k++;
				mas[i][k] = '"';
			}
			else
				mas[i][k] = envi->value[n];
			n++;
			k++;
			if (envi->value[n] == 0 && ft_strchr(envi->value, '='))
				mas[i][k] = '"';
		}
		envi = envi->next;
		i++;
	}
	i = 0;
	while (mas[i] && flag == 0)
	{
		flag = 1;
		i = 0;
		while (i < len_envi - 1)
		{
			if (ft_strcmp(mas[i], mas[i + 1]) > 0)
			{
				tmp = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = tmp;
				flag = 0;
			}
			i++;
		}
		len_envi--;
	}
	i = 0;
	z = 0;
	while (z < all->parse->count_r)
	{
		all->fd_iter++;
		z++;
	}
	dup_fd(all);
	while (mas[i])
	{
		printf("declare -x %s\n", mas[i]);
		i++;
	}
	close_fd(all);
}

int	check_key(t_env *envi, char	*str)
{
	int	len;

	while (envi)
	{
		if (ft_strncmp(envi->value, str, ft_strlen(str)) == 0)
			return (1);
		envi = envi->next;
	}
	return (0);
}

void	cmd_export(t_env *envi, char **argv, int argc, t_all *all)
{
	char	**split;
	int		i;
	int		len_value;
	int		n;
	int		k;
	t_env	*head;
	int		z;

	i = 0;
	n = 0;
	k = 1;
	head = envi;
	len_value = 0;
	// z = 0;
	// while (z < all->parse->count_r)
	// {
	// 	all->fd_iter++;
	// 	z++;
	// }
	// // all->fd_iter++;
	// dup_fd(all);
	if (argc >= 2 && all->parse->count_r == 0)
	{
		while (k < argc)
		{
			i = 0;
			n = 0;
			envi = head;
			if (ft_strchr(argv[k], '='))
			{
				split = ft_split(argv[k], '=');
				if (check_key(envi, split[0]))
				{
					while (ft_strncmp(envi->value, split[0], ft_strlen(split[0])) != 0)
						envi = envi->next;
					if (ft_strchr(envi->value, '='))
					{
						while (envi->value[i] != '=')
							i++;
					}
					else
					{
						envi->value = ft_strjoin(envi->value, "=");
						i++;
					}
					i++;
					len_value = ft_strlen(split[1]);
					while (len_value--)
					{
						envi->value[i] = split[1][n];
						n++;
						i++;
					}
					envi->value[i] = '\0';
				}
				else
				{
					while (envi->next)
						envi = envi->next;
					envi->next = malloc(sizeof(t_env));
					envi = envi->next;
					envi->value = ft_strdup(argv[k]);
					envi->next = NULL;
				}
			}
			else
			{
				while (envi->next)
					envi = envi->next;
				envi->next = malloc(sizeof(t_env));
				envi = envi->next;
				envi->value = ft_strdup(argv[k]);
				envi->next = NULL;
			}
			k++;
		}
	}
	else if (argc == 1 || all->parse->count_r != 0)
		sort_envi(envi, all);
}
