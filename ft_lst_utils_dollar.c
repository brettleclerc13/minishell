/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:09:31 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/08 21:34:31 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	d_lst_var(t_dollar **d_lst, char *content, int *i, int *start)
{
	t_dollar	*new;

	new = malloc(sizeof(t_dollar));
	if (!new)
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return ;
	}
	new->next = NULL;
	(*i)++;
	new->variable = 1;
	*start = *i;
	while (content[*i] && !is_specialchar(content[*i]))
		(*i)++;
	new->content = ft_substr(content, *start, *i - *start);
	ft_lstadd_back_dollar(d_lst, new);
	*start = *i;
}

void	d_lst_lonedol(t_dollar **d_lst, int *i, int *start)
{
	t_dollar	*new;

	new = malloc(sizeof(t_dollar));
	if (!new)
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return ;
	}
	new->next = NULL;
	new->variable = 0;
	new->content = ft_strdup("$");
	ft_lstadd_back_dollar(d_lst, new);
	*start = *i;
}

void	d_lst_status(t_dollar **d_lst, char *content, int *i, int *start)
{
	t_dollar	*new;

	new = malloc(sizeof(t_dollar));
	if (!new)
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return ;
	}
	new->next = NULL;
	new->variable = 0;
	if (content[*i + 1] == '$')
		new->content = ft_strdup("`PID'");
	else if (content[*i + 1] == '?')
		new->content = ft_itoa(g_var);
	ft_lstadd_back_dollar(d_lst, new);
	*i += 2;
	*start = *i;
}

void	d_lst_string(t_dollar **d_lst, char *content, int *i, int *start)
{
	t_dollar	*new;

	new = malloc(sizeof(t_dollar));
	if (!new)
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return ;
	}
	new->next = NULL;
	if (!content[*i + 1])
		(*i)++;
	new->variable = 0;
	new->content = ft_substr(content, *start, *i - *start);
	ft_lstadd_back_dollar(d_lst, new);
	*start = *i;
}
