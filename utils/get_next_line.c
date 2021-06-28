/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:12:35 by mjammie           #+#    #+#             */
/*   Updated: 2021/06/28 12:12:47 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static void	free_malloc(char **line, char *buf)
{
	char	*for_free;

	for_free = *line;
	*line = ft_strjoin(*line, buf);
	free(for_free);
}

static char	*check_rem(char **line, char **rem)
{
	char	*ptr;
	char	*for_free;

	ptr = 0;
	if (*rem)
	{
		ptr = ft_strchr(*rem, '\n');
		if (ptr)
		{
			*ptr = '\0';
			*line = ft_strdup(*rem);
			for_free = *rem;
			*rem = ft_strdup(++ptr);
			free(for_free);
		}
		else
		{
			*line = ft_strdup(*rem);
			free(*rem);
			*rem = 0;
		}
	}
	else
		*line = ft_strdup("");
	return (ptr);
}

int	check_in_params(t_params *param, char **line, int fd)
{
	if (!line || fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (0);
	param->buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (param->buf == 0)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*rem;
	t_params	param;

	if (!(check_in_params(&param, line, fd)))
		return (-1);
	param.check_n = check_rem(line, &rem);
	while (!param.check_n)
	{
		param.c_r = read(fd, param.buf, BUFFER_SIZE);
		if (param.c_r == 0 || param.c_r == -1)
			break ;
		param.buf[param.c_r] = '\0';
		param.check_n = ft_strchr(param.buf, '\n');
		if (param.check_n)
		{
			*param.check_n = 0;
			rem = ft_strdup(++param.check_n);
		}
		free_malloc(line, param.buf);
	}
	free(param.buf);
	if (param.check_n)
		return (1);
	return (0);
}
