/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:08:06 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/13 12:09:00 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, sizeof(pwd)))
	{
		ft_putstr_fd("minishell: pwd: cannot retrieve cwd", 2);
		return (1);
	}
	printf("%s\n", pwd);
	return (0);
}
