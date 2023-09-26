/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:53:41 by brettlecler       #+#    #+#             */
/*   Updated: 2023/09/26 17:40:08 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "builtin.h"

char	*get_home_dir(char **envp)
{
	int	i;
	
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "HOME", 4))
			return (envp[i] + 5);
	return (0);
}

int	ft_cd(int argc, char **argv, char **envp)
{
	char	*dir;

	if (argc == 2)
	{
		dir = get_home_dir(envp);
		if (!dir)
		{
			ft_putstr_fd("cd: Home directory not listed in environment\n", 2);
			return (1);
		}
	}
	else
		dir = argv[2];
	printf("dir:- %s\n", dir);
	if (chdir(dir))
	{
		ft_putstr_fd("cd error: ", 2);
		perror(dir);
		return (1);
	}
	return (0);
}
