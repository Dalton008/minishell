/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:02:40 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/11 11:49:37 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	n;

	n = 0;
	if (!s)
		return (0);
	// if (len > ft_strlen(s))
	// 	len = ft_strlen(s);
	// result = (char *)malloc(len * sizeof(char) + 1);
	result = (char *)malloc(len - start + 1);
	if (result == 0)
		return (0);
	// if (start >= ft_strlen(s))
	// {
	// 	result[0] = 0;
	// 	return (result);
	// }
	while (start < len)
	{
		result[n] = s[start];
		n++;
		start++;
	}
	result[n] = 0;
	return (result);
}
//echo $USER > file > file3 | env | grep USER > file2