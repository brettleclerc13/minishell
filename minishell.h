/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:37:10 by ehouot            #+#    #+#             */
/*   Updated: 2023/09/26 12:38:34 by ehouot           ###   ########.fr       */
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

enum	e_token
{
	WORD,
	STRING,
	FUNCTION,
	LEFT_CHEV,
	RIGHT_CHEV,
	DOUBLE_L_CHEV,
	DOUBLE_R_CHEV,
	PIPE,
	DOLLAR,
};

typedef struct s_lex
{
	char			*content;
	enum e_token	token;
	void			*next;
}				t_lex;

/* -- MINISHELL -- */

void	parsing(char *input);

/* -- LEXER -- */

void	*lexer(char **args, t_lex **list);
bool	lex_dollar(char **args, t_lex **list, int *i);
t_lex	*ft_lstnew_lex(void *content);
void	ft_lstadd_back_lex(t_lex **lst, t_lex *new);

/* -- BUILTIN -- */

void	ft_exit(void);

/* -- DEBUGGING -- */

void    print_list(t_lex *list);

#endif