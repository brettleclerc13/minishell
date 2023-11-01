/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 09:32:26 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/31 13:55:16 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <errno.h>

# include "../Libft/libft.h"
# include "./Get_next_line/get_next_line.h"

typedef struct s_varb
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
}				t_varb;

/* -- GNL -- */

char	*get_next_line(int fd);

/* -- PIPEX -- */

int		parsing_bonus(int argc, char **argv, t_varb *var);
void	exec_cmd_bonus(char *argv, char **envp, t_varb *var);
int		ft_mandatory(char **argv, char **envp, t_varb *var);
void	ft_close(t_varb *var);

#endif
