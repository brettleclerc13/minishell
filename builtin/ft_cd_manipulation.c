/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:20:03 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/24 08:42:45 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putstr_fd("getcwd: cannot access parent directories: No such file or directory\n", 2);
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

// int	get_oldpwd(char *dir, char *cwd, t_struct *mshell, bool is_cwd)
// {
// 	if (!get_env_value("OLDPWD=", mshell->envp))
// 		return (print_cd_error("!oldpwd"));
// 	dir = ft_strdup(get_env_value("OLDPWD=", mshell->envp));
// 	if (dir[0] == '\0')
// 		ft_putstr_fd("\n", 1);
// 	else
// 		printf("%s\n", dir);
// 	update_oldpwd(cwd, mshell, is_cwd);
// 	update_pwd(dir, cwd, mshell, is_cwd);
// 	return (0);
// }