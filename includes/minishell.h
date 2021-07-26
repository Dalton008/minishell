/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:54:03 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/26 16:20:25 by mjammie          ###   ########.fr       */
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
# include "preparser.h"

int	g_exit_status;

typedef struct s_iter
{
	int	q;
	int	i;
	int	n;
	int	x;
	int	len;
	int	i_sp;
}				t_iter;

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

	char			*pt_cmd;
	int				fd_for_open;
	int				count_r;
	char			*cmd;
	char			*line;
	char			**split;
	char			**tmp;
	struct s_parse	*next;
}				t_parse;

typedef struct s_all
{
	char			*readline;
	pid_t			*pid;
	int				absol;
	int				count_fd;
	int				count_pipe;
	int				pfd[100][2];
	int				redirfd[100][2];
	char			**files_name;
	int				fd_iter;
	int				fd_iter_redir;
	int				tm_fd1;
	int				tm_fd0;
	char			**paths;
	struct s_parse	*parse;
	int				f;
}				t_all;

//main
void	init_all(t_all *all);
void	double_reverse_redir(char *line, t_all *all);

//readline
char	*readline(const char *prompt);
int		add_history(const char *string_for_history);
int		rl_on_new_line(void);
void	dl_redisplay(void);
void	rl_replace_line(const char *buffer, int val);

// commands
void	cmd_pwd(void);
void	cmd_echo(int argc, char **argv);
void	cmd_env(t_env *envi, t_all *all);
void	cmd_export(t_env *envi, char **argv, int argc, t_all *all);
void	cmd_cd(t_env *envi, char *str);
void	cmd_unset(t_env *envi, char *key);
void	other_cmd(char **cmd, t_env *envi, t_all *all);
void	cmd_exit(char **split);
void	easter_egg(void);

// utils
int		ft_atoi(char *str);
int		ft_splitlen(char **str);
int		ft_strcmp(const char *str1, const char *str2);
char	**ft_split(char const *s, char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_strncmp(const char *str1, const char *str2, size_t size);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	get_path(t_env *envi, t_all *all);
char	*join_path_to_file(char *path, char *cmd, t_all *all);
char	ft_check(char c, const char *set);
int		ft_isalnum(int c);
void	*ft_calloc(size_t number, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
void	dup_fd(t_all *all);
void	dup_fd2(t_all *all);
void	close_fd(t_all *all);
void	close_fd2(t_all *all);
int		ft_isdigit(int c);
int		check_space(char *line);
int		list_len(t_env *envi);
void	create_array(t_env *envi, char **mas, int i, int k);
void	sort_array(char **mas, int len_envi);
void	search_path(t_all *all, char *cmd);
void	cut_array(char **cmd, t_all *all, char **tmp);
char	**set_env(t_env *envi);
char	*ft_itoa(int n);
int		ft_size(int n);
char	*ft_strcpy(char *dest, char *src);
void	free_array(char **array);
t_parse	*new_node(void);
int		precheck(char *cmd);

//parse
void	parse_redir_pipe(t_all *all, char *line);
t_parse	*new_node(void);
void	work_with_cmd(t_parse *parse);
void	work_with_files(t_all *all);
void	parse_fd(char *line, t_all *all);
void	init_env(t_env	**envi, char **env);
void	init_t_iter(t_iter *iter);
int		count_with_quotes(char *line);
void	work_with_quotes(char *line, t_parse *parse);
void	work_with_files(t_all *all);

// quotes
void	quot(t_all *all, t_env *envi);
void	quotes(t_all *all, t_env *envi);
void	do_two_quotes(t_all **all, t_env *envi);
void	do_simple_quotes(t_all **all);
void	do_dollar(t_all **all, t_env *envi);

//pipe
void	pipex(t_all *all, t_env *envi);
void	dup_for_redir(t_all *all);
void	wait_and_close(t_all *all);
int		check_cmd(t_all *all, t_env *envi);

//signal
void	signal_init(void);
void	signal_init_for_child(void);
void	ctrl_d_hook(void);
void	my_sigint(int val);
void	ctrlc_in_other(int val);
void	ctrlsl_in_other(int val);

#endif