/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:53:41 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/16 15:01:37 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_dir_path(char *dir, char *cwd, char *tmp)
{
	int		i;

	i = ft_strlen(cwd) + 1;
	if (dir[0] != '/')
	{
		tmp = ft_strjoin("/", dir);
		free(dir);
		dir = tmp;
		tmp = NULL;
	}
	while (--i >= 0)
	{
		if (i == (int)ft_strlen(cwd) || cwd[i] == '/')
		{
			if (cwd[i] == '/')
				i--;
			tmp = ft_substr(cwd, 0, i);
			tmp = ft_strjoin_path(tmp, dir, true);
			if (!access(tmp, F_OK | X_OK))			//if i == 0, then access(cwd...)
			{
				printf("check\n");
				free(dir);
				return (tmp);
			}
			free(tmp);
		}
	}
	return (dir);
}

static void	update_pwd(char *dir, char *cwd, t_struct *mshell, bool is_cwd)
{
	char	*tmp;
	t_var	var;

	tmp = NULL;
	if (is_cwd)
		dir = get_dir_path(dir, cwd, tmp);
	else
		dir = get_dir_path(dir, mshell->tmp_cwd, tmp);
	ft_create_var("PWD", &var);
	if (ft_varcmp_struct(&var, mshell->envp))
	{
		update_env(&var, dir, mshell, false);
		free(var.envp_var);
	}
	free(mshell->tmp_cwd);
	mshell->tmp_cwd = ft_strdup(dir);
	free(var.var);
}

static void	update_oldpwd(char *cwd, t_struct *mshell, bool is_cwd)
{
	t_var	var;

	ft_create_var("OLDPWD", &var);
	if (ft_varcmp_struct(&var, mshell->envp))
	{
		if (is_cwd)
			update_env(&var, cwd, mshell, false);
		else
			update_env(&var, mshell->tmp_cwd, mshell, false);
		free(var.envp_var);
	}
	free(var.var);
}

static int	ft_cd_contd(char *dir, char *cwd, t_struct *mshell, bool is_cwd)
{
	if (chdir(dir))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(dir);
		free(dir);
		return (1);
	}
	update_oldpwd(cwd, mshell, is_cwd);
	update_pwd(dir, cwd, mshell, is_cwd);
	free(dir);
	return (0);
}

int	ft_cd(char **args, t_struct *mshell)
{
	bool	is_cwd;
	char	*dir;
	char	cwd[PATH_MAX];

	is_cwd = true;
	if (!getcwd(cwd, sizeof(cwd)))
		is_cwd = false;
	if (ft_arraylen(args) == 1)
	{
		if (!ft_varcmp("HOME", mshell->envp))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		dir = ft_strdup(get_env_value("HOME=", mshell->envp));
	}
	else
		dir = ft_strdup(args[1]);
	if (ft_cd_contd(dir, cwd, mshell, is_cwd))
		return (1);
	return (0);
}
