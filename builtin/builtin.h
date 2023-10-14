/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:58:50 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/13 13:31:20 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
 
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdarg.h>
# include <limits.h>

# define true 1
# define false 0

# include "../Libft/libft.h"
# include "../minishell.h"

typedef struct	s_struct
{
	char		**envp;
}	t_struct;

/* -- BULTINS -- */
int		ft_echo(char **argv);
int		ft_cd(int argc, char **argv, t_struct *mshell);
int		ft_cd_contd(char *dir, char *cwd, t_struct *mshell);
int		ft_pwd(void);
int		ft_env(t_struct *mshell);

/* -- ENVP MANIPULATIONS -- */
char	**add_env_value(char *var, char *value, char **envp);
char	*get_env_value(char *var, char **envp);
void	update_env_value(char *var, char *new_value, char **envp);
char	**ft_arraydup(char **array);
int		ft_arraylen(char **array);
char	**ft_arrayadd(char *newline, char **array);
void	ft_arrayfree(char **array);
int		ft_update_shlvl(t_struct *mshell);
int		ft_export(char **argv, t_struct *mshell);

/* -- MINISHELL -- */
void	parsing(char *input, t_struct *mshell);

#endif
