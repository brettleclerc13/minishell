/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:10:35 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/30 18:10:23 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_cmd(char **argv, int *i)
{
	bool	n_cmd;
	int		j;

	n_cmd = false;
	*i = 0;
	while (argv[++(*i)] && argv[*i][0] == '-')
	{
		j = 0;
		while (argv[*i][++j])
			if (argv[*i][j] != 'n')
				return (n_cmd);
		n_cmd = true;
	}
	return (n_cmd);
}

int	ft_echo(char **args)
{
	bool	n_cmd;
	int		i;

	n_cmd = is_n_cmd(args, &i);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] && args)		//SKIP or DOUBLE_QUOTE to be considered
			printf(" ");
		i++;
	}
	if (!n_cmd)
		printf("\n");
	return (0);
}
