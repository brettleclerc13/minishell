/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:10:41 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/17 20:13:35 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_env_str(char *arg, char **envp)
{
	char	**new_envp;
	
	new_envp = ft_arrayadd(arg, envp);
	ft_arrayfree(envp);
	return (new_envp);
}

static void	ft_add_to_envp(char *arg, t_struct *mshell)
{
	char	*var;
	char	*skip_var;
	int		var_length;

	var_length = 0;
	skip_var = NULL;
	var = NULL;
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
	{
		skip_var = ft_strchr(arg, '+');
		var_length = ft_strlen(arg) - ft_strlen(skip_var);
		var = ft_substr(arg, 0, var_length);
		mshell->envp = add_env_value(var, arg + (var_length + 1), mshell->envp);
		free (var);
	}
	else
		mshell->envp = add_env_str(arg, mshell->envp);
}	

static bool	ft_isenv(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return(ft_put_export_error(arg));
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (ft_put_export_error(arg));
	while (arg[++i] && arg[i] != '=')
	{
		if ((!ft_isalnum(arg[i]) && arg[i] != '_') && \
			!(arg[i] == '+' && arg[i + 1] == '='))
			return(ft_put_export_error(arg));
	}
	return (true);
}

int	ft_export(char **argv, t_struct *mshell)
{
	int	i;
	int	result;	
	
	i = 0;
	result = 0;
	while (argv[++i])
	{
		if(!ft_isenv(argv[i]))
		{
			result = 1;
			continue ;
		}
		ft_add_to_envp(argv[i], mshell);
	}
	if (i == 1)
		ft_print_export(mshell->envp);
	return (result);
}
