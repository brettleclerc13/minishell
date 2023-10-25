/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:16:19 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/25 15:10:03 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_convert_to_array(t_lex *args)
{
	t_lex	*tmp;
	char	**array;
	int		struct_len;

	struct_len = 0;
	tmp = args;
	while (tmp)
	{
		struct_len++;
		tmp = tmp->next;
	}
	array = calloc(struct_len + 1, sizeof(char *));
	if (!array)
		return (NULL);
	tmp = args;
	struct_len = 0;
	while (tmp)
	{
		array[struct_len++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (array);
}

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

void	ft_execute(t_struct *mshell)
{
	char	**args;

	args = ft_convert_to_array(mshell->args);
	builtin_main(args, mshell);
	ft_arrayfree(args);
}
