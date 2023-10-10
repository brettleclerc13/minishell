/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:01:13 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/10 11:54:15 by brettlecler      ###   ########.fr       */
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

static void	print_token_contd(enum e_token token)
{
	if (token == WORD)
		printf("WORD\n");
	else if (token == STRING)
		printf("STRING\n");
	else if (token == FUNCTION)
		printf("FUNCTION\n");
	else if (token == LEFT_CHEV)
		printf("LEFT_CHEV\n");
	else if (token == RIGHT_CHEV)
		printf("RIGHT_CHEV\n");
	else if (token == DOUBLE_L_CHEV)
		printf("DOUBLE_L_CHEV\n");
	else if (token == DOUBLE_R_CHEV)
		printf("DOUBLE_R_CHEV\n");
	else if (token == PIPE)
		printf("PIPE\n");
	else if (token == DOLLAR)
		printf("DOLLAR\n");
	else
		printf("No idea wtf is this?\n");
}

void    print_token(t_lex *list)
{
	int i;

	i = -1;
	while (list)
	{
		i++;
		printf("list[%d]->token : ", i);
		print_token_contd(list->token);
		list = list->next;
	}
}

void	print_tab(char *tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		fprintf(stdout, "tab[%d] : %c\n", i, tab[i]);
}
