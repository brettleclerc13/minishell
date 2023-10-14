/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 09:32:26 by ehouot            #+#    #+#             */
/*   Updated: 2023/06/19 10:27:10 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <errno.h>

# include "./Libft/libft.h"

typedef struct s_var
{
	int		fd[2];
	int		pfd[2];
	pid_t	child;
	char	**path;
	char	**cmd;
}				t_var;

/* -- PIPEX -- */

int		main(int argc, char **argv, char **envp);
void	parsing(int argc, char **argv, t_var *var);
void	exec_cmd(char **argv, char **envp, t_var *var);

#endif