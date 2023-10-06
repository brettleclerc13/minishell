/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:17:25 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/06 09:29:53 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_dollar(t_lex **list, char **envp)
{
	char	*str;

	str = ft_strchr((*list)->content, '$');
	if (!str)
		return (false);
	(*list)->content = get_env_value(ft_substr((*list)->content, 1, ft_strlen((*list)->content)), envp);
	if ((*list)->content == NULL)
		return (false);
	return (true);
}

void	parser(t_lex **list, char **envp)
{
	/*t_lex	*tmp;
	bool	pipe;

	pipe = false;
	tmp = (*list);*/
	while (list)
	{
		/*if ((*list)->token  == WORD | (*list)->token == FUNCTION)
		{
			if ((*list)->)
		}
		if ((*list)->content == '|')
		{
			list = (*list)->next;
			if (list->content == '|')
			
		}*/
		if ((*list)->token == WORD | (*list)->token == STRING | (*list)->token == DOLLAR)
			check_dollar(list, envp);
		list = (*list)->next;
	}
}
