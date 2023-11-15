/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:53:41 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/15 20:47:36 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(char *dir, t_struct *mshell)
{
	t_var	var;

	ft_create_var("PWD", &var);
	if (!ft_varcmp_struct(&var, mshell->envp))
		mshell->envp = add_env_value("PWD=", dir, mshell->envp);
	else
	{
		update_env(&var, dir, mshell, false);
		free(var.envp_var);
	}
	free(var.var);
}

static void	update_oldpwd(char *cwd, t_struct *mshell)
{
	t_var	var;

	ft_create_var("OLDPWD", &var);
	if (!ft_varcmp_struct(&var, mshell->envp))
		mshell->envp = add_env_value("OLDPWD=", cwd, mshell->envp);
	else
	{
		update_env(&var, cwd, mshell, false);
		free(var.envp_var);
	}
	free(var.var);
}

int	ft_cd_contd(char *dir, char *cwd, t_struct *mshell)
{
	if (chdir(dir))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(dir);
		free(dir);
		return (1);
	}
	update_oldpwd(cwd, mshell);
	update_pwd(dir, mshell);
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
		if (!ft_varcmp("HOME", mshell->envp))
		{
			ft_putstr_fd("minishell: cd: home directory not listed in env\n", 2);
			return (1);
		}
		dir = ft_strdup(get_env_value("HOME=", mshell->envp));
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