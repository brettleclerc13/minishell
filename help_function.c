/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:01:13 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/15 08:51:15 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FUNCTIONS THAT HELP TO DEBUG //

void	print_list(t_lex *list)
{
	t_lex	*tmp_list;
	int		i;

	i = -1;
	tmp_list = list;
	while (tmp_list)
	{
		i++;
		printf("list[%d] : %s \n", i, tmp_list->content);
		tmp_list = tmp_list->next;
	}
}

void	print_lst_tok(t_lex *list)
{
	t_lex	*tmp;
	int		i;

	i = -1;
	tmp = list;
	while (tmp)
	{
		i++;
		printf("list[%d] : %s (%d) \n", i, tmp->content, tmp->token);
		tmp = tmp->next;
	}
}

void	print_lst_serie(t_serie *series)
{
	t_serie	*tmp_series;
	int		i;
	int		j;

	i = -1;
	j = -1;
	tmp_series = series;
	while (tmp_series)
	{
		i++;
		while (tmp_series->cmd[++j])
			printf("serie[%d]: cmd[%d]: %s\n", i, j, tmp_series->cmd[j]);
		printf("FD_OUT_TOKEN: %d\n", tmp_series->fd_out_token);
		printf("IN: %i, OUT: %i\n", tmp_series->fd_in, tmp_series->fd_out);
		printf("-------------\n\n");
		j = -1;
		tmp_series = tmp_series->next;
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
