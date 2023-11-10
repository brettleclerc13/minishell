/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bash_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:39:50 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/10 16:45:35 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	**ft_split_bash_error(char *message, char **dest)
{
	ft_freearray(dest);
	perror(message);
	return (NULL);
}
