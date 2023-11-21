/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:24:05 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/16 11:01:24 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	bool_print_error(char *str)
{
	if (!ft_strcmp("cwd", str))
	{
		ft_putstr_fd("minishell: cwd: Cannot retrieve cwd\n", 2);
		return (false);
	}
	if (!ft_strcmp("malloc", str))
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return (false);
	}
	return (true);
}
