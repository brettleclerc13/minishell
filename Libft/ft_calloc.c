/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:30:57 by ehouot            #+#    #+#             */
/*   Updated: 2022/11/24 20:10:01 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*dest;

	if (count && size > SIZE_MAX / count)
		return (NULL);
	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	dest = (char *) malloc (size * count);
	if (!dest)
		return (NULL);
	ft_bzero(dest, count * size);
	return (dest);
}
