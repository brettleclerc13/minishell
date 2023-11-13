/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:50:54 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/13 12:08:58 by ehouot           ###   ########.fr       */
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

void	ft_free_serie_lex(t_serie *series, t_lex *args)
{
	if (series)
		ft_free_serie(series);
	if (args)
		ft_free_lex(args);
	g_var = 1;
	exit(g_var);
}
