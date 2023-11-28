/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serie.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:52:57 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/27 13:13:13 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	serie_addition(t_serie **series, t_lex *args, int count, bool ispipe)
{
	t_serie	*new;

	new = NULL;
	new = ft_lstnew_serie(args, count, ispipe);
	if (!new)
		return (false);
	ft_lstadd_back_serie(series, new);
	return (true);
}

bool	serie_creation(t_lex *args, t_serie **series)
{
	int		count;
	t_lex	*tmp;

	count = 1;
	tmp = args;
	while (args)
	{
		if (args->token == PIPE)
		{ 
			if (serie_addition(series, tmp, count, true) == false)
				return (false);
			count = 0;
			tmp = args->next;
		}
		else if (!args->next)
		{
			if (serie_addition(series, tmp, count, false) == false)
				return (false);
		}
		count++;
		args = args->next;
	}
	return (true);
}
