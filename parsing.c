/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:34:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/25 17:10:54 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parsing(char *input, t_struct *mshell)
{
	char	**arguments;
	t_lex	*list;
	//t_lex	*tmp;

	list = NULL;
	arguments = ft_split_bash(input, ' ', '	');
	mshell->args = lexer(arguments, mshell->envp, &list);
	ft_arrayfree(arguments);
	mshell->pipe_count = ft_count_pipe(mshell);
	//tmp = list;
	//print_lst_tok(tmp);
	// parser(&list, envp);
	// print_list(list);
	return (true);
}
