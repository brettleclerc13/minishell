/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:51:29 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/09 20:14:03 by ehouot           ###   ########.fr       */
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
	return (false);
}

int	builtin_main(char **args, t_struct *mshell)
{
	if (builtin_function(args[0]) == true)
	{
		if (!ft_strcmp(args[0], "cd"))
			ft_cd(args, mshell);
		else if (!ft_strcmp(args[0], "echo"))
			ft_echo(args);
		else if (!ft_strcmp(args[0], "env"))
			ft_env(mshell->envp);
		else if (!ft_strcmp(args[0], "exit"))
			ft_exit(args, 1);
		else if (!ft_strcmp(args[0], "export"))
			ft_export(args, mshell);
		else if (!ft_strcmp(args[0], "pwd"))
			ft_pwd();
		else if (!ft_strcmp(args[0], "unset"))
			ft_unset(args, mshell);
		exit(0);
	}
	return (0);
}
