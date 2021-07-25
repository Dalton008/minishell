/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:31:36 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 14:36:47 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_init(void)
{
	signal(SIGINT, my_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	signal_init_for_child(void)
{
	signal(SIGINT, ctrlc_in_other);
	signal(SIGQUIT, ctrlsl_in_other);
	signal(SIGTSTP, SIG_IGN);
}
