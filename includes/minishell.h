/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:54:03 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/18 15:47:41 by mjammie          ###   ########.fr       */
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
# include <signal.h>
# include <errno.h>

int	g_exit_status;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_parse
{
	int				i_1;
	int				i_2;
	char			*line1;
	char			*line2;
	char			**split2;
	int				flag;

	int				redirfd[100][2];
	int				count_r;
	int				redir1; //>
	int				redir2; //<
	int				redir3; //>>
	int				redir4; //<<
	char			*cmd;
	char			*line;
	char			**files_name;
	char			**split;
	struct s_parse	*next;
}				t_parse;

typedef struct s_pipe
{
	int		pfd[100][2];
	char	**cmd;
	char	**path;
	char	*pt;
	int		i;
	int		op;
	int		file;
}				t_pipe;

typedef struct s_all
{
	pid_t			*pid;
	int				error;
	int				absol;
	int				count_fd;
	int				count_pipe;
	int				pfd[100][2];
	int				fd_iter;
	int				tm_fd1;
	int				tm_fd0;
	struct s_parse	*parse;
	int				f;
}				t_all;

//readline
char	*readline(const char *prompt);
int		add_history(const char *string_for_history);
int		rl_on_new_line(void);
void	dl_redisplay(void);
void	rl_replace_line(const char *buffer, int val);

// commands
void	cmd_pwd(t_env *envi, t_all *all);
char	*cmd_echo(int argc, char **argv, t_env *envi, t_all *all);
void	cmd_env(t_env *envi, t_all *all);
void	cmd_export(t_env *envi, char **argv, int argc, t_all *all);
void	cmd_cd(t_env *envi, char *str);
void	cmd_unset(t_env *envi, char *key);
void	other_cmd(char **cmd, t_env *envi, t_all *all);
void	cmd_exit(t_env *envi);

// utils
int		ft_splitlen(char **str);
int		ft_strcmp(const char *str1, const char *str2);
char	**ft_split(char const *s, char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_strncmp(const char *str1, const char *str2, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**get_path(t_env *envi);
char	*join_path_to_file(char *path, char *cmd, t_all *all);
char	ft_check(char c, const char *set);
int		ft_isalnum(int c);
void	*ft_calloc(size_t number, size_t size);
void	ft_bzero(void *s, size_t n);

//parse
void	parse_redir_pipe(t_all *all, char *line);
void	print_struct(t_all *all);//временная для вывода
t_parse	*new_node(void);
void	work_with_cmd(t_parse *parse);
void	work_with_files(t_parse *parse);

// quotes
void	quot(t_all *all, t_env *envi);
void	quotes(t_all *all, t_env *envi);
void	do_two_quotes(t_all **all, t_env *envi);
void	do_simple_quotes(t_all **all, t_env *envi);
void	do_dollar(t_all **all, t_env *envi);

//init
void	init_env(t_env	**envi, char **env);
void	work_with_fd(char *line, t_all *all);
void	dup_fd(t_all *all);
void	close_fd(t_all *all);

//pipe
int		pipex(int count_pipes, char **split, char **env, t_all *all, t_env *envi);

//signal
void	signal_init(void);
void	signal_init_for_child(void);
void	ctrl_d_hook(void);

#endif