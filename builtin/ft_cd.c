/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:53:41 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/13 12:08:59 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_contd(char *dir, char *cwd, t_struct *mshell)
{
	if (chdir(dir))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(dir);
		free(dir);
		return (1);
	}
	if (!get_env_value("OLDPWD=", mshell->envp))
		mshell->envp = add_env_value("OLDPWD=", cwd, mshell->envp);
	else
		update_env_value("OLDPWD=", cwd, mshell->envp);
	update_env_value("PWD=", dir, mshell->envp);
	free(dir);
	return (0);
}

int	ft_cd(char **args, t_struct *mshell)
{
	char	*dir;
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd("minishell: cwd: cannot retrieve cwd", 2);
		return (1);
	}
	if (ft_arraylen(args) == 1)
	{
		dir = ft_strdup(get_env_value("HOME=", mshell->envp));
		if (!dir)
		{
			ft_putstr_fd("minishell: cd: home directory not listed in env\n", 2);
			return (1);
		}
	}
	else
		dir = ft_strdup(args[1]);
	if (ft_cd_contd(dir, cwd, mshell))
		return (1);
	return (0);
}

/*
pwd
oldpwd
	printf("dir: %s\n", dir);
	printf("argv[2]: %s\n", argv[2]);
*/