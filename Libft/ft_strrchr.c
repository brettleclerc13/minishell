/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:11:36 by ehouot            #+#    #+#             */
/*   Updated: 2022/11/17 20:22:19 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{	
		if (s[i] == (char)c)
			return (((char *)s) + i);
		i--;
	}
	if (c == 0)
		return (((char *)s) + ft_strlen(s));
	return (NULL);
}
