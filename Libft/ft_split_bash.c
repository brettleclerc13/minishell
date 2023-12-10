/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:15:00 by ehouot            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/05 10:22:35 by ehouot           ###   ########.fr       */
=======
/*   Updated: 2023/12/08 21:15:55 by brettlecler      ###   ########.fr       */
>>>>>>> brett
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*quote_loop(char *dest, char const *s, t_split_count *fill)
{
	fill->quote = s[fill->index];
	dest[fill->size++] = s[fill->index++];
	while (s[fill->index] && s[fill->index] != fill->quote)
		dest[fill->size++] = s[fill->index++];
	return (dest);
}

static char	*ft_fill(char *dest, char const *s, t_split c, int i)
{
	t_split_count	fill;

	fill.char_num = -1;
	fill.size = 0;
	fill.index = 0;
	fill.quote = '\0';
	while (s[fill.index] && ++fill.char_num <= i)
	{
		while (s[fill.index] \
			&& (s[fill.index] == c.c1 || s[fill.index] == c.c2))
			fill.index++;
		while (s[fill.index] \
			&& (s[fill.index] != c.c1 && s[fill.index] != c.c2))
		{
			if ((s[fill.index] == '\"' || s[fill.index] == '\'') \
				&& fill.char_num == i)
				dest = quote_loop(dest, s, &fill);
			if (fill.char_num == i)
				dest[fill.size++] = s[fill.index];
			fill.index++;
		}
	}
	dest[fill.size] = '\0';
	return (dest);
}

static int	ft_count_size(char const *s, char c1, char c2, int i)
{
	t_split_count	c;

	c.char_num = -1;
	c.size = 0;
	c.index = 0;
	c.quote = '\0';
	while (s[c.index] && ++c.char_num <= i)
	{
		while (s[c.index] && (s[c.index] == c1 || s[c.index] == c2))
			c.index++;
		while (s[c.index] && (s[c.index] != c1 && s[c.index] != c2))
		{
			if ((s[c.index] == '\"' || s[c.index] == '\'') && c.char_num == i)
			{
				c.quote = s[c.index];
				c.size++;
				while (s[++c.index] && s[c.index] != c.quote)
					c.size++;
			}
			if (c.char_num == i)
				c.size++;
			c.index++;
		}
	}
	return (c.size);
}

static int	ft_count(char const *s, char c1, char c2)
{
	int		i;
	int		cpt;
	char	quote;

	cpt = 0;
	i = -1;
	quote = '\0';
	while (s[++i])
	{
		while ((s[i] == c1 || s[i] == c2) && s[i])
			i++;
		if ((s[i] != c1 && s[i] != c2) && s[i])
			cpt++;
		while ((s[i] != c1 && s[i] != c2) && s[i])
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				quote = s[i++];
				while (s[i] && s[i] != quote)
					i++;
			}
			i++;
		}
	}
	return (cpt);
}

char	**ft_split_bash(char const *s, char c1, char c2)
{
	char	**dest;
	int		i;
	int		nb_words;
	t_split	c;

	dest = NULL;
	c.c1 = c1;
	c.c2 = c2;
	i = 0;
	if (ft_count_quote(s) == false)
		return (NULL);
	nb_words = ft_count(s, c1, c2);
	dest = malloc (sizeof(char *) * (nb_words + 1));
	if (!dest)
		return (ft_split_bash_error("malloc", dest));
	while (i < nb_words)
	{
		dest[i] = malloc (ft_count_size(s, c1, c2, i) + 1);
		if (!dest[i])
			return (ft_split_bash_error("malloc", dest));
		dest[i] = ft_fill(dest[i], s, c, i);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
