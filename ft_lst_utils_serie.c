/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils_serie.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:12:53 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/15 08:59:29 by brettlecler      ###   ########.fr       */
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
	new->prev = tmp;
	tmp->next = new;
}

char	**ft_serie_array(t_lex *args, t_serie **new, int count)
{
	t_lex	*tmp;
	char	**array;
	int		j;

	j = -1;
	array = ft_calloc((count - (ft_count_redir(args) * 2)) + 1, sizeof(char *));
	if (!array)
		return (print_array_malloc_error());
	tmp = args;
	ft_set_redirections(tmp, new);
	tmp = args;
	while (tmp && tmp->token != 4)
	{
		if (tmp->token == RIGHT_CHEV || tmp->token == DOUBLE_R_CHEV \
			|| tmp->token == LEFT_CHEV || tmp->token == DOUBLE_L_CHEV)
			tmp = tmp->next;
		else if (tmp->content)
			array[++j] = ft_strdup(tmp->content);
		else
			array[++j] = ft_strdup("\0");
		tmp = tmp->next;
	}
	if (!array[0])
		array[++j] = ft_strdup("\0");
	return (array);
}

static t_serie	*print_serie_malloc_error(void)
{
	ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
	return (NULL);
}

t_serie	*ft_lstnew_serie(t_lex *args, int count, bool ispipe)
{
	t_serie	*new;

	new = malloc(sizeof(t_serie));
	if (!new)
		return (print_serie_malloc_error());
	new->fd_out_token = END;
	if (ispipe == true)
		new->fd_out_token = PIPE;
	new->pipe_hd[0] = STDIN_FILENO;
	new->pipe_hd[1] = STDOUT_FILENO;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->pid = 0;
	new->fd_hd = STDIN_FILENO;
	new->first_arg_token = args->token;
	new->cmd = ft_serie_array(args, &new, count);
	if (!new->cmd)
	{
		free(new);
		return (NULL);
	}
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
