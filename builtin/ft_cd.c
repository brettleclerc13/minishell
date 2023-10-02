/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:53:41 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/02 19:06:08 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "builtin.h"

int	ft_cd_contd(char *dir, char *cwd, char **envp)
{
	if (chdir(dir))
	{
		ft_putstr_fd("cd error: ", 2);
		perror(dir);
		return (1);
	}
	if (!get_env_value("OLD_PWD=", envp))
	{
		add_env_value("OLD_PWD=", cwd, envp);
	}
	else
	{
		update_env_value("OLD_PWD=", cwd, envp);
	}
	update_env_value("PWD=", dir, envp);
	return (0);
}

int	ft_cd(int argc, char **argv, char **envp)
{
	char	*dir;
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd("cwd: Cannot retrieve cwd", 2);
		perror(cwd);
		return (1);
	}
	if (argc == 2)
	{
		dir = get_env_value("HOME=", envp);
		printf("dir: %s\n", dir);
		if (!dir)
		{
			ft_putstr_fd("cd: Home directory not listed in env\n", 2);
			return (1);
		}
	}
	else
		dir = argv[2];
	if (ft_cd_contd(dir, cwd, envp))
		return (1);
	return (0);
}

/*
pwd
oldpwd
	printf("dir: %s\n", dir);
	printf("argv[2]: %s\n", argv[2]);
*/