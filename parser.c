/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:17:25 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/02 11:53:01 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_dollar(t_lex **list)
{
	int		i;
	t_lex	*tmp;

	i = -1;
	tmp = *list;
	while ((*list)->content[++i])
	{
		if ((*list)->token == WORD | (*list)->token == STRING)
		{
			if ((*list)->content[i] == '$')
			{
				
			}
		}
	}
	return (false);
}

void	parser(t_lex **list)
{
	t_lex	*tmp;

	tmp = (*list);
	while (list)
	{
		if ((*list)->token == WORD | (*list)->token == STRING | (*list)->token == DOLLAR)
			check_dollar(list);
		
	}
}
