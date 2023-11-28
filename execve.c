/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:07:07 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/28 12:25:05 by brettlecler      ###   ########.fr       */
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

void	ft_put_execve_error(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	if (ft_strcmp(arg, "") == 0)
		ft_putstr_fd("", 2);
	else
		ft_putstr_fd(arg, 2);
	ft_putstr_fd(": command not found\n", 2);
}

int	ft_execve(char **cmd, char **envp)
{
	char **path;

	path = ft_extract_path(envp);
	//print_array(cmd);
	if (!cmd || !cmd[0])
	{
		ft_arrayfree(path);
		exit(0);
	}
	execve(cmd[0], cmd, envp);
	if (path == NULL)
	{
		ft_put_execve_error(cmd[0]);
		return (127);
	}
	if (ft_strncmp(cmd[0], "", 1) != 0)
	{
		cmd[0] = ft_add_path(cmd[0], path);
		execve(cmd[0], cmd, envp);
	}
	ft_put_execve_error(cmd[0]);
	ft_arrayfree(path);
	return (127);
}
