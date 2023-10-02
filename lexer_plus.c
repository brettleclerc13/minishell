/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:07:30 by ehouot            #+#    #+#             */
/*   Updated: 2023/09/28 16:15:02 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	lex_dollar(char **args, t_lex **list, int *i)
{
	t_lex	*new;

	if (args[*i][0] == '$')
	{
		new = ft_lstnew_lex(args[*i]);
		ft_lstadd_back_lex(list, new);
		(*list)->token = DOLLAR;
		(*i)++;
		return (true);
	}
	return (false);
}