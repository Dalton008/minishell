/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:38:36 by lgarg             #+#    #+#             */
/*   Updated: 2021/07/19 15:31:21 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int static	ft_size(int n)
{
	unsigned int		size;

	size = 1;
	if (n < 0)
	{
		n = -n;
		size++;
	}
	while (n / 10 > 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				size;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = ft_size(n);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str[size--] = '\0';
	while (n / 10 > 0)
	{
		str[size] = (n % 10) + '0';
		n = n / 10;
		size--;
	}
	str[size] = n + '0';
	return (str);
}

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
					|| (*all)->parse->line1[(*all)->parse->i_1 + 1] == '\"') && (*all)->parse->flag != 1)
	{
		(*all)->parse->line2 = ft_itoa(g_exit_status);
		(*all)->parse->i_2 += ft_size(g_exit_status);
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

