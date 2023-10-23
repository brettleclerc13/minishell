/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:10:41 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/23 10:23:53 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_to_envp(char *arg, t_struct *mshell)
{
	t_var	var;

	ft_create_var(arg, &var);
	if (!ft_varcmp(&var, mshell->envp))
	{
		if (var.symbol == '+')
			mshell->envp = add_env_value(var.var, arg + (var.varlen + 1), mshell->envp);
		else
			mshell->envp = add_env_str(arg, mshell->envp);
	}
	else
	{
		if (var.symbol == '+')
			update_env(&var, arg + (var.varlen + 1), mshell);
		if (var.symbol == '=')
			update_env(&var, arg + var.varlen, mshell);
		free(var.envp_var);
	}
	free(var.var);
}

int	ft_export(char **argv, t_struct *mshell)
{
	int	i;
	int	result;	

	i = 0;
	result = 0;
	while (argv[++i])
	{
		if (!ft_isvar(argv[i]))
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

/*   ROUGH WORK   */
// static void	ft_add_to_envp(char *arg, t_struct *mshell)
// {
// 	char	*var;
// 	int		var_length;

// 	var_length = 0;
// 	var = NULL;
// 	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
// 	{
// 		var_length = ft_strlen(arg) - ft_strlen(ft_strchr(arg, '+'));
// 		var = ft_retrieve_var(arg, '+');
// 		if (get_env_value(var, mshell->envp))
// 			update_env_value(var, arg + (var_length + 1), mshell->envp);
// 		else
// 			mshell->envp = add_env_value(var, arg + (var_length + 1), mshell->envp);
// 		free (var);
// 	}
// 	else if (!ft_strchr(arg, '='))
// 	{
// 		if (get_env_value(arg, mshell->envp))
// 			return ;
// 		else
// 			mshell->envp = add_env_str(arg, mshell->envp);
// 	}
// 	else
// 	{
// 		var = ft_retrieve_var(arg, '=');
// 		if (get_env_value(var, mshell->envp))
// 			update_env_value(var, arg + (var_length + 1), mshell->envp);
// 		else
// 			mshell->envp = add_env_str(arg, mshell->envp);
// 		free (var);
// 	}
// }