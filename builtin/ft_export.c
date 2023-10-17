/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:10:41 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/17 09:29:52 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		//ft_add_env
	}
	if (i == 1)
		ft_print_export(mshell->envp);
	return (result);
}
