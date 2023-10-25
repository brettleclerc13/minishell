/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:45:40 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/25 08:56:54 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	lex_sign(char **args, t_lex **list, int *i, int j)
{
	t_lex			*new;
	enum e_token	save_tok;

	save_tok = -1;
	if (args[*i][j] == '|' && !args[*i][j + 1])
		save_tok = PIPE;
	else if (args[*i][j] == '<' && !args[*i][j + 1])
		save_tok = LEFT_CHEV;
	else if (args[*i][j] == '>' && !args[*i][j + 1])
		save_tok = RIGHT_CHEV;
	else if (args[*i][j] == '<' && args[*i][j + 1] == '<' && !args[*i][j + 1])
		save_tok = DOUBLE_L_CHEV;
	else if (args[*i][j] == '>' && args[*i][j + 1] == '>' && !args[*i][j + 1])
		save_tok = DOUBLE_R_CHEV;
	if (save_tok >= 0 && save_tok <= 4)
	{
		new = ft_lstnew_lex(args[*i], save_tok);
		ft_lstadd_back_lex(list, new);
		(*i)++;
		return (true);
	}
	return (false);
}

static void	lex_word(char **args, t_lex **list, int *i)
{
	ft_split_word(args[*i], list);
	(*i)++;
}

static bool	lex_function(char **args, t_lex **list, int *i)
{
	t_lex	*new;
	
	if (ft_strncmp(args[*i], "echo", 5) == 0
		|| ft_strncmp(args[*i], "cd", 3) == 0
		|| ft_strncmp(args[*i], "pwd", 4) == 0
		|| ft_strncmp(args[*i], "export", 7) == 0
		|| ft_strncmp(args[*i], "unset", 6) == 0
		|| ft_strncmp(args[*i], "env", 4) == 0
		|| ft_strncmp(args[*i], "exit", 5) == 0)
	{
		new = ft_lstnew_lex(args[*i], FUNCTION);
		ft_lstadd_back_lex(list, new);
		(*i)++;
		return (true);
	}
	return (false);
}

static bool	lex_string(char **args, t_lex **list, int *i, int j)
{
	t_lex	*new;

	while (args[*i][++j])
	{
		if (args[*i][j] == ' ' || args[*i][j] == '	')
		{
			if (!ft_split_word(args[*i], list))
			{	
				new = ft_lstnew_lex(args[*i], STRING);
				ft_lstadd_back_lex(list, new);
			}
			(*i)++;
			return (true);
		}
	}
	return (false);
}

t_lex	*lexer(char **args, t_lex **list)
{
	int		i;
	int		j;
	t_lex	*tmp;

	i = 0;
	tmp = *list;
	while (args[i])
	{
		j = 0;
		if (lex_string(args, list, &i, j) == true)
			continue;
		if (*args[i] == '#')
			ft_error("'#' not supported");
		if (lex_function(args, list, &i) == true)
			continue;
		if (lex_sign(args, list, &i, j) == true)
			continue;
		if (lex_dollar(args, list, &i) == true)
			continue;
		lex_word(args, list, &i);
	}
	tmp = *list;
	return (tmp);
}
