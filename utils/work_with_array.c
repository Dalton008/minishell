/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 16:02:03 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/26 16:22:59 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_array(t_env *envi, char **mas, int i, int k)
{
	int	n;

	while (envi)
	{
		n = 0;
		k = 0;
		mas[i] = malloc(ft_strlen(envi->value) + 3);
		mas[i][ft_strlen(envi->value) + 2] = '\0';
		while (envi->value[n])
		{
			if (envi->value[n] == '=')
			{
				mas[i][k++] = envi->value[n];
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
}

void	sort_array(char **mas, int len_envi)
{
	int		i;
	char	*tmp;
	int		flag;

	i = 0;
	flag = 0;
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
}
