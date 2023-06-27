/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:15:07 by ehouot            #+#    #+#             */
/*   Updated: 2022/11/24 21:09:55 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strchar(char *str, char *to_find)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i])
	{
		j = 0;
		while (str[i] != to_find[j] && to_find[j])
			j++;
		if (to_find[j] == '\0')
			return (str + i);
		i++;
	}
	if (i == ft_strlen(str))
		return ("");
	return (0);
}

static char	*ft_strchar_rev(char *s1, char *set)
{
	char	*dest;
	int		i;
	int		j;

	dest = NULL;
	i = ft_strlen(s1) - 1;
	while (i >= 0 || s1[i] == '\0')
	{
		j = 0;
		while (s1[i] != set[j] && set[j])
			j++;
		if (set[j] == '\0')
		{
			dest = malloc ((ft_strlen(s1) + 2)
					- ((ft_strlen(s1) + 1) - (i + 1)));
			if (!dest)
				return (0);
			break ;
		}
		i--;
	}
	ft_strlcpy(dest, s1, i + 2);
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	if (!s1 || !set)
		return (0);
	s1 = ft_strchar((char *)s1, (char *)set);
	if (!s1)
		return ("");
	return (ft_strchar_rev((char *)s1, (char *)set));
}
