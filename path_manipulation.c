/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:12:09 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/15 09:12:33 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_extract_path(char **envp)
{
	char	**stash;
	char	*trimmed;
	int		i;

	i = -1;
	stash = NULL;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			trimmed = ft_strtrim(envp[i], "PATH=");
			stash = ft_split(trimmed, ':');
			free(trimmed);
			i = -1;
			while (stash[++i])
				stash[i] = ft_strjoin_path(stash[i], "/", true);
			return (stash);
		}
	}
	return (stash);
}

char	*ft_add_path(char *cmd, char **path)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			free(cmd);
			return (tmp);
		}
		free(tmp);
	}
	return (cmd);
}
