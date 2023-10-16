/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:33:16 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/16 20:41:00 by brettlecler      ###   ########.fr       */
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
	char	*var_length;
	int		i;

	i = -1;
	ft_sort_ascii(envp);
	while (envp[++i])
	{
		var_length = ft_strchr(envp[i], '=');
		if (!var_length)
			printf("declare -x %s\n", envp[i]);
		else
		{
			tmp = ft_strtrim(envp[i], "=");
			printf("declare -x %s", tmp);
			printf("\"%s\"\n", envp[i] + ft_strlen(var_length));
			free(tmp);
		}
	}
}

bool	ft_put_export_error(char *arg)
{
	ft_putstr_fd("export : ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return (false);
}
