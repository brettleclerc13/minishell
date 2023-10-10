/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:34:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/09 15:27:03 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *input, char **envp)
{
	char	**arguments;
	t_lex	*list;
	t_lex	*tmp;

	list = NULL;
	tmp = list;
	arguments = ft_split_bash(input, ' ', '	');
	lexer(arguments, envp, &list);
	print_list(list);
	// parser(&list, envp);
	// print_list(list);
	// while (*arguments)
	// {
    // 	free(*arguments);
    // 	arguments++;
	// }
	// free(arguments);
}
