/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 12:10:33 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/14 11:20:57 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//echo "$USER > file > file2 | env | grep USER > file3

t_parse	*new_node(void)
{
	t_parse	*new;

	new = (struct s_parse *)malloc(sizeof(t_parse));
	new->count_r = 0;
	new->redir1 = 0;
	new->redir2 = 0;
	new->redir3 = 0;
	new->redir4 = 0;
	new->line = NULL;
	new->cmd = NULL;
	new->split = NULL;
	new->next = NULL;
	return (new);
}

void	print_struct(t_all *all)
{
	int	i;
	int	n;

	i = 0;
	while (all->parse)
	{
		n = 0;
		printf("STRUCT №%d\n", i);
		printf("Количество ФД=%d\n", all->count_fd);
		printf("Количество пайпов=%d\n", all->count_pipe);
		printf(">=%d\n", all->parse->redir1);
		printf("<=%d\n", all->parse->redir2);
		printf(">>=%d\n", all->parse->redir3);
		printf("<<=%d\n", all->parse->redir4);
		printf("line={%s}\n", all->parse->line);
		printf("cmd={%s}\n", all->parse->cmd);
		while (all->parse->split[n])
		{
			printf("-%s-\n", all->parse->split[n]);
			n++;
		}
		n = 0;
		printf("FILES NAME: \n");
		while (all->parse->files_name[n])
		{
			printf("}%s{\n", all->parse->files_name[n]);
			n++;
		}
		if (all->parse->next)
			all->parse = all->parse->next;
		else
			break ;
		i++;
	}
}

void	parse_redir_pipe(t_all *all, char *line)
{
	int	i;
	int	n;
	t_parse	*head;

	i = 0;
	n = 0;
	head = all->parse;
	while (line[i])
	{
		if (line[i] == '|')
		{
			all->parse->line = ft_substr(line, n, i);
			n = i + 1;
			all->parse->split = ft_split(all->parse->line, ' ');
			all->parse->next = new_node();
			all->parse = all->parse->next;
			all->count_fd++;
			all->count_pipe++;
		}
		if (line[i] == '>')
		{
			if (line[i + 1] == '>')
			{
				all->parse->count_r++;
				all->parse->redir3++;
				i++;
			}
			else
			{
				all->parse->count_r++;
				all->parse->redir1++;
			}
			all->count_fd++;
		}
		if (line[i] == '<')
		{
			if (line[i + 1] == '<')
			{
				all->parse->count_r++;
				all->parse->redir4++;
				i++;
			}
			else
			{
				all->parse->count_r++;
				all->parse->redir2++;
				all->count_fd++;
			}
		}
		i++;
		if (line[i] == '\0')
		{
			all->parse->line = ft_substr(line, n, i);
			all->parse->split = ft_split(all->parse->line, ' ');
		}
	}
	all->parse = head;
	work_with_cmd(all->parse);
	work_with_files(all->parse);
}

void	work_with_cmd(t_parse *parse)
{
	int i;

	while (parse)
	{
		i = 0;
		if (!parse->split[i + 1])
		{
			parse->cmd = ft_strdup(parse->split[i]);
		}
		else
		{
			while (parse->split[i] && parse->split[i + 1] && !ft_strchr("<>", parse->split[i + 1][0]))
			{
				parse->cmd = ft_strjoin(parse->split[i], " ");
				parse->cmd = ft_strjoin(parse->cmd, parse->split[i + 1]);
				i++;
			}
			if (!parse->cmd)
				parse->cmd = ft_strdup(parse->split[0]);
		}
		parse = parse->next;
	}
}

void	work_with_files(t_parse *parse)
{
	int	i;
	int	n;

	while (parse)
	{
		n = 0;
		i = 0;
		parse->files_name = malloc(sizeof(char *) * 5);
		parse->files_name[5] = NULL;
		while (parse->split[i] && parse->split[i + 1])
		{
			if (ft_strchr("<>", parse->split[i][0]))
			{
				parse->files_name[n] = ft_strdup(parse->split[i + 1]);
				n++;
			}
			i++;
		}
		parse = parse->next;
	}
}
