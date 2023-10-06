/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:00:23 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/06 08:48:53 by brettlecler      ###   ########.fr       */
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

	mshell.envp = ft_arraydup(envp);
	if (ft_update_shlvl(&mshell))
		return (1);
	if (ft_cd(argc, argv, &mshell))
		return (1);
	if (ft_pwd())
		return (1);
	printf("\033[0;32m__________________\033[0m\n");
	if (ft_env(&mshell))
		return (1);
	printf("\033[0;32m__________________\033[0m\n");
	return (0);
}
