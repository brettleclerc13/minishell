/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serie.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:52:57 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/07 18:06:50 by ehouot           ###   ########.fr       */
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

void	ft_set_redirections(t_lex *tmp, t_serie **new, int start, int end)
{
	while (tmp && start < end && tmp->token != 4)
	{
		if (tmp->token == RIGHT_CHEV)
		{
			tmp = tmp->next;
			(*new)->fd_out = open(tmp->content, O_RDWR | O_TRUNC | O_CREAT, 0644);
		}
		if (tmp->token == DOUBLE_R_CHEV)
		{
			tmp = tmp->next;
			(*new)->fd_out = open(tmp->content, O_RDWR | O_APPEND | O_CREAT, 0644);
		}
		if (tmp->token == LEFT_CHEV)
		{
			tmp = tmp->next;
			(*new)->fd_in = open(tmp->content, O_RDWR, 0666);
		}
		if (tmp->token == DOUBLE_L_CHEV)
			(*new)->fd_in = -5;
		tmp = tmp->next;
	}
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
	ft_set_redirections(tmp, new, start, end);
	i = 0;
	while (tmp && start < end && tmp->token != 4)
	{
		array[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
		start++;
	}
	if (tmp)
		(*new)->fd_out_token = tmp->token;
	else
		(*new)->fd_out_token = END;
	return (array);
}

t_serie	*ft_lstnew_serie(t_lex *args, int start, int end)
{
	t_serie	*new;

	new = malloc (sizeof(t_serie));
	if (!new)
		return (NULL);
	new->fd_out_token = ZERO;
	new->fd_in = 0;
	new->fd_out = 0;
	new->cmd_token = ZERO;
	new->cmd = ft_serie_array(args, &new, start, end);
	new->next = NULL;
	return (new);
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
		if (!tmp_arg->next)
		{
			new = ft_lstnew_serie(mshell->args, j , i);
			ft_lstadd_back_serie(series, new);
		}
        i++;
		tmp_arg = tmp_arg->next;
	}
}
