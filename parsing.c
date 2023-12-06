/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:34:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/06 09:53:02 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	argument_empty(char **arguments, char *input)
{
	if (!arguments || !arguments[0])
	{
		free(input);
		g_var = 0;
	}
	else if (!ft_strcmp(arguments[0], ""))
	{
		free(input);
		g_var = 0;
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
	if (!lex_var->args || !lex_var->args[0] || !ft_strcmp(lex_var->args[0], ""))
		return (argument_empty(lex_var->args, input));
	list = lexer(lex_var, &list);
	free(lex_var);
	print_lst_tok(list);
	(*mshell)->check_valid = parser(&list, (*mshell)->envp);
	if ((*mshell)->check_valid == false)
		ft_free_lex(list);
	else
		(*mshell)->args = list;
	return (true);
}
