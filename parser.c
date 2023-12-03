/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:17:25 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/03 10:55:47 by ehouot           ###   ########.fr       */
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
	t_lex			*tmp;

	tmp = *list;
	while (tmp)
	{
		if (check_double_pipe(&tmp) == false || check_redir(&tmp) == false)
		{
			g_var = 2;
			return (false);
		}
		if (check_dollar(&tmp->content, envp) == false)
		{
			g_var = 1;
			return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}
