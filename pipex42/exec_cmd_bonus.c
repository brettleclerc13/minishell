/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:59:50 by ehouot            #+#    #+#             */
/*   Updated: 2023/06/23 13:56:47 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_path(char **envp, t_varb *var)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		ft_error("command not found (no path/no env)");
	var->path = ft_split(ft_strchr(envp[i], '=') + 1, ':');
}

static char	*check_cmd(t_varb *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin("/", var->cmd[0]);
	i = -1;
	while (var->path[++i])
	{
		var->path[i] = ft_strjoin(var->path[i], tmp);
		if (access(var->path[i], F_OK) == 0)
			return (var->path[i]);
	}
	free(tmp);
	ft_error("cmd not found\n");
	return (NULL);
}

void	exec_cmd_bonus(char *argv, char **envp, t_varb *var)
{
	init_path(envp, var);
	var->cmd = ft_split(argv, ' ');
	if (execve(var->cmd[0], var->cmd, envp) == 0)
		return ;
	var->cmd[0] = check_cmd(var);
	execve(var->cmd[0], var->cmd, envp);
}
