/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:56:49 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/25 16:58:04 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_parser(char *s1, char *s2, bool free_first_param)
{
	size_t	i;
	size_t	j;
	size_t	lens1;
	size_t	lens2;
	char	*dest;

	j = 0;
	i = -1;
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	dest = (char *) malloc (lens1 + lens2 + 1);
	if (!dest)
		return (NULL);
	while (s1 && ++i < lens1)
		dest[i] = s1[i];
	while (s2 && j < lens2)
		dest[i++] = s2[j++];
	dest[i] = '\0';
	if (free_first_param)
		free(s1);
	return (dest);
}
