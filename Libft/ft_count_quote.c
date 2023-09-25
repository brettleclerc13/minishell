/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:31:48 by ehouot            #+#    #+#             */
/*   Updated: 2023/09/15 00:32:08 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_count_quote(char const *s)
{
	int	i;
	int	cpt;

	i = -1;
	cpt = 0;
	while (s[++i])
	{
		if (s[i] == '"')
			cpt++;
	}
	if (cpt % 2 != 0)
		ft_error("simple \" is not supported");
}
