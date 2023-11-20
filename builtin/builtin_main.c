/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:51:29 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/13 126:56:54 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_checker(char *args)
{
	if (!args)
		return (true);
	else if (!ft_strncmp(args, "cd", 3))
		return (true);
	else if (!ft_strncmp(args, "echo", 5))
		return (true);
	else if (!ft_strncmp(args, "env", 4))
		return (true);
	else if (!ft_strncmp(args, "exit", 5))
		return (true);
	else if (!ft_strncmp(args, "export", 7))
		return (true);
	else if (!ft_strncmp(args, "pwd", 4))
		return (true);
	else if (!ft_strncmp(args, "unset", 6))
		return (true);
	return (false);
}

int	builtin_main(char **args, t_struct *mshell, int process)
{
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, mshell));
	else if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args));
	else if (!ft_strcmp(args[0], "env"))
		return (ft_env(mshell->envp));
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(args, process);
	else if (!ft_strcmp(args[0], "export"))
		return (ft_export(args, mshell));
	else if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, mshell));
	return (0);
}

