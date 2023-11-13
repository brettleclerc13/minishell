/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:17:25 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/13 12:08:59 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **envp)
{
	int	i;

	i = -1;
	if (!envp)
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		return (127);
	}
	while (envp[++i])
	{
		if (ft_strchr(envp[i], '='))
		printf("%s\n", envp[i]);
	}
	return (0);
}
