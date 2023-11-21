/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:03:33 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/20 13:31:48 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_heredoc(t_lex *args)
{
	int		nb_heredoc;
	t_lex	*tmp;

	nb_heredoc = 0;
	tmp = args;
	while (tmp)
	{
		if (tmp->token == DOUBLE_L_CHEV)
			nb_heredoc++;
		tmp = tmp->next;
	}
	return (nb_heredoc);
}

void	ft_here_doc(t_lex *tmp, t_serie **new, int nb_heredoc)
{
	char	*str;
	
	if (nb_heredoc == 0)
	{
		if (pipe(&(*new)->fd_in) == -1)
			ft_error("here_doc pipe error\n"); // juste pour test
	}
	while (1)
	{
		str = readline("> ");
		if (ft_strcmp(str, tmp->content) == 0)
		{
			free(str);
			break ;
		}
		// write(1, str, ft_strlen(str) + 1);
		if (nb_heredoc == 0)
			write((*new)->fd_in, str, ft_strlen(str) + 1);
	}
}
