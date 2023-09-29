/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:58:50 by brettlecler       #+#    #+#             */
/*   Updated: 2023/09/29 12:15:19 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
 
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stddef.h>
# include <limits.h>

# define true 1
# define false 0

# include "../Libft/libft.h"

int		ft_cd(int argc, char **argv, char **envp);
int		ft_cd_contd(char *dir, char *cwd, char **envp);
char	*get_env_value(char *var, char **envp);
int		ft_echo(char **argv);

#endif
