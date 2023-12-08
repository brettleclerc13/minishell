/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:45:40 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/08 08:18:25 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	lex_sign(t_lex_var *lex_var, t_lex **list, int *i, int j)
{
	t_lex			*new;
	enum e_token	save_tok;

	save_tok = -1;
	if (lex_var->args[*i][j] == '|' && !lex_var->args[*i][j + 1])
		save_tok = PIPE;
	else if (lex_var->args[*i][j] == '<' && !lex_var->args[*i][j + 1])
		save_tok = LEFT_CHEV;
	else if (lex_var->args[*i][j] == '>' && !lex_var->args[*i][j + 1])
		save_tok = RIGHT_CHEV;
	else if (lex_var->args[*i][j] == '<' && lex_var->args[*i][j + 1] == '<' && !lex_var->args[*i][j + 1])
		save_tok = DOUBLE_L_CHEV;
	else if (lex_var->args[*i][j] == '>' && lex_var->args[*i][j + 1] == '>' && !lex_var->args[*i][j + 1])
		save_tok = DOUBLE_R_CHEV;
	if (save_tok >= 0 && save_tok <= 4)
	{
		new = ft_lstnew_lex(lex_var, lex_var->args[*i], list, save_tok);
		ft_lstadd_back_lex(list, new);
		(*i)++;
		return (true);
	}
	return (false);
}

static void	lex_word(t_lex_var *lex_var, t_lex **list, int *i)
{
	ft_split_word(lex_var, lex_var->args[*i], list);
	(*i)++;
}

static void	lex_add_string(t_lex **list, enum e_token token, t_lex **new)
{
	if (!(*new)->content || (*new)->content[0] == '\0')
		ft_lstadd_back_lex(list, *new);
	else
		ft_split_string((*new)->content, list, token);
}

static bool	lex_string(t_lex_var *lex_var, t_lex **list, int *i, int j)
{
	t_lex	*new;

	while (lex_var->args[*i][j])
	{
		if (lex_var->args[*i][j] == '\"' || lex_var->args[*i][j] == '\'')
		{
			if (lex_var->args[*i][j] == '\'')
			{
				lex_var->args[*i][ft_strlen(lex_var->args[*i])] = '\0';
				new = ft_lstnew_lex(lex_var, lex_var->args[*i], list, SINGLE_QUOTE);
				lex_add_string(list, SINGLE_QUOTE, &new);
			}
			else if (lex_var->args[*i][j] == '\"')
			{
				lex_var->args[*i][ft_strlen(lex_var->args[*i])] = '\0';
				new = ft_lstnew_lex(lex_var, lex_var->args[*i], list, DOUBLE_QUOTE);
				lex_add_string(list, DOUBLE_QUOTE, &new);
			}
			(*i)++;
			return (true);
		}
		j++;
	}
	return (false);
}

t_lex	*lexer(t_lex_var *lex_var, t_lex **list)
{
	int		i;
	int		j;
	t_lex	*tmp;

	i = 0;
	tmp = *list;
	while (lex_var->args[i])
	{
		j = 0;
		if (lex_string(lex_var, list, &i, j) == true)
			continue ;
		if (lex_sign(lex_var, list, &i, j) == true)
			continue ;
		lex_word(lex_var, list, &i);
	}
	tmp = *list;
	return (tmp);
}
