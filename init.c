/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:38:35 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/06 16:34:27 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_path(char **envp)
{
	char	**path;
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
	{
		ft_putstr_fd("path/env not found in env", 2);
		return (NULL);
	}
	path = ft_split(ft_strchr(envp[i], '=') + 1, ':');
	return(path);
}

t_struct	*before_loop_init(int argc, char **envp)
{
	t_struct	*mshell;

	if (argc != 1)
		return (NULL);
	mshell = malloc(sizeof(t_struct));
	if (!mshell)
		return (NULL);
	mshell->args = malloc(sizeof(t_lex));
	if (!mshell->args)
		return (NULL);
	mshell->series = malloc(sizeof(t_serie));
	if (!mshell->series)
		return (NULL);
	mshell->pipe_count = 0;
	mshell->child = 0;
	mshell->envp = ft_arraydup(envp);
	if (!mshell->envp)
		return (NULL);
	if (ft_update_shlvl(mshell))
		return (NULL);
	mshell->path = init_path(mshell->envp);
	if (!mshell->path)
		return (NULL);
	return (mshell);
}
