/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:45:40 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/08 21:38:11 by brettlecler      ###   ########.fr       */
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
	else if (lex_var->args[*i][j] == '<' && lex_var->args[*i][j + 1] == '<' \
		&& !lex_var->args[*i][j + 1])
		save_tok = DOUBLE_L_CHEV;
	else if (lex_var->args[*i][j] == '>' && lex_var->args[*i][j + 1] == '>' \
		&& !lex_var->args[*i][j + 1])
		save_tok = DOUBLE_R_CHEV;
	if (save_tok >= 0 && save_tok <= 4)
	{
		new = ft_lstnew_lex(lex_var->args[*i], save_tok);
		ft_lstadd_back_lex(list, new);
		(*i)++;
		return (true);
	}
	return (false);
}

static void	lex_word(t_lex_var *lex_var, t_lex **list, int *i)
{
	ft_split_word(lex_var->args[*i], list);
	(*i)++;
}

static void	ft_expand_quotes(t_lex_var *lex_var, t_lex **list)
{
	t_lex	*tmp_list;
	char	*swap_str;
	char	quote;
	char	*tmp;

	tmp_list = *list;
	quote = '\0';
	tmp = NULL;
	while (tmp_list)
	{
		if (contains_quotes(tmp_list->content))
		{
			swap_str = ft_strdup(tmp_list->content);
			free(tmp_list->content);
			tmp_list->content = quotes(lex_var, swap_str, quote, tmp);
			free(swap_str);
		}
		tmp_list = tmp_list->next;
	}
}

static bool	lex_string(t_lex_var *lex_var, t_lex **list, int *i, int j)
{
	while (lex_var->args[*i][j])
	{
		if (lex_var->args[*i][j] == '\"' || lex_var->args[*i][j] == '\'')
		{
			if (lex_var->args[*i][j] == '\'')
			{
				lex_var->args[*i][ft_strlen(lex_var->args[*i])] = '\0';
				ft_split_string(lex_var->args[*i], list, SINGLE_QUOTE);
				ft_expand_quotes(lex_var, list);
			}
			else if (lex_var->args[*i][j] == '\"')
			{
				lex_var->args[*i][ft_strlen(lex_var->args[*i])] = '\0';
				ft_split_string(lex_var->args[*i], list, DOUBLE_QUOTE);
				ft_expand_quotes(lex_var, list);
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
