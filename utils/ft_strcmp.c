/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 17:52:54 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/28 12:14:33 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	unsigned long	n;

	n = 0;
	while (str1[n] != 0 || str2[n] != 0)
	{
		if (str1[n] != str2[n])
			return ((unsigned char)str1[n] - (unsigned char)str2[n]);
		n++;
	}
	return (0);
}
