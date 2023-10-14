/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:37:10 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/14 11:29:44 by brettlecler      ###   ########.fr       */
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

# include "./Libft/libft.h"
//# include "./pipex/pipex_bonus.h"

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

typedef struct	s_split_word
{
	int				i;
	int				start;
	enum e_token	type;
	int				skip;
}				t_sp_wd;

/* -- MINISHELL -- */

void	parsing(char *input, char **envp);

/* -- LEXER -- */

void	*lexer(char **args, char **envp, t_lex **list);
bool	lex_dollar(char **args, t_lex **list, int *i);
t_lex	*ft_lstnew_lex(void *content, enum e_token token);
void	ft_lstadd_back_lex(t_lex **lst, t_lex *new);
int		ft_split_word(char *args, t_lex **list);

/* -- PARSER -- */

void	parser(t_lex **list, char **envp);

/* -- BUILTIN -- */

void	ft_exit(void);
int		ft_echo(char **argv);

/* -- DEBUGGING -- */

void    print_list(t_lex *list);
void    print_token(t_lex *list);
void	print_tab(char *tab);
void	print_lst_tok(t_lex *list);

#endif
