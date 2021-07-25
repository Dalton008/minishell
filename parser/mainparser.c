/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 12:10:33 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/24 21:12:07 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parse	*new_node(void)
{
	t_parse	*new;

	new = (struct s_parse *)malloc(sizeof(t_parse));
	new->count_r = 0;
	new->line = NULL;
	new->cmd = NULL;
	new->split = NULL;
	new->next = NULL;
	return (new);
}

void	if_pipe(char *line, t_iter *iter, t_all *all)
{
	if (line[iter->i] == '"' || line[iter->i] == '\'')
		iter->q++;
	if (line[iter->i] == '|' && line[iter->i - 1] != '"' && iter->q % 2 != 0)
	{
		all->parse->line = ft_substr(line, iter->n, iter->i);
		iter->n = iter->i + 1;
		if (!ft_strchr(line, '"'))
			all->parse->split = ft_split(all->parse->line, ' ');
		else
			work_with_quotes(all->parse->line, all->parse);
		all->parse->next = new_node();
		all->parse = all->parse->next;
		all->count_fd++;
		all->count_pipe++;
	}
}

void	if_redir(char *line, t_iter *iter, t_all *all)
{
	if (line[iter->i] == '>')
	{
		if (line[iter->i + 1] == '>')
		{
			all->parse->count_r++;
			iter->i++;
		}
		else
			all->parse->count_r++;
		all->count_fd++;
	}
	if (line[iter->i] == '<')
	{
		if (line[iter->i + 1] == '<')
		{
			all->parse->count_r++;
			iter->i++;
		}
		else
		{
			all->parse->count_r++;
			all->count_fd++;
		}
	}
}

void	parse_redir_pipe(t_all *all, char *line)
{
	t_iter	iter;
	t_parse	*head;

	head = all->parse;
	init_t_iter(&iter);
	while (line[iter.i])
	{
		if_pipe(line, &iter, all);
		if_redir(line, &iter, all);
		iter.i++;
		if (line[iter.i] == '\0')
		{
			all->parse->line = ft_substr(line, iter.n, iter.i);
			if (!ft_strchr(line, '"'))
				all->parse->split = ft_split(all->parse->line, ' ');
			else
				work_with_quotes(all->parse->line, all->parse);
		}
	}
	all->parse = head;
	work_with_cmd(all->parse);
	work_with_files(all);
}

void	work_with_cmd(t_parse *parse)
{
	int		i;
	char	*for_free;

	while (parse)
	{
		i = 0;
		if (!parse->split[i + 1])
			parse->cmd = ft_strdup(parse->split[i]);
		else
		{
			while (parse->split[i] && parse->split[i + 1] && \
				!ft_strchr("<>", parse->split[i + 1][0]))
			{
				for_free = parse->cmd;
				parse->cmd = ft_strjoin(parse->split[i], " ");
				free(for_free);
				for_free = parse->cmd;
				parse->cmd = ft_strjoin(parse->cmd, parse->split[i + 1]);
				free(for_free);
				i++;
			}
			if (!parse->cmd)
				parse->cmd = ft_strdup(parse->split[0]);
		}
		parse = parse->next;
	}
}
