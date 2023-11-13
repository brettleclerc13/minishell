/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:17:25 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/13 12:08:58 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_parser_error(char *pre_msg, char* post_msg, char *content)
{
	ft_putstr_fd(pre_msg, 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd(post_msg, 2);
	return (false);
}

bool	check_redir(t_lex **list, enum e_token prev_tok)
{
	t_lex	*tmp;

	tmp = *list;
	if ((*list)->token >= 0 && (*list)->token <= 3)
	{
		if (tmp->next == NULL)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			return (false);
		}
		tmp = tmp->next;
		if ((*list)->token == LEFT_CHEV && prev_tok == (enum e_token) -1 \
			&& (open(tmp->content, O_RDONLY) == -1))
			return (ft_parser_error("minishell: ", ": No such file or directory\n", tmp->content));
		if ((tmp->token >= 0 && tmp->token <= 4))
			return (ft_parser_error("minishell: syntax error near unexpected token `", "'\n", tmp->content));
	}
	return (true);
}

bool	check_double_pipe(t_lex **list)
{
	t_lex	*tmp;

	tmp = *list;
	if ((*list)->token == PIPE)
	{
		if (tmp->next == NULL)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			return (false);
		}
		tmp = tmp->next;
		if (tmp->token == PIPE)
		{
			ft_putstr_fd("minishell: double pipe not supported\n", 2); // faire retourner le prompt
			return (false);
		}
	}
	return (true);
}

bool	parser(t_lex **list, char **envp)
{
	enum e_token	prev_tok;
	t_lex			*tmp;

	prev_tok = -1;
	tmp = *list;
	while (tmp)
	{
		if (check_double_pipe(&tmp) == false)
			return (false);
		if (check_dollar(&tmp, envp) == false)
			return (false);
		if (tmp->content == NULL)
			tmp->content = "\0";
		if (check_redir(&tmp, prev_tok) == false)
			return (false);
		prev_tok = tmp->token;
		tmp = tmp->next;
	}
	return (true);
}
