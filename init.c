/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:38:35 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/15 20:03:04 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_shlvl(t_struct *mshell)
{
	char	*shlvl;

	shlvl = ft_itoa(ft_atoi(get_env_value("SHLVL=", mshell->envp)) + 1);
	update_env_value("SHLVL=", shlvl, mshell->envp);
	free(shlvl);
}

char	**init_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
	{
		ft_putstr_fd("path/env not found in env", 2);
		return (NULL);
	}
	path = ft_split(ft_strchr(envp[i], '=') + 1, ':');
	return (path);
}

bool	init_envp(t_struct *mshell)
{
	char	pwd[PATH_MAX];
	
	mshell->envp = NULL;
	if (!getcwd(pwd, sizeof(pwd)))
	{
		ft_putstr_fd("minishell: cwd: cannot retrieve cwd", 2);
		return (false);
	}
	mshell->envp = ft_calloc(5, sizeof(char *));
	if (!mshell->envp)
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return (false);
	}
	mshell->envp[0] = ft_strdup("OLDPWD");
	mshell->envp[1] = ft_strjoin("PWD=", pwd);
	mshell->envp[2] = ft_strdup("SHLVL=1");
	mshell->envp[3] = ft_strdup("_");
	return (true);
}

t_struct	*before_loop_init(int argc, char **envp)
{
	t_struct	*mshell;

	if (argc != 1)
		return (NULL);
	mshell = malloc(sizeof(t_struct));
	if (!mshell)
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return (NULL);
	}
	mshell->args = NULL;
	mshell->series = NULL;
	mshell->pipe_count = 0;
	mshell->tmp_fd = STDIN_FILENO;
	if (!envp[0])
	{
		if (!init_envp(mshell))
			return (NULL);
	}
	else
	{
		mshell->envp = ft_arraydup(envp);
		ft_update_shlvl(mshell);
	}
	return (mshell);
}
