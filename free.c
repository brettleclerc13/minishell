/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:50:54 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/10 16:40:31 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_serie(t_serie *series)
{
	if (!series)
		return ;
	while (series)
	{
		ft_arrayfree(series->cmd);
		if (series->fd_in != STDIN_FILENO && series->fd_in != -1)
			close(series->fd_in);
		if (series->fd_out != STDOUT_FILENO && series->fd_out != -1)
			close(series->fd_out);
		series = series->next;
	}
}

void	ft_free_lex(t_lex *lex)
{
	if (!lex)
		return ;
	while (lex)
	{
		free(lex->content);
		lex = lex->next;
	}
}