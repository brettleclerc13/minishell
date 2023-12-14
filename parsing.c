/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:34:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/11 11:51:49 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	argument_empty(char *input, t_lex_var *lex_var)
{
	free(input);
	ft_free_lex_var(lex_var);
	g_var = 0;
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
	lex_var->envp = ft_arraydup((*mshell)->envp);
	list = NULL;
	lex_var->args = ft_split_bash(input, ' ', '	');
	if (!lex_var->args || !lex_var->args[0] || !ft_strcmp(*lex_var->args, ""))
		return (argument_empty(input, lex_var));
	list = lexer(lex_var, &list);
	ft_free_lex_var(lex_var);
	(*mshell)->check_valid = parser(&list, (*mshell)->envp);
	if ((*mshell)->check_valid == false)
		ft_free_lex(list);
	else
		(*mshell)->args = list;
	return (true);
}
