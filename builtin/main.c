/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:00:23 by brettlecler       #+#    #+#             */
/*   Updated: 2023/09/26 17:31:57 by brettlecler      ###   ########.fr       */
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
	ft_cd(argc, argv, envp);
	return (0);
}
