/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:16:19 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/07 18:10:02 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	**ft_convert_to_array(t_lex *args)
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

void	ft_execute_serie(t_serie *serie, t_struct *mshell)
{
	int	fd[2];
	

	if (mshell->series->cmd_token == FUNCTION)
		g_var = builtin_main(mshell->series->cmd, mshell);
	else
		g_var = ft_execve(mshell->series->cmd, mshell->envp);
}

void	ft_execute(t_struct *mshell)
{
	t_serie	*series;

	series = NULL;
	serie_creation(mshell, &series);
	// ft_count_pipe(mshell);
	mshell->series = series;
	print_lst_serie(mshell->series);
	while (mshell->series)
	{
		ft_execute_serie(mshell->series, mshell);
		mshell->series = mshell->series->next;
	}
	//ft_arrayfree(args);
}
// char	**args;

	// args = ft_convert_to_array(mshell->args);

	// builtin_main(args, mshell);
	// ft_arrayfree(args);