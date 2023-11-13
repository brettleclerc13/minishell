/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:14:33 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/13 12:34:15 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill(char *dest, char const *s, char c, int i)
{
	int	j;
	int	z;
	int	a;

	z = 0;
	j = 0;
	a = 0;
	while (s[z] && a <= i)
	{
		while (s[z] && s[z] == c)
			z++;
		while (s[z] && s[z] != c)
		{
			if (a == i)
			{
				dest[j] = s[z];
				j++;
			}
			z++;
		}
		a++;
	}
	dest[j] = 0;
	return (dest);
}

static int	ft_count_size(char const *s, char c, int i)
{
	int	j;
	int	z;
	int	a;

	z = 0;
	j = 0;
	a = 0;
    if (s[i] == c && !s[i + 1])
    {
        return (1);
    }
	while (s[z] && a <= i)
	{
		while (s[z] && s[z] == c)
			z++;
		while (s[z] && s[z] != c)
		{
			if (a == i)
				j++;
			z++;
		}
		a++;
	}
	return (j);
}

static int	ft_count(char const *s, char c)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && !s[i + 1])
			cpt++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (cpt);
}

char	**ft_split_dollar(char const *s, char c)
{
	char	**dest;
	int		i;
	int		nb_words;

	i = 0;
	if (!s)
		return (NULL);
	nb_words = ft_count(s, c);
	dest = malloc (sizeof(char *) * (nb_words + 1));
	if (!dest)
		return (NULL);
	while (i < nb_words)
	{
		dest[i] = malloc (ft_count_size(s, c, i) + 1);
		if (!dest[i])
			return (NULL);
        if (s[i] == c && !s[i + 1])
            dest[i] = &c;
        else
		    dest[i] = ft_fill(dest[i], s, c, i);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
