/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:34:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/01 20:13:59 by ehouot           ###   ########.fr       */
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
	t_lex_var	*lex_var;
	t_lex		*list;

	(*mshell)->check_valid = true;
	lex_var = malloc (sizeof(t_lex_var));
	if (!lex_var)
		return (false);
	lex_var->envp = (*mshell)->envp;
	list = NULL;
	lex_var->args = ft_split_bash(input, ' ', '	');
	if (!lex_var->args || argument_empty(lex_var->args) == true)
	{
		free(input);
		g_var = 1;
		return (false);
	}
	list = lexer(lex_var, &list);
	free(lex_var);
	(*mshell)->check_valid = parser(&list, (*mshell)->envp);
	if ((*mshell)->check_valid == false)
		ft_free_lex(list);
	else
		(*mshell)->args = list;
	return (true);
}

//print_lst_tok(list);