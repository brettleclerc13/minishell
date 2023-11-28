/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:09:31 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/28 12:17:15 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_dollar_lst	*ft_lstlast_dollar(t_dollar_lst *d_lst)
{
	if (!d_lst)
		return (d_lst);
	while (d_lst->next)
		d_lst = d_lst->next;
	return (d_lst);
}

static void	ft_lstadd_back_dollar(t_dollar_lst **d_lst, t_dollar_lst *new)
{
	t_dollar_lst	*tmp;

	if (!(*d_lst))
	{
		(*d_lst) = new;
		return ;
	}
	tmp = ft_lstlast_dollar(*d_lst);
	tmp-> next = new;
}

void	d_lst_var(t_dollar_lst **d_lst, char *content, int *i, int *start)
{
	t_dollar_lst	*new;
	
	new = malloc(sizeof(t_dollar_lst));
	if (!new)
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return ;
	}
	(*i)++;
	new->variable = 1;
	*start = *i;
	while (content[*i] && !is_specialchar(content[*i]))
		(*i)++;
	new->content = ft_substr(content, *start, *i - *start);
	ft_lstadd_back_dollar(d_lst, new);
	*start = *i;
}

void	d_lst_lonedol(t_dollar_lst **d_lst, int *i, int *start)
{
	t_dollar_lst	*new;
	
	new = malloc(sizeof(t_dollar_lst));
	if (!new)
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return ;
	}
	new->variable = 0;
	new->content = ft_strdup("$");
	ft_lstadd_back_dollar(d_lst, new);
	*start = *i;
}

void	d_lst_pid_exitstatus(t_dollar_lst **d_lst, char *content, int *i, int *start)
{
	t_dollar_lst	*new;
	
	new = malloc(sizeof(t_dollar_lst));
	if (!new)
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return ;
	}
	new->variable = 0;
	if (content[*i + 1] == '$')
		new->content = ft_strdup("`PID'");
	else if (content[*i + 1] == '?')
		new->content = ft_itoa(g_var);
	ft_lstadd_back_dollar(d_lst, new);
	*i += 2;
	*start = *i;
}

void	d_lst_string(t_dollar_lst **d_lst, char *content, int *i, int *start)
{
	t_dollar_lst	*new;
	
	new = malloc(sizeof(t_dollar_lst));
	if (!new)
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return ;
	}
	if (!content[*i + 1])
		(*i)++;
	new->variable = 0;
	new->content = ft_substr(content, *start, *i - *start);
	ft_lstadd_back_dollar(d_lst, new);
	*start = *i;
}
