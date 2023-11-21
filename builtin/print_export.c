/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:33:16 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/21 13:51:54 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sort_ascii(char **array)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (array[++i])
	{
		j = i;
		while (array[++j])
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
}

void	ft_print_export(char **envp)
{
	char	*tmp;
	char	*skip_var;
	int		var_length;
	int		i;

	i = -1;
	var_length = 0;
	ft_sort_ascii(envp);
	while (envp[++i])
	{
		skip_var = ft_strchr(envp[i], '=');
		if (!skip_var)
			ft_printf("declare -x %s\n", envp[i]);
		else
		{
			var_length = (ft_strlen(envp[i]) - ft_strlen(skip_var)) + 1;
			tmp = ft_substr(envp[i], 0, var_length);
			ft_printf("declare -x %s", tmp);
			ft_printf("\"%s\"\n", envp[i] + var_length);
			free(tmp);
		}
	}
}

bool	ft_put_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (false);
}
