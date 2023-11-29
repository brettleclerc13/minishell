/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:37:10 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/29 14:50:18 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # define COLOR_PROMPT "\033[44;1mmin\033[47;1mish\033[41;1mell"
// # define COLOR_RESET "\033[0m"

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
# include <sys/wait.h>
# include <termios.h>

# include "Libft/libft.h"

extern int	g_var;

enum	e_token
{
	DOUBLE_L_CHEV,		// --> 0
	DOUBLE_R_CHEV,		// --> 1
	LEFT_CHEV,			// --> 2
	RIGHT_CHEV,			// --> 3
	PIPE,				// --> 4
	SINGLE_QUOTE,		// --> 5
	DOUBLE_QUOTE,		// --> 6
	WORD,				// --> 7
	DOLLAR,				// --> 8
	ZERO,				// --> 9
	SKIP,				// --> 10
	END,				// --> 11
};

extern void	rl_replace_line(const char *text, int clear_undo);

typedef struct s_separator
{
	char	*str;
	int		num;
}			t_sep;

typedef struct s_lex
{
	char			*content;
	enum e_token	token;
	void			*next;
}					t_lex;

typedef struct s_serie
{
	char			**cmd;
	enum e_token	fd_out_token;
	bool			is_pipe;
	int				pipe_hd[2];
	int				fd_in;
	int				fd_out;
	char			*hd_limiter;
	bool			hd;
	pid_t			pid;
	void			*prev;
	void			*next;
}					t_serie;

typedef struct s_count_red
{
	int	double_left;
	int	double_right;
	int	left;
	int	right;
}		t_count_red;

typedef struct s_struct
{
	char		**envp;
	t_lex		*args;
	t_serie		*series;
	int			pipe_count;
	bool		check_valid;
	int			tmp_fd;
	char		*tmp_cwd;
	t_count_red	redir;
}				t_struct;

typedef struct s_split_word
{
	int				i;
	int				start;
	enum e_token	type;
	int				skip;
}					t_sp_wd;

typedef struct s_var
{
	char		*var;
	char		*envp_var;
	int			symbol;
	int			varlen;
}				t_var;

typedef struct s_dollar
{
	char		*content;
	int			variable;
	void		*next;
}				t_dollar;

/* -- INIT -- */
t_struct	*before_loop_init(int argc, char **envp);
char		**init_path(char **envp);
bool		init_envp(t_struct *mshell, char **envp);
void		init_oldpwd(t_struct *mshell);

/* -- LEXER -- */
t_lex		*lexer(char **args, t_lex **list);
t_lex		*ft_lstnew_lex(void *content, enum e_token token);
void		ft_lstadd_back_lex(t_lex **lst, t_lex *new);
int			ft_split_word(char *args, t_lex **list);

/* -- PARSER -- */
bool		parsing(char *input, t_struct **mshell);
bool		parser(t_lex **list, char **envp);

/* -- DOLLAR PARSER -- */
bool		check_dollar(t_lex **list, char **envp);
void		d_lst_creation(t_dollar **d_lst, char *content);
char		*d_lst_expansion(t_dollar *d_lst, char **envp);
bool		is_specialchar(char c);
void		d_lst_string(t_dollar **d_lst, char *content, int *i, int *start);
void		d_lst_pid_exitstatus(t_dollar **d_lst, char *content, int *i, int *start);
void		d_lst_lonedol(t_dollar **d_lst, int *i, int *start);
void		d_lst_var(t_dollar **d_lst, char *content, int *i, int *start);
bool		is_dollar(char *s);

/* -- SERIES -- */
bool		serie_creation(t_lex *args, t_serie **series);
bool		serie_addition(t_serie **series, t_lex *args, int count, bool ispipe);
t_serie		*ft_lstnew_serie(t_lex *args, int count, bool ispipe);
char		**ft_serie_array(t_lex *args, t_serie **new, int count);
void		ft_lstadd_back_serie(t_serie **series, t_serie *new);
t_serie		*ft_lstlast_serie(t_serie *series);

