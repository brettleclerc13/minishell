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
	if (!ft_strcmp(args, "cd"))
		return (true);
	else if (!ft_strcmp(args, "echo"))
		return (true);
	else if (!ft_strcmp(args, "env"))
		return (true);
	else if (!ft_strcmp(args, "exit"))
		return (true);
	else if (!ft_strcmp(args, "export"))
		return (true);
	else if (!ft_strcmp(args, "pwd"))
		return (true);
	else if (!ft_strcmp(args, "unset"))
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

