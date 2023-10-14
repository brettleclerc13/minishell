/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:34:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/13 15:53:41 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *input, t_struct *mshell)
{
	int	i;
	char	**arguments;
	//t_lex	*list;
	//t_lex	*tmp;

	//list = NULL;
	i = -1;
	arguments = ft_split_bash(input, ' ', '	');
	while (arguments[++i])
		printf("arg[%i]: %s\n", i, arguments[i]);
	ft_export(arguments, mshell);
	//lexer(arguments, envp, &list);
	//tmp = list;
	//print_list(tmp);
	//tmp = list;
	//parser(&list, envp);
	//print_token(tmp);
	// while (*arguments)
	// {
    // 	free(*arguments);
    // 	arguments++;
	// }
	// free(arguments);
}
