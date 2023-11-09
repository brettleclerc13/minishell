/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serie.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:52:57 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/08 15:35:56 by brettlecler      ###   ########.fr       */
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

void	ft_set_redirections(t_lex **args, t_serie **new)
{
	enum e_token	tmp_token;

	tmp_token = (*args)->token;
	if (tmp_token == RIGHT_CHEV)
		(*new)->fd_out = open((*args)->content, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (tmp_token == DOUBLE_R_CHEV)
		(*new)->fd_out = open((*args)->content, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (tmp_token == LEFT_CHEV)
		(*new)->fd_in = open((*args)->content, O_RDWR, 0666);
	if (tmp_token == DOUBLE_L_CHEV)
		(*new)->fd_in = -5;
	*args = (*args)->next;
}

char	**ft_serie_array(t_lex *args, t_serie **new)
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
	ft_set_redirections(tmp, new, start, end);
	i = 0;
	while (tmp && start < end && tmp->token != 4)
	{
		array[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
		start++;
	}
	if (tmp)
		(*new)->is_pipe = true;
	return (array);
}
void	ft_serie(t_lex *args, t_serie **new)
{
	while (args && args->token != PIPE)
	{
		if (args->token >= 0 && args->token <= 3)
			ft_set_redirections(&args, new);
		else
			ft_serie_array(args, new);
		args = args->next;
	}
}


t_serie	*ft_lstnew_serie(t_lex *args)
{
	t_serie	*new;

	new = malloc(sizeof(t_serie));
	if (!new)
		return (NULL);
	new->is_pipe = false;
	new->fd_in = 0;
	new->fd_out = 0;
	new->cmd = ft_calloc(1, sizeof(char *));
	new->next = NULL;
	ft_serie(args, &new);
	return (new);
}

void	serie_creation(t_struct *mshell, t_serie **series)
{
	t_serie	*new;
	t_lex	*tmp_arg;

	new = NULL;
	tmp_arg = mshell->args;
	while (tmp_arg)
	{
		if (tmp_arg->token == PIPE)
		{
			new = ft_lstnew_serie(mshell->args);
			ft_lstadd_back_serie(series, new);
		}
		if (!tmp_arg->next)
		{
			new = ft_lstnew_serie(mshell->args);
			ft_lstadd_back_serie(series, new);
		}
		mshell->args = tmp_arg;
		tmp_arg = tmp_arg->next;
	}
}
