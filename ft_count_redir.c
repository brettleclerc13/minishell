/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:16:15 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/04 23:16:46 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_redir(t_lex *args)
{
	int		nb_red;
	t_lex	*tmp;

	nb_red = 0;
	tmp = args;
	while (tmp)
	{
		if (tmp->token == RIGHT_CHEV
			|| tmp->token == LEFT_CHEV
			|| tmp->token == DOUBLE_R_CHEV
			|| tmp->token == DOUBLE_L_CHEV)
			nb_red++;
		tmp = tmp->next;
	}
	return (nb_red);
}
