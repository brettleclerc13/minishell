/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:53:41 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/23 19:09:45 by brettlecler      ###   ########.fr       */
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
	if (ft_varcmp_struct(&var, mshell->envp))
	{
		update_env(&var, dir, mshell, false);
		free(var.envp_var);
	}
	free(mshell->tmp_cwd);
	mshell->tmp_cwd = ft_strdup(dir);
	free(var.var);
	free(dir);
}

void	update_oldpwd(char *cwd, t_struct *mshell, bool is_cwd)
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

int	print_cd_error(char	*error)
{
	if (!ft_strcmp(error, ">args"))
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!ft_strcmp(error, "!home"))
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (!ft_strcmp(error, "!oldpwd"))
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	return (0);
}

static int	ft_cd_contd(char *dir, char *cwd, t_struct *mshell, bool is_cwd)
{
	if (dir[0] == '\0')
		return (0);
	if (!ft_strncmp(dir, "-", 2))
		return (get_oldpwd(dir, cwd, mshell, is_cwd));
	if (chdir(dir))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(dir);
		free(dir);
		return (1);
	}
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
		return (print_cd_error(">args"));
	if (ft_arraylen(args) == 1 || !ft_strncmp(args[1], "~", 2))
	{
		if (!get_env_value("HOME=", mshell->envp))
			return (print_cd_error("!home"));
		dir = ft_strdup(get_env_value("HOME=", mshell->envp));
	}
	else
		dir = ft_strdup(args[1]);
	if (ft_cd_contd(dir, cwd, mshell, is_cwd))
		return (1);
	return (0);
}


// while (--i >= 0)
// 	{
// 		if (i == (int)ft_strlen(cwd) || cwd[i] == '/')
// 		{
// 			tmp = ft_substr(cwd, 0, i);
// 			printf("tmp in dir path: %s\n", tmp);
// 			tmp = ft_strjoin_path(tmp, dir, true);
// 			if (!access(tmp, F_OK | X_OK))
// 			{
// 				free(dir);
// 				return (tmp);
// 			}
// 			free(tmp);
// 		}
// 	}
// 	return (dir);

	// while (--i >= 0)
	// {
	// 	if (cwd[i] == '/' && (cwd[i - 1] == '.' && cwd[i - 2] == '.'))
	// 		continue;
	// 	if (cwd[i] == '/' && (cwd[i - 1] != '.' && cwd[i - 2] != '.'))
	// 	{
	// 		printf("entering here again\n");
	// 		tmp = ft_substr(cwd, 0, i);
	// 		if (!access(tmp, F_OK | X_OK))
	// 		{
	// 			printf("and again\n");
	// 			free(dir);
	// 			return (tmp);
	// 		}
	// 		free(tmp);
	// 	}
	// 	if (i - 1 == -1)
	// 	{
	// 		free(dir);
	// 		return (ft_strdup("/"));
	// 	}
	// }
	//return (dir);