/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:55:51 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/08 21:59:15 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_specialchar(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (true);
	return (false);
}

static bool	is_dollar(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (false);
	while (s[++i])
		if (s[i] == '$')
			return (true);
	return (false);
}

static char	*remove_white_space(char *content)
{
	char	**split;
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	split = NULL;
	if (!content)
		return (content);
	split = ft_split(content, ' ');
	free(content);
	i = -1;
	while (split[++i])
	{
		tmp = ft_strjoin_dol(tmp, split[i]);
		if (split[i + 1])
			tmp = ft_strjoin_dol(tmp, " ");
	}
	ft_arrayfree(split);
	return (tmp);
}

bool	check_dollar(char **content, char **envp, enum e_token token)
{
	char		*result;
	t_dollar	*d_lst;

	result = NULL;
	d_lst = NULL;
	if (!is_dollar(*content))
		return (false);
	d_lst_creation(&d_lst, *content);
	result = d_lst_expansion(d_lst, envp);
	while (d_lst)
	{
		free(d_lst);
		d_lst = d_lst ->next;
	}
	if (token == WORD)
		result = remove_white_space(result);
	if (!result)
		result = ft_strdup("\0");
	free(*content);
	*content = result;
	return (true);
}
