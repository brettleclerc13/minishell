/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:17:25 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/06 10:38:46 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_parser_error(char *pre_msg, char *post_msg, char *content)
{
	ft_putstr_fd(pre_msg, 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd(post_msg, 2);
	return (false);
}

bool	check_redir(t_lex **list)
{
	t_lex	*tmp;

	tmp = *list;
	if ((*list)->token >= 0 && (*list)->token <= 3)
	{
		if (tmp->next == NULL)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			return (false);
		}
		tmp = tmp->next;
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
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (false);
		}
		tmp = tmp->next;
		if (tmp->token == PIPE)
		{
			ft_putstr_fd("minishell: double pipe not supported\n", 2);
			return (false);
		}
	}
	return (true);
}

bool	parser(t_lex **list, char **envp)
{
	t_lex	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (check_double_pipe(&tmp) == false || check_redir(&tmp) == false)
		{
			g_var = 2;
			return (false);
		}
		if (tmp->token != SINGLE_QUOTE)
		{
			if (check_dollar(&tmp->content, envp, tmp->token) == false)
			{
				g_var = 1;
				return (false);
			}
			if (!tmp->content[0] && tmp->token != DOUBLE_QUOTE)
				tmp->token = SKIP;
		}
		tmp = tmp->next;
	}
	return (true);
}
