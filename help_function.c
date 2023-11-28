/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:01:13 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/28 13:47:17 by ehouot           ###   ########.fr       */
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

void	print_lst_tok(t_lex *list)
{
	int i;

	i = -1;
	while (list)
	{
		i++;
		printf("list[%d] : %s (%d) \n", i, list->content, list->token);
		list = list->next;
	}
}

void	print_prev_serie(t_serie *series)
{
	int i;

	i = -1;
	while (series)
	{
		if (series->next == NULL)
			break ;
		i++;
		printf("(NEXT) | serie[%d]: cmd: %d\n", i, series->cmd_token);
		series = series->next;
	}
	printf("----------------\n");
	while (series)
	{
		i--;
		printf("(PREV) | serie[%d]: cmd: %d\n", i, series->cmd_token);
		series = series->prev;
	}
}

void	print_lst_serie(t_serie *series)
{
	int i;
	int	j;

	i = -1;
	j = -1;
	while (series)
	{
		i++;
		while (series->cmd[++j])
			printf("serie[%d]: cmd[%d]: %s\n", i, j, series->cmd[j]);
		printf("FD_OUT_TOKEN: %d\n", series->fd_out_token);
		printf("FD_IN: %i, FD_OUT: %i\n", series->fd_in, series->fd_out);
		printf("-------------\n\n");
		j = -1;
		series = series->next;
	}
}

void	print_string(char **tab)
{
	int	i;
	int	j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			printf("tab[%d] : %s\n", i, tab[i]);
	}
}

void	print_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		printf("array[%i] : %s\n", i, array[i]);
}
