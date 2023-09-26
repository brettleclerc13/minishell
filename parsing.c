/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:34:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/09/26 12:06:09 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *input)
{
	char	**arguments;
	t_lex	*list;
	t_lex	*tmp;

	list = NULL;
	tmp = list;
	arguments = ft_split_bash(input, ' ', '	');
	lexer(arguments, &list);
	print_list(list);
	// while (*arguments)
	// {
    // 	free(*arguments);
    // 	arguments++;
	// }
	// free(arguments);
}