/* -- DEBUGGING -- */
void		print_list(t_lex *list);
void		print_lst_serie(t_serie *series);
void		print_string(char **tab);
void		print_lst_tok(t_lex *list);
void		print_array(char **array);
void		print_lst_serie(t_serie *series);
void		print_prev_serie(t_serie *series);

/* -- BUILTINS -- */
int			builtin_main(char **args, t_struct *mshell, int process);

int			ft_cd(char **args, t_struct *mshell);
void		update_pwd(char *dir, char *cwd, t_struct *mshell, bool is_cwd);
void		update_oldpwd(char *cwd, t_struct *mshell, bool is_cwd);
bool		is_previous_levels(char *dir);
char		*get_previous_level_dir(char *dir, char *cwd);
char		*get_dir_path(char *dir, char *cwd, char *tmp);
int			print_cd_error(char	*error, char *dir);

bool		builtin_checker(char *args);
int			ft_echo(char **args);
int			ft_env(char **envp);
void		ft_exit(char **args, pid_t child);
int			ft_export(char **args, t_struct *mshell);
int			ft_pwd(t_struct *mshell);
int			ft_unset(char **args, t_struct *mshell);

/* -- PRINT EXPORT -- */
void		ft_print_export(char **envp);
void		ft_sort_ascii(char **array);
bool		ft_put_export_error(char *arg);

/* -- ENVP -- */
char		**add_env_value(char *var, char *value, char **envp);
char		*get_env_value(char *var, char **envp);
void		update_env_value(char *var, char *new_value, char **envp);
void		ft_update_shlvl(t_struct *mshell);
char		**add_env_str(char *arg, char **envp);
void		update_env(t_var *var, char *new_value, t_struct *mshell, bool is_equal);
void		ft_add_to_envp(char *arg, t_struct *mshell);

/* -- ENV VARIABLE-- */
char		*get_env_var(char *line);
int			ft_varcmp_struct(t_var *var, char **envp);
void		ft_create_var(char *arg, t_var *var);
char		*ft_varjoin(char *s1, char *s2);
bool		ft_varcmp(char *var, char **envp);

/* -- ARRAY -- */
char		**ft_arraydup(char **array);
int			ft_arraylen(char **array);
char		**ft_arrayadd(char *newline, char **array);
void		ft_arrayfree(char **array);
char		**ft_arrayremove(char *removeline, char **array);

/* -- EXECUTE -- */
void		ft_execute(t_struct *mshell);
pid_t		ft_execute_serie(t_serie *serie, int start, t_struct *mshell);
pid_t		ft_fork_execution(t_serie *serie, t_struct *mshell, int start);
int			ft_execve(char **cmd, char **envp);
void		set_child_input(t_serie *serie, int pfd[], int previous_fd, int start);
void		set_child_output(t_serie *serie, int pfd[]);
void		set_parent_io(int pfd[], t_struct *mshell);
void		ft_waitpid(t_serie *series);

/* -- REDIRECTION -- */
int			ft_count_redir(t_lex *args);
void		ft_set_redirections(t_lex *tmp, t_serie **new);
void		ft_here_doc(t_lex *tmp, t_serie **serie, int nb_heredoc);
int			ft_count_heredoc(t_lex *args);

/* -- SIGNALS -- */
void		signals_types(void);
void		ft_gvar_result(int process_result);
void		heredoc_signals(void);
void		ignore_signals(void);
void		sig_in_command(void);
void		ft_termios(bool set);

/* -- FREE -- */
void		ft_free_serie(t_serie *series);
void		ft_free_lex(t_lex *lex);
void		ft_free_serie_lex(t_serie *series, t_lex *args);

/* -- ERROR -- */
bool		bool_print_error(char *str);

#endif
