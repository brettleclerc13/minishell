/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:45:40 by ehouot            #+#    #+#             */
/*   Updated: 2023/06/28 17:05:40 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(char **args)
{
	int		i;
	int		j;
	int		n;
	t_lex	*list;

	i = 0;
	n = 0;
	while (args[i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '"')
			{
				j++;
				while (args[i][j] && args[i][j] != '"')
				{
					if (!list->content)
						list->content = ft_strdup(args[i][j]);
					else
						list->content = ft_strjoin(list->content, args[i][j]);
					if (!args[i][j + 1] && args[i][j] != '"')
					{
						free(list);
						ft_error(" \" is not supported");
					}
					j++;
				}
				list->token = STRING;
				list = list->next;
			}
			else if (args[i][j])
			else if (ft_isalnum(args[i][j])) //add number
			
			else if (args[i][j] == '|' || args[i][j] == '<' || args[i][j] == '>' || (args[i][j] == '<' && args[i][j + 1] == '<') || (args[i][j] == '>' && args[i][j + 1] == '>'))
			{
				list->content = ;
			}
		}
	}
	
}
