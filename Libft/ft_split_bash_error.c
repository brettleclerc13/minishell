/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bash_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:39:50 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/08 21:15:43 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* array free function for Libft lib */
static void	ft_freearray(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

char	**ft_split_bash_error(char *error, char **dest)
{
	if (!ft_strcmp(error, "malloc"))
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
	ft_freearray(dest);
	return (NULL);
}
