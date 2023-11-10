/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:38:35 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/10 15:56:51 by ehouot           ###   ########.fr       */
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
	t_struct	*mshell = NULL;

	if (argc != 1)
		return (NULL);
	mshell = malloc(sizeof(t_struct));
	if (!mshell)
		return (NULL);
	mshell->args = NULL;
	mshell->series = NULL;
	mshell->pipe_count = 0;
	mshell->child = 0;
	mshell->tmp_fd = STDIN_FILENO;
	mshell->envp = ft_arraydup(envp);
	if (!mshell->envp)
		return (NULL);
	if (ft_update_shlvl(mshell))
		return (NULL);
	return (mshell);
}
