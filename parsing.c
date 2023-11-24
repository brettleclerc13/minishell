/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:34:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/23 14:14:22 by ehouot           ###   ########.fr       */
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
