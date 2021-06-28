/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 13:15:20 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/28 20:53:58 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_envi(t_env *envi)
{
	int		i;
	char	**mas;
	char	*tmp;
	t_env	*head;
	int		flag;
	int		len_envi;

	i = 0;
	flag = 0;
	head = envi;
	len_envi = 0;
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
		mas[i] = ft_strdup(envi->value);
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
	while (mas[i])
	{
		printf("declare -x %s\n", mas[i]);
		i++;
	}
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

void	cmd_export(t_env *envi, char **argv, int argc)
{
	char	**split;
	int		i;
	int		len_value;
	int		n;

	i = 0;
	n = 0;
	len_value = 0;
	if (argc == 2)
	{
		if (ft_strchr(argv[1], '='))
		{
			split = ft_split(argv[1], '=');
			if (check_key(envi, split[0]))
			{
				while (ft_strncmp(envi->value, split[0], ft_strlen(split[0])) != 0)
					envi = envi->next;
				while (envi->value[i] != '=')
					i++;
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
				envi->value = ft_strdup(argv[1]);
				envi->next = NULL;
			}
		}
	}
	else if (argc == 1)
		sort_envi(envi);
}
