/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:08:06 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/05 15:08:44 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, sizeof(pwd)))
	{
		ft_putstr_fd("pwd: Cannot retrieve cwd", 2);
		perror(pwd);
		return (1);
	}
	printf("%s\n", pwd);
	return (0);
}
