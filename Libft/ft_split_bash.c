/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:15:00 by ehouot            #+#    #+#             */
/*   Updated: 2023/07/10 09:43:50 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill(char *dest, char const *s, t_split c, int i)
{
	t_split_count	fill;

	fill.a = 0;
	fill.j = 0;
	fill.a = 0;
	while (s[fill.z] && fill.a <= i)
	{
		while (s[fill.z] && (s[fill.z] == c.c1 || s[fill.z] == c.c2))
			fill.z++;
		if (s[fill.z] == '"')
		{
			dest[fill.j++] = s[fill.z++];
			while (s[fill.z] != '"' && s[fill.z])
				dest[fill.j++] = s[fill.z++];
			if (s[fill.z] == '"')
				dest[fill.j++] = s[fill.z++];
		}
		else
		{
			while (s[fill.z] && (s[fill.z] != c.c1 || s[fill.z] == c.c2))
			{
				if (fill.a == i)
					dest[fill.j++] = s[fill.z];
				fill.z++;
			}
			fill.a++;
		}
	}
	dest[fill.j] = 0;
	return (dest);
}

static int	ft_count_size(char const *s, char c1, char c2, int i)
{
	t_split_count	count;

	count.z = 0;
	count.j = 0;
	count.a = 0;
	while (s[count.z] && count.a <= i)
	{
		while (s[count.z] && (s[count.z] == c1 || s[count.z] == c2))
			count.z++;
		if (s[count.z] == '"')
		{
			count.j++;
			count.z++;
			while (s[++count.z] != '"' && s[count.z])
			{
				count.j++;
				count.z++;
			}
			if (s[count.z] == '"')
				count.j++;
		}
		else
		{
			while (s[count.z] && (s[count.z] != c1 || s[count.z] == c2))
			{
				if (count.a == i)
					count.j++;
				count.z++;
			}
			count.a++;
		}
	}
	return (count.j);
}

static int	ft_count(char const *s, char c1, char c2)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c1 || s[i] == c2))
			i++;
		if (s[i])
			cpt++;
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"' && s[i])
			{
				if (!s[i + 1] && s[i] != '"')
					ft_error("simple \" is not supported");
				i++;
			}
			if (s[i] == '"')
				i++;
		}
		while (s[i] && (s[i] != c1 || s[i] != c2))
			i++;
	}
	return (cpt);
}

char	**ft_split_bash(char const *s, char c1, char c2)
{
	char	**dest;
	int		i;
	int		nb_words;
	t_split	c;

	c.c1 = c1;
	c.c2 = c2;
	i = 0;
	if (!s)
		return (NULL);
	nb_words = ft_count(s, c1, c2);
	dest = malloc (sizeof(char *) * (nb_words + 1));
	if (!dest)
		return (NULL);
	while (i < nb_words)
	{
		dest[i] = malloc (ft_count_size(s, c1, c2, i) + 1);
		if (!dest[i])
			return (NULL);
		dest[i] = ft_fill(dest[i], s, c, i);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
