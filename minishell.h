/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:37:10 by ehouot            #+#    #+#             */
/*   Updated: 2023/06/27 13:46:40 by ehouot           ###   ########.fr       */
/*   Updated: 2023/07/10 08:41:48 by ehouot           ###   ########.fr       */
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
	LEFT_CHEV,
	RIGHT_CHEV,
	DOUBLE_L_CHEV,
	DOUBLE_R_CHEV,
	PIPE,
	COMMENT,
};

/* -- MINISHELL -- */

int		main(int argc, char **argv, char **envp);
void	parsing(char *input);

/* -- BUILTIN -- */

void	ft_exit(void);

#endif