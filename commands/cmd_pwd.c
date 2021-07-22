/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:52:31 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/22 14:29:06 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_pwd(void)
{
	char	*buf;
	char	*pwd;

	buf = NULL;
	pwd = getcwd(buf, 0);
	printf("%s\n", pwd);
	free(pwd);
	free(buf);
	g_exit_status = 0;
}
