/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:01:13 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/29 09:09:36 by brettlecler      ###   ########.fr       */
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
		printf("serie[%d]: cmd_token: %d, fd_token: %d\n", i, series->cmd_token, series->fd_token);
		j = -1;
		series = series->next;
	}
}

void	print_string(char *tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		printf("tab[%d] : %c\n", i, tab[i]);
}

void	print_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		printf("array[%i] : %s\n", i, array[i]);
}
