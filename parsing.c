/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:34:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/09/22 18:19:24 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *input)
{
	char	**arguments;
	t_lex	*list;
	int		i;

	i = 0;
	list = NULL;
	arguments = ft_split_bash(input, ' ', '	');
	list = lexer(arguments, list);
	while (list)
	{
		i++;
		printf("list[%d] : %s \n", i, list->content);
		list = list->next;
	}
	// while (*arguments) 
	// {
    // 	free(*arguments);
    // 	arguments++;
	// }
	// free(arguments);
}
