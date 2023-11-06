/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:07:07 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/02 12:03:43 by ehouot           ###   ########.fr       */
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
				stash[i] = ft_strjoin_gnl(stash[i], "/", true);
			return (stash);
		}
	}
	return (stash);
}

char	*ft_add_path(t_varb *arg, char *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (arg->envp[++i])
	{
		tmp = ft_strjoin(arg->envp[i], cmd);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			free(cmd);
			return (tmp);
		}
		free(tmp);
	}
	free(cmd);
	return (NULL);
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

int	ft_execve(char *cmd, t_varb *arg, char **envp)
{
	if (arg->cmd[0] == NULL)
		ft_print_error(2);
	execve(arg->cmd[0], arg->cmd, envp);
	arg->cmd[0] = ft_add_path(arg, arg->cmd[0]);
	if (arg->cmd[0] == NULL)
		ft_print_error(6);
	execve(arg->cmd[0], arg->cmd, envp);
	return (-1);
}