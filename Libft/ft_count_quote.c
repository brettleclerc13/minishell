/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:31:48 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/28 16:56:43 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_check_doublon(char const *s)
{
	int		i;
	char	c;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			c = s[i];
			while (s[++i] && s[i] != c)
				;
			if (!s[i])
				return (c);
		}
	}
	return ('n');
}

bool	ft_count_quote(char const *s)
{
	char	res;

	res = ft_check_doublon(s);
	if (res == '\"')
	{
		ft_putstr_fd("minishell: \": open-ended quotes are not supported\n", 2);
		return (false);
	}
	if (res == '\'')
	{
		ft_putstr_fd("minishell: \': open-ended quotes are not supported\n", 2);
		return (false);
	}
	return (true);
}
