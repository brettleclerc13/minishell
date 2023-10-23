/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:37:10 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/23 09:56:08 by brettlecler      ###   ########.fr       */
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

# include "../Libft/libft.h"
# include "../pipex42/pipex_bonus.h"

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
};

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

typedef struct	s_struct
{
	char		**envp;
	t_lex		*args;
	int			pipe_count;
	char		**path;
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

/* -- MINISHELL -- */
bool		parsing(char *input, t_struct *mshell);
t_struct	*before_loop_init(int argc, char **envp);
char		**init_path(char **envp);

/* -- LEXER -- */
void	*lexer(char **args, char **envp, t_lex **list);
bool	lex_dollar(char **args, t_lex **list, int *i);
t_lex	*ft_lstnew_lex(void *content, enum e_token token);
void	ft_lstadd_back_lex(t_lex **lst, t_lex *new);
int		ft_split_word(char *args, t_lex **list);

/* -- PARSER -- */
void	parser(t_lex **list, char **envp);
int		ft_count_pipe(t_struct *mshell);

/* -- DEBUGGING -- */
void    print_list(t_lex *list);
void    print_token(t_lex *list);
void	print_string(char *tab);
void	print_lst_tok(t_lex *list);
void	print_array(char **array);

/* -- BUILTINS -- */
int		ft_echo(char **argv);
int		ft_cd(int argc, char **argv, t_struct *mshell);
int		ft_cd_contd(char *dir, char *cwd, t_struct *mshell);
int		ft_pwd(void);
int		ft_env(char **envp);
int		ft_export(char **argv, t_struct *mshell);

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
bool	ft_isvar(char *arg);
char	*get_env_var(char *line);
int		ft_varcmp(t_var *var, char **envp);
void	ft_create_var(char *arg, t_var *var);
char	*ft_varjoin(char *s1, char *s2);

/* -- ARRAY MANIPULATIONS -- */
char	**ft_arraydup(char **array);
int		ft_arraylen(char **array);
char	**ft_arrayadd(char *newline, char **array);
void	ft_arrayfree(char **array);

/* -- EXECUTE -- */
void	ft_execute(t_struct *mshell);

#endif
