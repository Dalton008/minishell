/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:24:03 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/28 12:12:45 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_strcpy(char *dst, char *src)
{
	int	n;

	n = 0;
	if (!dst || !src)
		return (0);
	while (src[n])
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = 0;
	return (dst);
}

char	*ft_strdup(const char *str)
{
	char	*n_str;
	int		n;
	int		len;

	n = 0;
	len = 0;
	while (str[len])
		len++;
	n_str = (char *) malloc(sizeof(*str) * (len + 1));
	if (n_str == 0)
		return (0);
	while (str[n] != 0)
	{
		n_str[n] = str[n];
		n++;
	}
	n_str[n] = 0;
	return (n_str);
}

char	*ft_strchr(const char *str, int c)
{
	int		n;

	n = 0;
	while (str[n])
	{
		if (str[n] == c)
			return ((char *)str + n);
		n++;
	}
	if (c == 0)
		return ((char *)str + n);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		len_str1;
	int		len_str2;
	int		n;
	int		i;

	n = 0;
	i = 0;
	if (!s1 || !s2)
		return (0);
	len_str1 = ft_strlen(s1);
	len_str2 = ft_strlen(s2);
	result = (char *)malloc(len_str1 + len_str2 + 1);
	if (result == 0)
		return (0);
	while (n < len_str1)
	{
		result[n] = s1[n];
		n++;
	}
	while (i < len_str2)
		result[n++] = s2[i++];
	result[n] = 0;
	return (result);
}
