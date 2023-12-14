/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:09:31 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/14 17:26:14 by ehouot           ###   ########.fr       */
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
	*start = *i + 1;
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

void	d_lst_string(t_dollar **d_lst, char *content, t_dol_var *dol)
{
	t_dollar	*new;

	new = malloc(sizeof(t_dollar));
	if (!new)
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return ;
	}
	new->next = NULL;
	if (!content[dol->i + 1])
		(dol->i)++;
	new->variable = 0;
	new->content = ft_substr(content, dol->start, dol->i - dol->start);
	ft_lstadd_back_dollar(d_lst, new);
	dol->start = dol->i;
	dol->increment = false;
}
