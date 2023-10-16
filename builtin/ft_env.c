/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:17:25 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/16 16:20:12 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **envp)
{
	int	i;

	i = -1;
	if (!envp)
	{
		ft_putstr_fd("env: env not found", 2);
		return (1);
	}
	while (envp[++i])
	{
		if (!ft_strchr(envp[i], '='))
		printf("%s\n", envp[i]);
	}
	return (0);
}
