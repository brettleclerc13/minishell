/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:52:12 by ehouot            #+#    #+#             */
/*   Updated: 2022/11/24 21:07:02 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_print(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((len > i) && haystack[i])
	{
		if (haystack[i] != (char)needle[0])
			i++;
		else
		{
			j = 0;
			while ((haystack[i + j] == needle[j]
					|| needle[j] == '\0') && i + j <= len)
			{
				if (needle[j] == '\0')
					return ((char *)haystack + i);
				j++;
			}
			if ((i + j) == len)
				return (0);
			i++;
		}
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (!haystack && len == 0)
		return (0);
	if (*needle == 0)
		return ((char *)haystack);
	return (ft_print(haystack, needle, len));
}
