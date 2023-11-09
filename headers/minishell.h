/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:37:10 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/09 10:46:07 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define COLOR_PROMPT "\033[44;1mmin\033[47;1mish\033[41;1mell"
# define COLOR_RESET "\033[0m"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <signal.h>
#include <sys/wait.h>

# include "../Libft/libft.h"
# include "../pipex42/pipex_bonus.h"

extern int	g_var;

enum	e_token
{
	DOUBLE_L_CHEV,
	DOUBLE_R_CHEV,
	LEFT_CHEV,
	RIGHT_CHEV,
	PIPE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	WORD,
	STRING,
	FUNCTION,
	DOLLAR,
	ZERO,
	END,
};

extern void	rl_replace_line(const char *text, int clear_undo);

typedef struct	s_separator
{
	char	*str;
	int		num;
}				t_sep;

typedef struct s_lex
{
	char			*content;
	enum e_token	token;
	void			*next;
}				t_lex;

typedef struct	s_serie
{
	char			**cmd;
	enum e_token	fd_out_token;
	enum e_token	cmd_token;
	bool			is_pipe;
	int				fd_in;
	int				fd_out;
	char			*hd_limiter;
	bool			hd;
	void			*next;
}				t_serie;

typedef struct	s_count_red
{
	int	double_left;
	int	double_right;
	int	left;
	int	right;
}				t_count_red;

typedef struct	s_struct
{
	char		**envp;
	t_lex		*args;
	t_serie		*series;
	int			pipe_count;
	bool		check_valid;
	pid_t		child;
	t_count_red	redir;
}				t_struct;

typedef struct	s_split_word
{
	int				i;
	int				start;
	enum e_token	type;
	int				skip;
}				t_sp_wd;

typedef struct	s_var
{
	char		*var;
	char		*envp_var;
	int			symbol;
	int			varlen;
}			t_var;

typedef struct s_fd
{
	int		infile;
	int		outfile;
	int		pfd[2];
	int		fdhd[2];
	int		tmpfd;
	int		here_doc;
	pid_t	child;
	char	**path;
	char	**cmd;
}				t_fd;

/* -- MINISHELL -- */
void		parsing(char *input, t_struct **mshell);
t_struct	*before_loop_init(int argc, char **envp);
char		**init_path(char **envp);

/* -- LEXER -- */
t_lex	*lexer(char **args, t_lex **list);
bool	lex_dollar(char **args, t_lex **list, int *i);
t_lex	*ft_lstnew_lex(void *content, enum e_token token);
void	ft_lstadd_back_lex(t_lex **lst, t_lex *new);
int		ft_split_word(char *args, t_lex **list);

/* -- PARSER -- */
bool	parser(t_lex **list, char **envp);
int		ft_count_pipe(t_struct *mshell);
void	check_dollar(t_lex **list, char **envp);

/* -- SERIES -- */
void	serie_creation(t_struct *mshell, t_serie **series);
t_serie	*ft_lstnew_serie(t_lex *args, int i, bool ispipe);
char	**ft_serie_array(t_lex *args, t_serie **new, int i);
void	ft_lstadd_back_serie(t_serie **series, t_serie *new);
t_serie	*ft_lstlast_serie(t_serie *series);

/* -- DEBUGGING -- */
void    print_list(t_lex *list);
void	print_lst_serie(t_serie *series);
void	print_string(char *tab);
void	print_lst_tok(t_lex *list);
void	print_array(char **array);
void	print_lst_serie(t_serie *series);

/* -- BUILTINS -- */
int		builtin_main(char **args, t_struct *mshell);
bool	builtin_function(char *arg);
int		ft_cd(char **args, t_struct *mshell);
int		ft_cd_contd(char *dir, char *cwd, t_struct *mshell);
int		ft_echo(char **args);
int		ft_env(char **envp);
void	ft_exit(char **args, pid_t child);
int		ft_export(char **args, t_struct *mshell);
int		ft_pwd(void);
int		ft_unset(char **args, t_struct *mshell);

/* -- PRINT EXPORT -- */
void	ft_print_export(char **envp);
void	ft_sort_ascii(char **array);
bool	ft_put_export_error(char *arg);

/* -- ENVP MANIPULATIONS -- */
char	**add_env_value(char *var, char *value, char **envp);
char	*get_env_value(char *var, char **envp);
void	update_env_value(char *var, char *new_value, char **envp);
int		ft_update_shlvl(t_struct *mshell);
char	**add_env_str(char *arg, char **envp);
void	update_env(t_var *var, char *new_value, t_struct *mshell);

/* -- ENV VARIABLE MANIPULATIONS -- */
char	*get_env_var(char *line);
int		ft_varcmp(t_var *var, char **envp);
void	ft_create_var(char *arg, t_var *var);
char	*ft_varjoin(char *s1, char *s2);
bool	ft_varcmp_vtwo(char *var, char **envp);

/* -- ARRAY MANIPULATIONS -- */
char	**ft_arraydup(char **array);
int		ft_arraylen(char **array);
char	**ft_arrayadd(char *newline, char **array);
void	ft_arrayfree(char **array);
char	**ft_arrayremove(char *removeline, char **array);

/* -- EXECUTE -- */
void	ft_execute(t_struct *mshell);
int		ft_execve(char **cmd, char **envp);

/* -- REDIRECTION -- */
int	ft_count_redir(t_lex *args);
int	ft_set_redirections(t_lex *tmp, t_serie **new);

/* -- SIGNALS -- */
void    signals_types(char *input, bool isheredoc);

#endif
