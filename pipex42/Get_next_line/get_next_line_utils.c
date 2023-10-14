/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:42:51 by ehouot            #+#    #+#             */
/*   Updated: 2023/06/13 16:39:21 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2, bool free_first_param)
{
	size_t	i;
	size_t	j;
	size_t	lens1;
	size_t	lens2;
	char	*dest;

	j = 0;
	i = -1;
	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen_gnl(s1);
	lens2 = ft_strlen_gnl(s2);
	dest = (char *) malloc (lens1 + lens2 + 1);
	if (!dest)
		return (NULL);
	while (++i < lens1)
		dest[i] = s1[i];
	while (j < lens2)
		dest[i++] = s2[j++];
	dest[i] = '\0';
	if (free_first_param)
		free(s1);
	return (dest);
}

char	*ft_strdup_gnl(const char *s1)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *) malloc ((ft_strlen_gnl(s1) + 1) * sizeof(char));
	if (dest == NULL)
		return (0);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*ft_strcpy_gnl(char *dst, const char *src)
{
	size_t	i;
	size_t	lsrc;

	lsrc = ft_strlen_gnl(src);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
