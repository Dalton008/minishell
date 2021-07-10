/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:31:42 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/09 15:17:30 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
