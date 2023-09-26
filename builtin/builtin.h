/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:58:50 by brettlecler       #+#    #+#             */
/*   Updated: 2023/09/26 17:29:14 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
 
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stddef.h>

# define true 1
# define false 0

# include "../Libft/libft.h"

int	ft_cd(int argc, char **argv, char **envp);
char	*get_home_dir(char **envp);
int	ft_echo(char **argv);

#endif
