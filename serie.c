/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serie.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:15:30 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/29 09:00:32 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_serie	*ft_lstlast_serie(t_serie *series)
{
	if (series == NULL)
		return (series);
	while (series->next != NULL)
	{
		series = series->next;
	}
	return (series);
}

void	ft_lstadd_back_serie(t_serie **series, t_serie *new)
{
	t_serie	*tmp;

	if ((*series) == NULL)
	{
		(*series) = new;
		return ;
	}
	tmp = ft_lstlast_serie(*series);
	tmp->next = new;
}

t_serie	*ft_lstnew_serie(t_lex *args, int start, int end)
{
	t_serie	*new;

	new = malloc (sizeof(t_serie));
	if (!new)
		return (NULL);
	new->cmd = ft_serie_array(args, &new, start, end);
	new->next = NULL;
	return (new);
}

char	**ft_serie_array(t_lex *args, t_serie **new, int start, int end)
{
	t_lex	*tmp;
	char	**array;
	int		i;
	
	i = -1;
	array = ft_calloc((end - start) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	tmp = args;
	while (tmp && ++i < start)
		tmp = tmp->next;
	(*new)->cmd_token = tmp->token;
	i = 0;
	while (tmp && start < end)
	{
		array[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
		start++;
	}
	if (tmp)
		(*new)->fd_token = tmp->token;
	return (array);
}

void	serie_creation(t_struct *mshell, t_serie **series)
{
	int		i;
	int		j;
	t_serie	*new;
	t_lex	*tmp_arg;

	i = 1;
	j = 0;
	new = NULL;
	tmp_arg = mshell->args;
	while (tmp_arg)
	{
		if (tmp_arg->token >= 0 && tmp_arg->token <= 4)
		{
			new = ft_lstnew_serie(mshell->args, j , i);
			ft_lstadd_back_serie(series, new);
			j = i;
		}
		i++;
		if (!tmp_arg->next)
		{
			new = ft_lstnew_serie(mshell->args, j , i);
			ft_lstadd_back_serie(series, new);
		}
		tmp_arg = tmp_arg->next;
	}
}
