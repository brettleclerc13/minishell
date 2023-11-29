/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:55:51 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/29 12:04:23 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_specialchar(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (true);
	return (false);
}

bool	is_dollar(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '$')
			return (true);
	return (false);
}

bool	is_single_quote(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '\'')
			return (true);
	return (false);
}

bool	is_double_quote(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '\"')
			return (true);
	return (false);
}

static char	*remove_double_quotes(char *content)
{
	char	**split;
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	split = NULL;
	if (!content || !is_double_quote(content))
		return (content);
	split = ft_split(content, '\"');
	i = -1;
	while (split[++i])
		tmp = ft_strjoin_dollar(tmp, split[i]);
	ft_arrayfree(split);
	free(content);
	return (tmp);
}

char	*d_lst_expansion(t_dollar *d_lst, char **envp)
{
	char	*tmp;

	tmp = NULL;
	while (d_lst)
	{
		if (d_lst->variable)
		{
			if (ft_varcmp(d_lst->content, envp))
			{
				d_lst->content = ft_strjoin_dollar(d_lst->content, "=");
				if (!get_env_value(d_lst->content, envp))
 				break ;
 				tmp = ft_strjoin_dollar(tmp, get_env_value(d_lst->content, envp));
			}
		}
		else
			tmp = ft_strjoin_dollar(tmp, d_lst->content);
		free(d_lst->content);
		d_lst = d_lst->next;
	}
	tmp = remove_double_quotes(tmp);
	return (tmp);
}

void	d_lst_creation(t_dollar **d_lst, char *content)
{
	int		i;
	int		start;
	bool	increment;

	i = 0;
	start = 0;
	while (content[i])
	{
		increment = true;
		if (content[i] == '$' || !content[i + 1])
		{
			if (start != i || !content[i + 1])
				d_lst_string(d_lst, content, &i, &start);
			if (content[i] == '$' && (content[i + 1] == '$' || content[i + 1] == '?'))
			{
				d_lst_pid_exitstatus(d_lst, content, &i, &start);
				increment = false;
			}
			else if (content[i] == '$' && (!is_specialchar(content[i + 1])))
			{
				d_lst_var(d_lst, content, &i, &start);
				increment = false;
			}
			else if (content[i] == '$')
				d_lst_lonedol(d_lst, &i, &start);
		}
		if (increment)
			i++;
	}
}

bool	check_dollar(t_lex **list, char **envp)
{
	char		*result;
	t_dollar	*d_lst;
	bool		double_quote;

	result = NULL;
	d_lst = NULL;
	double_quote = false;
	if (!is_dollar((*list)->content) || is_single_quote((*list)->content))
		return (true);
	if (is_double_quote((*list)->content))
		double_quote = true;
	d_lst_creation(&d_lst, (*list)->content);
	result = d_lst_expansion(d_lst, envp);
	while (d_lst)
	{
		free(d_lst);
		d_lst = d_lst ->next;
	}
	 if (!result)
	 {
	 	result = ft_strdup("\0");
		if (double_quote == false)
			(*list)->token = SKIP;			//need to follow this up in series and exec
	 }
	free((*list)->content);
	(*list)->content = result;
	return (true);
}
