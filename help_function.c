/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:01:13 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/02 11:01:52 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// HELPING FUNCTION FOR DEBUGGING //

void    print_list(t_lex *list)
{
	int i;

	i = -1;
	while (list)
	{
		i++;
		printf("list[%d] : %s \n", i, list->content);
		list = list->next;
	}
}

void    print_token(t_lex *list)
{
	int i;

	i = -1;
	while (list)
	{
		i++;
		printf("list[%d] : %u \n", i, list->token);
		list = list->next;
	}
}
