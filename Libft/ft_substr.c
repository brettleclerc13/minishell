/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:24:55 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/15 15:49:52 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	len_s;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (len > len_s)
		cpy = (char *) malloc (len_s);
	else
		cpy = (char *) malloc (len + 1);
	if (!cpy)
		return (0);
	if (start > len_s)
	{
		cpy[0] = '\0';
		return (cpy);
	}
	while (i < len && i < len_s)
		cpy[i++] = s[start++];
	cpy[i] = '\0';
	return (cpy);
}
