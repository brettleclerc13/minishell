/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:56:07 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/23 17:19:51 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remove_from_envp(char *arg, t_struct *mshell)
{
	char	*envp_var;
	int	i;

	i = -1;
	while (mshell->envp[++i])
	{
		envp_var = get_env_var(mshell->envp[i]);
		if (!ft_strcmp(arg, envp_var))
		{
			free(envp_var);
			mshell->envp = ft_arrayremove(mshell->envp[i], mshell->envp);
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

static bool	ft_is_unset_arg(char *arg)
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

int	ft_unset(char **argv, t_struct *mshell)
{
	int	i;
	int	result;
	
	i = 0;
	mshell->envp = mshell->envp;
	result = 0;
	while (argv[++i])
	{
		if (!ft_is_unset_arg(argv[i]))
		{
			result = 1;
			continue ;
		}
		ft_remove_from_envp(argv[i], mshell);
	}
	return (result);
}