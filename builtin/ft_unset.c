/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:56:07 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/08 20:58:36 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove_from_envp(char *arg, t_struct *mshell)
{
	char	*envp_var;
	int		i;

	i = -1;
	while (mshell->envp[++i])
	{
		envp_var = get_env_var(mshell->envp[i]);
		if (!ft_strncmp(arg, envp_var, ft_strlen(envp_var) + 1))
		{
			mshell->envp = ft_arrayremove(mshell->envp[i], mshell->envp);
			free(envp_var);
			return ;
		}
		free(envp_var);
	}
}

bool	ft_put_unset_error(char *arg)
{
	ft_putstr_fd("minishell: unset: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return (false);
}

static bool	ft_isunsetarg(char *arg)
{
	int	i;

	i = 0;
	if (!*arg)
		return (ft_put_unset_error(arg));
	if (arg[0] && (!ft_isalpha(arg[i]) && arg[i] != '_'))
		return (ft_put_unset_error(arg));
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (ft_put_unset_error(arg));
	}
	return (true);
}

int	ft_unset(char **args, t_struct *mshell)
{
	int	i;
	int	result;

	i = 0;
	mshell->envp = mshell->envp;
	result = 0;
	while (args[++i])
	{
		if (!ft_isunsetarg(args[i]))
		{
			result = 1;
			continue ;
		}
		ft_remove_from_envp(args[i], mshell);
	}
	return (result);
}
