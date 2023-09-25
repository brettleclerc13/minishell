/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:45:40 by ehouot            #+#    #+#             */
/*   Updated: 2023/09/22 19:00:13 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool lex_sign(char **args, t_lex *list, int i, int j)
{
	t_lex	*new;
	
	if (args[i][j] == '|')
		list->token = PIPE;
	else if (args[i][j] == '<')
		list->token = LEFT_CHEV;
	else if (args[i][j] == '>')
		list->token = RIGHT_CHEV;
	else if (args[i][j] == '<' && args[i][j + 1] == '<')
		list->token = DOUBLE_L_CHEV;
	else if (args[i][j] == '>' && args[i][j + 1] == '>')
		list->token = DOUBLE_R_CHEV;
	if (list->token >= 3 && list->token <= 7)
	{
		new = ft_lstnew_lex(args[i]);
		ft_lstadd_back_lex(&list, new);
		list = list->next;
		return (true);
	}
	return (false);
}

static bool lex_word(char **args, t_lex *list, int i, int j)
{
	t_lex	*new;
	
	j = 0;
	if (ft_isalnum(*args[i]) == 1)
	{
		new = ft_lstnew_lex(args[i]);
		ft_lstadd_back_lex(&list, new);
		list->token = WORD;
		list = list->next;
		return (true);
	}
	return (false);
}

static bool lex_function(char **args, t_lex *list, int i)
{
	t_lex	*new;
	
	if (ft_strncmp(args[i], "echo", 5) == 0
		|| ft_strncmp(args[i], "cd", 3) == 0
		|| ft_strncmp(args[i], "pwd", 4) == 0
		|| ft_strncmp(args[i], "export", 7) == 0
		|| ft_strncmp(args[i], "unset", 6) == 0
		|| ft_strncmp(args[i], "env", 4) == 0
		|| ft_strncmp(args[i], "exit", 5) == 0)
	{
		new = ft_lstnew_lex(args[i]);
		ft_lstadd_back_lex(&list, new);
		list->token = FUNCTION;
		list = list->next;
		return (true);
	}
	return (false);
}

static bool	lex_string(char **args, t_lex *list, int i, int j)
{
	t_lex	*new;

	while (args[i][++j])
	{
		if (args[i][j] == ' ' || args[i][j] == '	')
		{
			new = ft_lstnew_lex(args[i]);
			ft_lstadd_back_lex(&list, new);
			list->token = STRING;
			list = list->next;
			return (true);
		}
	}
	return (false);
}

t_lex	*lexer(char **args, t_lex *list)
{
	int		i;
	int		j;
	t_lex	*tmp;

	i = 0;
	tmp = list;
	while (args[i])
	{
		j = -1;
		if (lex_string(args, list, i, j) == true)
			i++;
		else if (*args[i] == '#')
			ft_error("'#' not supported");
		else if (lex_function(args, list, i) == true)
			i++;
		else if (lex_sign(args, list, i, j) == true)
			i++;
		else if (lex_word(args, list, i, j) == true)
			i++;
	}
	i = -1;
	printf("yes\n");
	while (tmp)
	{
		printf("yes 2\n");
		i++;
		printf("tmp[%d] : %s \n", i, tmp->content);
		tmp = tmp->next;
	}
	return (tmp);
}
