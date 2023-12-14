/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:28:53 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/11 16:36:34 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	dest = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest)
		return (NULL);
	if (s1[i])
	{
		while (i < ft_strlen(s1))
		{
			dest[i] = s1[i];
			i++;
		}
	}
	while (j < ft_strlen(s2))
	{
		dest[i++] = s2[j++];
	}
	dest[i] = '\0';
	return (dest);
}
