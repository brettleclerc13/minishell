/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils_lex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:46:42 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/03 11:43:44 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lex	*ft_lstlast_lex(t_lex *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_lex(t_lex **lst, t_lex *new)
{
	t_lex	*tmp;

	if ((*lst) == NULL)
	{
		(*lst) = new;
		return ;
	}
	tmp = ft_lstlast_lex(*lst);
	tmp->next = new;
}

char	*ft_if_quotes(t_lex_var *lex_var, char *content)
{
	int		i;
	char	quote;
	char	*tmp;
	int		check_dol;

	i = -1;
	check_dol = -1;
	tmp = NULL;
	quote = '\0';
	while (content[++i])
	{
		if (content[i] == '\"' || content[i] == '\'')
		{
			quote = content[i];
			while (content[++i] && content[i] != quote)
			{
				if (content[i] == '$' && quote == '\"')
					check_dol = i;
				if (!tmp)
					tmp = ft_substr(content, i, 1);
				else
					tmp = ft_strjoin_path(tmp, ft_substr(content, i, 1), true);
			}
			if (check_dol != -1)
				check_dollar(&tmp, lex_var->envp);
			i++;
		}
		if (!tmp)
			tmp = ft_substr(content, i, 1);
		else if (content[i])
			tmp = ft_strjoin_path(tmp, ft_substr(content, i, 1), true);
	}
	return (tmp);
}

t_lex	*ft_lstnew_lex(t_lex_var *lex_var, void *content, enum e_token token)
{
	t_lex	*new;

	new = malloc (sizeof(t_lex));
	if (!new)
		return (NULL);
	if (token == SINGLE_QUOTE || token == DOUBLE_QUOTE)
		new->content = ft_strdup(ft_if_quotes(lex_var, (char*)content));
	else
		new->content = ft_strdup(content);
	new->token = token;
	new->next = NULL;
	return (new);
}
