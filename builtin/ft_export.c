/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:10:41 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/30 16:11:39 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_to_envp(char *arg, t_struct *mshell)
{
	t_var	var;

	ft_create_var(arg, &var);
	if (!ft_varcmp_struct(&var, mshell->envp))
	{
		if (var.symbol == '+')
			mshell->envp = add_env_value(var.var, arg + (var.varlen + 1), mshell->envp);
		else
			mshell->envp = add_env_str(arg, mshell->envp);
	}
	else
	{
		if (var.symbol == '+')
			update_env(&var, arg + (var.varlen + 1), mshell, true);
		if (var.symbol == '=')
			update_env(&var, arg + var.varlen, mshell, true);
		free(var.envp_var);
	}
	free(var.var);
}

static bool	ft_isvar(char *arg)
{
	int	i;

	i = 0;
	if (!*arg)
		return (ft_put_export_error(arg));
	if (arg[0] && (!ft_isalpha(arg[i]) && arg[i] != '_'))
		return (ft_put_export_error(arg));
	while (arg[++i] && arg[i] != '=')
	{
		if ((!ft_isalnum(arg[i]) && arg[i] != '_') && \
			!(arg[i] == '+' && arg[i + 1] == '='))
			return (ft_put_export_error(arg));
	}
	return (true);
}

int	ft_export(char **args, t_struct *mshell)
{
	char	**tmp;
	int		i;
	int		result;	

	i = 0;
	result = 0;
	tmp = ft_arraydup(mshell->envp);
	while (args[++i])
	{
		if (!ft_isvar(args[i]))
		{
			result = 1;
			continue ;
		}
		ft_add_to_envp(args[i], mshell);
	}
	if (i == 1)
		ft_print_export(tmp);
	ft_arrayfree(tmp);
	return (result);
}
