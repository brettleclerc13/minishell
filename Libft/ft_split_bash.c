/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:15:00 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/01 10:57:38 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*quote_loop(char *dest, char const *s, t_split_count *fill)
{
	char	quote;

	quote = s[fill->index];
	dest[fill->size++] = s[fill->index];
	while (s[++fill->index] != quote && s[fill->index])
		dest[fill->size++] = s[fill->index];
	dest[fill->size++] = s[fill->index];
	dest[fill->size] = '\0';
	return (dest);
}

static char	*ft_fill(char *dest, char const *s, t_split c, int i)
{
	t_split_count	fill;
	char			quote;

	fill.char_num = -1;
	fill.size = 0;
	fill.index = 0;
	while (s[fill.index] && ++fill.char_num <= i)
	{
		while (s[fill.index] && (s[fill.index] == c.c1 || s[fill.index] == c.c2))
			fill.index++;
		while (s[fill.index] && (s[fill.index] != c.c1 && s[fill.index] != c.c2))
		{
			if ((s[fill.index] == '"' || s[fill.index] == '\'') && fill.char_num == i)
				quote_loop(dest, s, &fill);
			else if (s[fill.index] == '"' || s[fill.index] == '\'')
			{
				quote = s[fill.index];
				while (s[++fill.index] != quote)
					;
			}
			else if (fill.char_num == i)
				dest[fill.size++] = s[fill.index];
			fill.index++;
		}
	}
	dest[fill.size] = '\0';
	return (dest);
}

static int	ft_count_size(char const *s, char c1, char c2, int i)
{
	t_split_count	count;
	char			quote;

	count.char_num = -1;
	count.size = 0;
	count.index = 0;
	while (s[count.index] && ++count.char_num <= i)
	{
		while (s[count.index] && (s[count.index] == c1 || s[count.index] == c2))
			count.index++;
		while (s[count.index] && (s[count.index] != c1 && s[count.index] != c2))
		{
			if ((s[count.index] == '"' || s[count.index] == '\'') && count.char_num == i)
			{
				quote = s[count.index];
				while (s[++count.index] != quote && s[count.index])
					count.size++;
				return (count.size + 1);
			}
			else if (s[count.index] == '"' || s[count.index] == '\'')
			{
				quote = s[count.index];
				while (s[++count.index] != quote)
					;
			}
			else if (count.char_num == i)
				count.size++;
			count.index++;
		}
	}
	return (count.size);
}

static int	ft_count(char const *s, char c1, char c2)
{
	int		i;
	int		cpt;
	char	quote;

	cpt = 1;
	i = -1;
	while (s[++i])
	{
		if ((s[i] == c1 || s[i] == c2 || s[i] == '"' || s[i] == '\'') && s[i])
			cpt++;
		
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i];
			i++;
			while (s[i] != quote && s[i])
				i++;
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
	printf("NB_WORD : %d\n", nb_words);
	dest = malloc (sizeof(char *) * (nb_words + 1));
	if (!dest)
		return (ft_split_bash_error("minishell: malloc: cannot allocate memory\n", NULL));
	while (i < nb_words)
	{
		dest[i] = malloc (ft_count_size(s, c1, c2, i) + 1);
		if (!dest[i])
			return (ft_split_bash_error("minishell: malloc: cannot allocate memory\n", NULL));
		dest[i] = ft_fill(dest[i], s, c, i);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
