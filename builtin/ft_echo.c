/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:10:35 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/06 08:24:25 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "builtin.h"

static bool is_newline(char **argv, int *i)
{
	bool	is_newline;
	int		j;

	is_newline = false;
	*i = 1;
	while (argv[++(*i)] && argv[*i][0] == '-')
	{
		j = 0;
		while (argv[*i][++j])
			if (argv[*i][j] != 'n')
				return (is_newline);
		is_newline = true;
	}
	return (is_newline);
}

int	ft_echo(char **argv)
{
	bool	newline;
	int		i;
	
	newline = is_newline(argv, &i);
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline == false)
		printf("\n");
	return (0);
}
