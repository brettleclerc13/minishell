/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:20:03 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/15 08:30:02 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_cd_error(char	*error, char *dir)
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
		free(dir);
		return (1);
	}
	if (!ft_strcmp(error, "!chdir"))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(dir);
		free(dir);
		return (1);
	}
	return (0);
}

static char	*dir_update(char *dir, char *tmp, char *cwd, bool start_slash)
{
	if (!ft_strncmp(dir, ".", 2))
	{
		free(dir);
		return (ft_strdup(cwd));
	}
	if (start_slash)
	{
		tmp = ft_strjoin("/", dir);
		free(dir);
		dir = tmp;
		tmp = NULL;
		return (dir);
	}
	else
	{
		tmp = ft_substr(dir, 0, ft_strlen(dir) - 1);
		free(dir);
		dir = tmp;
		tmp = NULL;
		return (dir);
	}
}

char	*get_dir_path(char *dir, char *cwd, char *tmp)
{
	if (!ft_strncmp(dir, "/", 2))
		return (dir);
	if (!ft_strncmp(dir, ".", 2))
		dir = dir_update(dir, tmp, cwd, true);
	if (dir[0] != '/')
		dir = dir_update(dir, tmp, cwd, true);
	if (dir[ft_strlen(dir) - 1] == '/')
		dir = dir_update(dir, tmp, cwd, false);
	if (!ft_strncmp(cwd, "/", 2) && dir[0] == '/')
		tmp = ft_strdup(dir);
	else
		tmp = ft_strjoin(cwd, dir);
	if (!access(tmp, F_OK | X_OK))
	{
		free(dir);
		return (tmp);
	}
	free(tmp);
	return (dir);
}

char	*get_previous_level_dir(char *dir, char *cwd)
{
	char	tmp_cwd[PATH_MAX];

	if (!getcwd(tmp_cwd, sizeof(tmp_cwd)))
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		free(dir);
		return (ft_strjoin(cwd, "/.."));
	}
	else
	{
		free(dir);
		return (ft_strdup(tmp_cwd));
	}
}

bool	is_previous_levels(char *dir)
{
	if (!ft_strncmp(dir, "..", 3))
		return (true);
	else if (dir[ft_strlen(dir) - 1] == '.' && dir[ft_strlen(dir) - 2] == '.' \
		&& dir[ft_strlen(dir) - 3] == '/')
		return (true);
	else if (dir[ft_strlen(dir) - 1] == '/' && dir[ft_strlen(dir) - 2] == '.' \
		&& dir[ft_strlen(dir) - 3] == '.' && dir[ft_strlen(dir) - 4] == '/')
		return (true);
	return (false);
}
