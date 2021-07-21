/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:52:31 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/20 12:05:28 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_pwd(t_env *envi, t_all *all)
{
	char	*buf;
	char	*pwd;
	// int		z;

	// z = 1;
	// while (z < all->parse->count_r)
	// {
	// 	all->fd_iter_redir++;
	// 	z++;
	// }
	// dup_fd(all);
	buf = NULL;
	pwd = getcwd(buf, 0);
	printf("%s\n", pwd);
	free(pwd);
	free(buf);
	// close_fd(all);
	g_exit_status = 0;
}
