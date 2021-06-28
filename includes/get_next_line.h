/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:24:19 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/28 13:55:55 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 1024

typedef struct s_params
{
	char		*buf;
	int			c_r;
	char		*check_n;
}				t_params;

int			get_next_line(int fd, char **line);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *str, int c);
char		*ft_strdup(const char *str);
char		*ft_strcpy(char *dst, char *src);

#endif
