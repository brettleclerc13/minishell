/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:37:10 by ehouot            #+#    #+#             */
/*   Updated: 2023/09/25 18:47:04 by brettlecler      ###   ########.fr       */
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

typedef struct s_lex
{
	char	*content;
	int		token;
	void	*next;
}				t_lex;

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
	COMMENT,
};

/* -- MINISHELL -- */

void	parsing(char *input);

/* -- LEXER -- */

t_lex	*lexer(char **args, t_lex *list);
t_lex	*ft_lstnew_lex(void *content);
void	ft_lstadd_back_lex(t_lex **lst, t_lex *new);

/* -- BUILTIN -- */

void	ft_exit(void);
int		ft_echo(char **argv);

#endif