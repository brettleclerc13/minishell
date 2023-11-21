/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:38:35 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/21 14:53:03 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_oldpwd(t_struct *mshell)
{
	t_var	var;

	ft_create_var("OLDPWD", &var);
	if (!ft_varcmp_struct(&var, mshell->envp))
		mshell->envp = add_env_str("OLDPWD", mshell->envp);
	else
	{
		update_env(&var, NULL, mshell, false);
		free(var.envp_var);
	}
	free(var.var);
}

void	ft_update_shlvl(t_struct *mshell)
{
	char	*shlvl;

	shlvl = ft_itoa(ft_atoi(get_env_value("SHLVL=", mshell->envp)) + 1);
	update_env_value("SHLVL=", shlvl, mshell->envp);
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

bool	init_envp(t_struct *mshell, char **envp)
{
	char	cwd[PATH_MAX];
	
	mshell->envp = NULL;
	mshell->tmp_cwd = NULL;
	if (!getcwd(cwd, sizeof(cwd)))
		return (bool_print_error("cwd"));
	else
		mshell->tmp_cwd = ft_strdup(cwd);
	if (!envp[0])
	{
		mshell->envp = ft_calloc(5, sizeof(char *));
		if (!mshell->envp)
			return (bool_print_error("malloc"));
		mshell->envp[0] = ft_strdup("OLDPWD");
		mshell->envp[1] = ft_strjoin("PWD=", cwd);
		mshell->envp[2] = ft_strdup("SHLVL=1");
		mshell->envp[3] = ft_strdup("_");
	}
	else
	{
		mshell->envp = ft_arraydup(envp);
		ft_update_shlvl(mshell);
	}
	return (true);
}

t_struct	*before_loop_init(int argc, char **envp)
{
	t_struct	*mshell;

	if (argc != 1)
	{
		ft_putstr_fd("minishell: argv: no arguments accepted\n", 2);
		return (NULL);
	}
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
	if (!init_envp(mshell, envp))
		return (NULL);
	init_oldpwd(mshell);
	return (mshell);
}
