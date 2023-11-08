/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:07:07 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/07 18:26:13 by ehouot           ###   ########.fr       */
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
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])))
		{
			trimmed = ft_strtrim(envp[i], "PATH=");
			stash = ft_split(trimmed, ':');
			free(trimmed);
			i = -1;
			while (stash[++i])
				stash[i] = ft_strjoin_parser(stash[i], "/", true);
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

// int	ft_execve(char *cmd, t_varb *arg, char **envp)
// {
// 	arg->cmd = ft_split(cmd, ' ');
// 	if (arg->cmd[0] == NULL)
// 		ft_print_error(2);
// 	execve(arg->cmd[0], arg->cmd, envp);
// 	arg->cmd[0] = ft_add_path(arg, arg->cmd[0]);
// 	if (arg->cmd[0] == NULL)
// 		ft_print_error(6);
// 	execve(arg->cmd[0], arg->cmd, envp);
// 	return (-1);
// }
void	ft_put_execve_error(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": command not found\n", 2);
}

int	ft_execve(char **cmd, char **envp)
{
	char **path;

	path = ft_extract_path(envp);
	execve(cmd[0], cmd, envp);
	if (path == NULL)
	{
		ft_put_execve_error(cmd[0]);
		return (-1);
	}
	cmd[0] = ft_add_path(cmd[0], path);
	execve(cmd[0], cmd, envp);
	ft_put_execve_error(cmd[0]);
	ft_arrayfree(path);
	return (-1);
}
