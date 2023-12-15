/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:53:41 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/15 08:46:07 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(char *dir, char *cwd, t_struct *mshell, bool is_cwd)
{
	char	*tmp;
	t_var	var;

	tmp = NULL;
	if (is_previous_levels(dir) && is_cwd)
		dir = get_previous_level_dir(dir, cwd);
	else if (is_previous_levels(dir) && !is_cwd)
		dir = get_previous_level_dir(dir, mshell->tmp_cwd);
	else if (is_cwd)
		dir = get_dir_path(dir, cwd, tmp);
	else
		dir = get_dir_path(dir, mshell->tmp_cwd, tmp);
	ft_create_var("PWD", &var);
	if (ft_varcmp(var.var, mshell->envp))
		update_env(&var, dir, mshell, false);
	free(mshell->tmp_cwd);
	mshell->tmp_cwd = ft_strdup(dir);
	free(var.var);
	free(dir);
}

void	update_oldpwd(char *cwd, t_struct *mshell, bool is_cwd)
{
	t_var	var;

	ft_create_var("OLDPWD", &var);
	if (ft_varcmp(var.var, mshell->envp))
	{
		if (is_cwd)
			update_env(&var, cwd, mshell, false);
		else
			update_env(&var, mshell->tmp_cwd, mshell, false);
	}
	free(var.var);
}

static int	cd_hyphen(char **dir, char *cwd, t_struct *mshell, bool is_cwd)
{
	if (!get_env_value("OLDPWD=", mshell->envp))
		return (print_cd_error("!oldpwd", *dir));
	free(*dir);
	*dir = ft_strdup(get_env_value("OLDPWD=", mshell->envp));
	if (*dir[0] == '\0')
	{
		ft_putstr_fd("\n", 1);
		update_oldpwd(cwd, mshell, is_cwd);
		free(*dir);
		return (0);
	}
	return (5);
}

static int	ft_cd_contd(char *dir, char *cwd, t_struct *mshell, bool is_cwd)
{
	int	cd_hyphen_ret;

	cd_hyphen_ret = 0;
	if (dir[0] == '\0')
	{
		free(dir);
		return (0);
	}
	if (!ft_strncmp(dir, "-", 2))
	{
		cd_hyphen_ret = cd_hyphen(&dir, cwd, mshell, is_cwd);
		if (cd_hyphen_ret == 5)
			printf("%s\n", dir);
		else
			return (cd_hyphen_ret);
	}
	if (chdir(dir))
		return (print_cd_error("!chdir", dir));
	update_oldpwd(cwd, mshell, is_cwd);
	update_pwd(dir, cwd, mshell, is_cwd);
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
	if (ft_arraylen(args) > 2)
		return (print_cd_error(">args", NULL));
	if (ft_arraylen(args) == 1 || !ft_strncmp(args[1], "~", 2))
	{
		if (!get_env_value("HOME=", mshell->envp))
			return (print_cd_error("!home", NULL));
		dir = ft_strdup(get_env_value("HOME=", mshell->envp));
	}
	else
		dir = ft_strdup(args[1]);
	if (ft_cd_contd(dir, cwd, mshell, is_cwd))
		return (1);
	return (0);
}
