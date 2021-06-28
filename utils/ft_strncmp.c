/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:40:28 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/28 12:15:33 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strncmp(const char *str1, const char *str2, size_t size)
{
	unsigned long	n;

	n = 0;
	while ((n < size) && (str1[n] != 0 || str2[n] != 0))
	{
		if (str1[n] != str2[n])
			return ((unsigned char)str1[n] - (unsigned char)str2[n]);
		n++;
	}
	return (0);
}
