/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:51:29 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/24 19:41:37 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_function(char *arg)
{
	if (!ft_strcmp(arg, "cd"))
		return (true);
	if (!ft_strcmp(arg, "echo"))
		return (true);
	if (!ft_strcmp(arg, "env"))
		return (true);
	if (!ft_strcmp(arg, "exit"))
		return (true);
	if (!ft_strcmp(arg, "export"))
		return (true);
	if (!ft_strcmp(arg, "pwd"))
		return (true);
	if (!ft_strcmp(arg, "unset"))
		return (true);
}

int	builtin_main(char **args, t_struct *mshell)
{
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(mshell->args, mshell));
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(mshell->args));
	if (!ft_strcmp(args[0], "env"))
		return (ft_env(mshell->envp));
	if (!ft_strcmp(args[0], "exit"))
		ft_exit(args, 1);
	if (!ft_strcmp(args[0], "export"))
		return (ft_export(args, mshell));
	if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, mshell));
	return (0);
}