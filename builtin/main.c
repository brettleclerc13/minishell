/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:00:23 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/02 19:13:50 by brettlecler      ###   ########.fr       */
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
	int		i;
	char	**tmp_envp;

	i = -1;
	tmp_envp = ft_arraydup(envp);
	printf("array len: %d\n", ft_arraylen(tmp_envp));
	ft_cd(argc, argv, tmp_envp);
	while (tmp_envp[++i])
		printf("%s\n", tmp_envp[i]);
	return (0);
}
