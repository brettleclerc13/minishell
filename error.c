/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:24:05 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/15 08:18:28 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	bool_print_error(char *str)
{
	if (!ft_strcmp("cwd", str))
	{
		ft_putstr_fd("minishell: cwd: Cannot retrieve cwd\n", 2);
		return (false);
	}
	if (!ft_strcmp("malloc", str))
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return (false);
	}
	return (true);
}

void	ft_put_redir_error(char *file, bool is_dir)
{
	char	*tmp;

	tmp = NULL;
	if (is_dir)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": is a directory\n", 2);
		g_var = 1;
		return ;
	}
	tmp = ft_strjoin("minishell: ", file);
	perror(tmp);
	free(tmp);
}

void	ft_put_ambiguous_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	g_var = 1;
}

void	amb_error_minus_one(char *file, t_serie **new, bool fd_in)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	g_var = 1;
	if (fd_in)
		(*new)->fd_in = -1;
	else
		(*new)->fd_out = -1;
}
