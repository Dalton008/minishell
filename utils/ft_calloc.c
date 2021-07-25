/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:08:09 by lgarg             #+#    #+#             */
/*   Updated: 2021/07/25 18:03:59 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_calloc(size_t number, size_t size)
{
	unsigned char	*str;

	str = (unsigned char *)malloc(number * size);
	if (str == NULL)
		return (NULL);
	if (str != NULL && (number * size) != 0)
		ft_bzero(str, number * size);
	return (str);
}
