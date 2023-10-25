/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:34:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/25 09:01:47 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *input, t_struct **mshell)
{
	char	**arguments;
	t_lex	*list;

	(*mshell)->check_valid = false;
	list = NULL;
	arguments = ft_split_bash(input, ' ', '	');
	list = lexer(arguments, &list);
	printf("yes\n");
	print_lst_tok(list);
	(*mshell)->check_valid = parser(&list, (*mshell)->envp);
	printf("yes2\n");
	print_lst_tok(list);
	ft_arrayfree(arguments);
	if ((*mshell)->check_valid == true)
		return ;
	(*mshell)->args = list;
	// (*mshell)->pipe_count = ft_count_pipe(*mshell);
	return ;
}
