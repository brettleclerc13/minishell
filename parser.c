/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:17:25 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/07 18:04:31 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	opening_redir(t_lex **list, enum e_token prev_tok, t_lex *tmp)
// {
// 	(void)prev_tok;
// 	tmp = tmp->next;

// 	if ((*list)->token == RIGHT_CHEV && tmp->token == WORD)
// 		open(tmp->content, O_RDWR | O_TRUNC | O_CREAT, 0644);
// }

bool	check_redir(t_lex **list, enum e_token prev_tok)
{
	t_lex	*tmp;

	tmp = *list;
	if ((*list)->token >= 0 && (*list)->token <= 3)
	{
		if (tmp->next == NULL)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (true);
		}
		// opening_redir(list, prev_tok, tmp);
		tmp = tmp->next;
		if ((*list)->token == LEFT_CHEV && prev_tok == (enum e_token)-1 \
			&& (open(tmp->content, O_RDONLY) == -1))
		{
			printf("minishell: %s: No such file or directory\n", tmp->content);
			return (true);
		}
		if ((tmp->token >= 0 && tmp->token <= 4))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", tmp->content);
			return (true);
		}
	}
	return (false);
}

bool	check_double_pipe(t_lex **list)
{
	t_lex	*tmp;

	tmp = *list;
	if ((*list)->token == PIPE)
	{
		if (tmp->next == NULL)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (true);
		}
		tmp = tmp->next;
		if (tmp->token == PIPE)
		{
			printf("Double pipe not supported\n"); // faire retourner le prompt
			return (true);
		}
	}
	return (false);
}

bool	parser(t_lex **list, char **envp)
{
	enum e_token	prev_tok;
	t_lex			*tmp;

	prev_tok = -1;
	tmp = *list;
	while (tmp)
	{
		if (check_double_pipe(&tmp) == true) // cas des doubles pipes
			return (true);
		check_dollar(&tmp, envp); // cas des dollars
		if (tmp->content == NULL)
			tmp->content = "\0";
		if (check_redir(&tmp, prev_tok) == true) // cas des redirections
			return (true);
		prev_tok = tmp->token;
		tmp = tmp->next;
	}
	return (false);
}
