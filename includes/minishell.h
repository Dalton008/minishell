/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:54:03 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/02 19:23:14 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_parse
{
	int	pipe;
}				t_parse;

typedef struct s_history //история?
{
	char				*value;
	struct s_history	*next;
	struct s_history	*prev;
}				t_history;

typedef struct s_pipe
{
	char	**cmd;
	char	**path;
	char	*pt;
	int		i;
	int		op;
	int		file;
}				t_pipe;

// commands
void	cmd_pwd(t_env *envi);
char	*cmd_echo(int argc, char **argv, t_env *envi);
void	cmd_env(t_env *envi);
void	cmd_export(t_env *envi, char **argv, int argc);
void	cmd_cd(t_env *envi, char *str);
void	cmd_unset(t_env *envi, char *key);
void	check_cmd(char **cmd, t_env *envi, char **env);
void	cmd_exit(t_env *envi);

// utils
int		ft_strcmp(const char *str1, const char *str2);
char	**ft_split(char const *s, char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *str1, const char *str2, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *str, int c);

//init
void	init_env(t_env	**envi, char **env);

//pipe
int		pipex(int argc, char **argv, char **env);

#endif