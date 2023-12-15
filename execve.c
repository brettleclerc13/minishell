/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:07:07 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/15 12:04:11 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_put_execve_error(char *arg, bool no_path)
{
	if (arg[0] == '.' && arg[1] == '/')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		if (arg[2] == '\0')
			ft_putstr_fd("./: Is a directory\n", 2);
		else
			ft_putstr_fd(": permission denied\n", 2);
	}
	else
	{
		if (no_path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": no such file or directory\n", 2);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
	}
}

static bool	check_dot_permissions(char *file)
{
	if (open(file, O_DIRECTORY) != -1)
	{
		ft_put_redir_error(file, true);
		return (false);
	}
	if (access(file, X_OK) == -1)
	{
		if (errno == EACCES)
			g_var = 126;
		else
			g_var = 1;
		ft_put_redir_error(file, false);
		return (false);
	}
	return (true);
}

static int	dot_cmd(char **cmd)
{
	if (cmd[0] && !ft_strcmp(cmd[0], ".."))
	{
		ft_put_execve_error("..", false);
		g_var = 127;
		exit(g_var);
	}
	else if ((cmd[0] && !ft_strcmp(cmd[0], ".")) && !cmd[0][1])
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		g_var = 2;
		exit(g_var);
	}
	else if (cmd[0] && !ft_strncmp(cmd[0], "./", 3))
	{
		ft_putstr_fd("minishell: ./: Is a directory\n", 2);
		g_var = 126;
		exit(g_var);
	}
	else if (cmd[0] && !ft_strncmp(cmd[0], "./", 2))
	{
		if (!check_dot_permissions(cmd[0] + 2))
			exit(g_var);
	}
	return (0);
}

int	ft_execve(t_serie *serie, char **cmd, char **envp)
{
	char	**path;

	path = NULL;
	dot_cmd(cmd);
	if (!cmd || !cmd[0] || (!ft_strcmp(cmd[0], "") \
		&& serie->first_arg_token != DOUBLE_QUOTE \
		&& serie->first_arg_token != SINGLE_QUOTE))
		exit(0);
	path = ft_extract_path(envp);
	execve(cmd[0], cmd, envp);
	if (path == NULL)
	{
		ft_put_execve_error(cmd[0], true);
		return (127);
	}
	if (ft_strncmp(cmd[0], "", 1) != 0)
	{
		cmd[0] = ft_add_path(cmd[0], path);
		execve(cmd[0], cmd, envp);
	}
	ft_put_execve_error(cmd[0], false);
	ft_arrayfree(path);
	return (127);
}
