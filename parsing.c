/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:34:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/14 11:31:48 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *input, char **envp)
{
	char	**arguments;
	t_lex	*list;
	t_lex	*tmp;

	list = NULL;
	arguments = ft_split_bash(input, ' ', '	');
	lexer(arguments, envp, &list);
	// print_list(list);
	// print_token(list);
	tmp = list;
	print_lst_tok(tmp);
	// parser(&list, envp);
	// print_list(list);
	// while (*arguments)
	// {
    // 	free(*arguments);
    // 	arguments++;
	// }
	// free(arguments);
}
