/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:38:46 by ehouot            #+#    #+#             */
/*   Updated: 2022/11/24 21:09:20 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	lsrc;
	size_t	ldst;

	if ((!dst || !src) && dstsize == 0)
		return (0);
	lsrc = ft_strlen(src);
	ldst = ft_strlen(dst);
	i = ldst;
	j = 0;
	if (dstsize == 0)
		return (lsrc);
	if (dstsize < ldst)
		return (lsrc + dstsize);
	while (src[j] && (i < dstsize - 1))
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (ldst + lsrc);
}
