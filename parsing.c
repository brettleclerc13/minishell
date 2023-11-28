/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:34:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/27 09:18:19 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	argument_empty(char **arguments)
{
	if (ft_strcmp(arguments[0], "") == 0)
	{
		g_var = 0;
		return (true);
	}
	return (false);
}

bool	parsing(char *input, t_struct **mshell)
{
	char	**arguments;
	t_lex	*list;

	(*mshell)->check_valid = true;
	list = NULL;
	arguments = ft_split_bash(input, ' ', '	');
	if (!arguments || argument_empty(arguments) == true)
	{
		free(input);
		g_var = 1;
		return (false);
	}
	list = lexer(arguments, &list);
	//print_lst_tok(list);
	ft_arrayfree(arguments);
	(*mshell)->check_valid = parser(&list, (*mshell)->envp);
	if ((*mshell)->check_valid == false)
	{
		g_var = 1;
		ft_free_lex(list);
	}
	else
		(*mshell)->args = list;
	return (true);
}
