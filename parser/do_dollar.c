/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:38:36 by lgarg             #+#    #+#             */
/*   Updated: 2021/07/18 20:57:14 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	if_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

void	get_key(t_all **all, char *key)
{
	int i;

	i = 0;
	while (if_key((*all)->parse->line1[(*all)->parse->i_1]))
		key[i++] = (*all)->parse->line1[(*all)->parse->i_1++];
	key[i] = '\0';
}

void	do_dollar(t_all **all, t_env *envi)
{
	char	*key;
	int		key_len; 

	key = ft_strdup("");
	(*all)->parse->i_1++;
	if ((*all)->parse->line1[(*all)->parse->i_1] == '?' && (!(*all)->parse->line1[(*all)->parse->i_1 + 1] \
					|| (*all)->parse->line1[(*all)->parse->i_1 + 1] == '\"') && (*all)->parse->flag == 1)
	{
		printf("%d\n", g_exit_status);
		(*all)->parse->i_1++;
	}
	else if (!(*all)->parse->line1[(*all)->parse->i_1])
		printf("$\n");
	else
	{
		get_key(all, key);
		key_len = ft_strlen(key);
		while (envi)
		{
			if (ft_strncmp(key, envi->value, key_len) == 0)
			{
				ft_strcpy((*all)->parse->line2 + (*all)->parse->i_2, envi->value + key_len + 1);
				(*all)->parse->i_2 += ft_strlen(envi->value + key_len + 1);
			}
			envi = envi->next;
		}
	free (key);
	}
}

