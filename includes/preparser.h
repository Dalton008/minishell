/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:58:12 by lgarg             #+#    #+#             */
/*   Updated: 2021/07/24 22:20:06 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREPARSER_H
# define PREPARSER_H

int		main_preparser(char *commands);

int		preparse_inredirect(char *commands, int i, int *flag);
void	for_intder_prep_1(char *commands, int i, int *flag);
void	preparse_inredirect1(char *commands, int i, int *flag);
void	preparse_inredirect2(char *commands, int i, int *flag);
void	preparse_inredirect3(char *commands, int i, int *flag);
void	preparse_inredirect4(char *commands, int i, int *flag);
void	preparse_inredirect5(char *commands, int i, int *flag);
void	preparse_inredirect6(char *commands, int i, int *flag);

int		preparse_outredirect(char *commands, int i, int *flag);
void	for_prep_outred1(char *commands, int i, int *flag);
void	preparse_outredirect1(char *commands, int i, int *flag);
void	for_prep_outred2(char *commands, int i, int *flag);
void	preparse_outredirect2(char *commands, int i, int *flag);
void	for_prep_outred4(char *commands, int i, int *flag);
void	preparse_outredirect4(char *commands, int i, int *flag);
void	preparse_outredirect5(char *commands, int i, int *flag);

int		preparse_pipes(char *commands, int i, int *flag);

#endif