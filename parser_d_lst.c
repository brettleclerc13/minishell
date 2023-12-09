/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_d_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:29:03 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/08 22:23:13 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dollar	*ft_lstlast_dollar(t_dollar *d_lst)
{
	if (d_lst == NULL)
		return (d_lst);
	while (d_lst->next != NULL)
		d_lst = d_lst->next;
	return (d_lst);
}

void	ft_lstadd_back_dollar(t_dollar **d_lst, t_dollar *new)
{
	t_dollar	*tmp;

	if (!(*d_lst))
	{
		(*d_lst) = new;
		return ;
	}
	tmp = ft_lstlast_dollar(*d_lst);
	tmp->next = new;
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
				d_lst->content = ft_strjoin_dol(d_lst->content, "=");
				if (!get_env_value(d_lst->content, envp))
					break ;
				tmp = ft_strjoin_dol(tmp, get_env_value(d_lst->content, envp));
			}
		}
		else
			tmp = ft_strjoin_dol(tmp, d_lst->content);
		free(d_lst->content);
		d_lst = d_lst->next;
	}
	return (tmp);
}

static void	d_lst_contd(t_dol_var *dol, t_dollar **d_lst, char *str, bool var)
{
	if (var)
	{
		d_lst_var(d_lst, str, &dol->i, &dol->start);
		dol->increment = false;
	}
	else
	{
		d_lst_status(d_lst, str, &dol->i, &dol->start);
		dol->increment = false;
	}
}

void	d_lst_creation(t_dollar **d_lst, char *str)
{
	t_dol_var	dol;

	dol.i = 0;
	dol.start = 0;
	while (str[dol.i])
	{
		dol.increment = true;
		if (str[dol.i] == '$' || !str[dol.i + 1])
		{
			if (dol.start != dol.i || !str[dol.i + 1])
				d_lst_string(d_lst, str, &dol.i, &dol.start);
			if (str[dol.i] == '$' && (str[dol.i + 1] == '$' \
				|| str[dol.i + 1] == '?'))
				d_lst_contd(&dol, d_lst, str, false);
			else if (str[dol.i] == '$' && (!is_specialchar(str[dol.i + 1])))
				d_lst_contd(&dol, d_lst, str, true);
			else if (str[dol.i] == '$')
				d_lst_lonedol(d_lst, &dol.i, &dol.start);
		}
		if (dol.increment)
			dol.i++;
	}
}
