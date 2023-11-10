/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:34:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/10 16:27:23 by brettlecler      ###   ########.fr       */
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
	(*mshell)->check_valid = parser(&list, (*mshell)->envp);
	ft_arrayfree(arguments);
	if ((*mshell)->check_valid == true)
		return ;
	(*mshell)->args = list;
	return ;
}
