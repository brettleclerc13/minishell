/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:16:19 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/29 09:10:19 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_pipe(t_struct *mshell)
{
	t_lex	*args;
	int		pipe_count;

	pipe_count = 0;
	args = mshell->args;
	while (args)
	{
		if (args->token == 4)
			pipe_count++;
		args = args->next;
	}	
	return(pipe_count);
}

// char	**ft_lex_array(t_lex *args)
// {
// 	t_lex	*tmp;
// 	char	**array;
// 	int		struct_len;

// 	struct_len = 0;
// 	tmp = args;
// 	while (tmp)
// 	{
// 		struct_len++;
// 		tmp = tmp->next;
// 	}
// 	array = ft_calloc(struct_len + 1, sizeof(char *));
// 	if (!array)
// 		return (NULL);
// 	tmp = args;
// 	struct_len = 0;
// 	while (tmp)
// 	{
// 		array[struct_len++] = ft_strdup(tmp->content);
// 		tmp = tmp->next;
// 	}
// 	return (array);
// }

void	ft_execute(t_struct *mshell)
{
	t_serie	*series;
	t_serie *tmp;

	series = NULL;
	serie_creation(mshell, &series);
	tmp = series;
	print_lst_serie(series);
	while (tmp)
	{
		builtin_main(tmp->cmd, mshell);
		tmp = tmp->next;
	}
	//ft_arrayfree(args);
}
