/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serie.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:52:57 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/29 09:22:21 by ehouot           ###   ########.fr       */
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
