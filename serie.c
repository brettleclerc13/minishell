/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serie.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:52:57 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/09 12:30:36 by brettlecler      ###   ########.fr       */
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


char	**ft_serie_array(t_lex *args, t_serie **new, int i)
{
	t_lex	*tmp;
	char	**array;
	int		j;

	j = -1;
	array = ft_calloc((i + 1) - ft_count_redir(args) * 2, sizeof(char *));
	if (!array)
		return (NULL);
	tmp = args;
	(*new)->cmd_token = tmp->token;
	if (ft_set_redirections(tmp, new) == -1)
		return (NULL);
	while (tmp && tmp->token != 4)
	{
		if (tmp->token == RIGHT_CHEV || tmp->token == DOUBLE_R_CHEV \
			|| tmp->token == LEFT_CHEV || tmp->token == DOUBLE_L_CHEV)
			tmp = tmp->next;
		else
			array[++j] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (array);
}

t_serie	*ft_lstnew_serie(t_lex *args, int i, bool ispipe)
{
	t_serie	*new;

	new = malloc(sizeof(t_serie));
	if (!new)
		return (NULL);
	if (ispipe == true)
		new->fd_out_token = PIPE;
	else
		new->fd_out_token = END;
	new->fd_in = 0;
	new->fd_out = 1;
	new->pid = 0;
	new->cmd_token = ZERO;
	new->hd = false;
	new->hd_limiter = NULL;
	new->cmd = ft_serie_array(args, &new, i);
	new->next = NULL;
	return (new);
}

void	serie_creation(t_struct *mshell, t_serie **series)
{
	int		i;
	t_serie	*new;
	t_lex	*tmp;

	i = 1;
	new = NULL;
	tmp = mshell->args;
	while (mshell->args)
	{
		if (mshell->args->token == PIPE)
		{
			new = ft_lstnew_serie(tmp, i, true);
			ft_lstadd_back_serie(series, new);
			i = 0;
			tmp = mshell->args;
		}
		else if (!mshell->args->next)
		{
			new = ft_lstnew_serie(tmp, i, false);
			ft_lstadd_back_serie(series, new);
		}
		i++;
		mshell->args = mshell->args->next;
	}
}
