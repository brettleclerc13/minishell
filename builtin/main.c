/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:00:23 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/03 14:34:23 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

//echo main
/*int	main(int argc, char **argv)
{
	if (argc > 1)
		ft_echo(argv);
	return (0);
}*/

//cd main
int	main(int argc, char **argv, char **envp)
{
	t_struct	mshell;
	int			i;

	i = 0;
	mshell.envp = ft_arraydup(envp);
	ft_cd(argc, argv, &mshell);
	printf("\033[0;32m__________________\033[0m\n");
	while (mshell.envp[i] && mshell.envp)
	{
		printf("%s\n", mshell.envp[i]);
		i++;
	}
	printf("\033[0;32m__________________\033[0m\n");
	return (0);
}
