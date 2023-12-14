/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:29:32 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/12 11:47:08 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_permissions(char *file, enum e_token token)
{
	if (!file[0] && token != DOUBLE_QUOTE)
	{
		ft_put_ambiguous_error(file);
		return ;
	}
	if (access(file, X_OK) == -1)
	{
		if (errno == EACCES)
			g_var = 126;
		else
			g_var = 1;
		ft_put_redir_error(file, false);
	}
}

static void	heredoc_redir(t_lex *tmp_hd, t_serie **new, int nb_heredoc)
{
	while (tmp_hd && tmp_hd->token != 4)
	{
		if (tmp_hd->token == DOUBLE_L_CHEV)
		{
			nb_heredoc -= 1;
			fd_in_redir(tmp_hd, new, nb_heredoc);
		}
		tmp_hd = tmp_hd->next;
	}
}

void	ft_set_redirections(t_lex *tmp, t_serie **new)
{
	t_lex	*tmp_hd;
	int		nb_heredoc;

	tmp_hd = tmp;
	nb_heredoc = ft_count_heredoc(tmp);
	if (nb_heredoc > 0)
		heredoc_redir(tmp_hd, new, nb_heredoc);
	while (tmp && tmp->token != 4)
	{
		if (tmp->token == RIGHT_CHEV || tmp->token == DOUBLE_R_CHEV)
			fd_out_redir(tmp, new);
		else if (tmp->token == LEFT_CHEV)
			fd_in_redir(tmp, new, 0);
		else if (tmp->token == DOUBLE_L_CHEV)
		{
			if ((*new)->fd_in == -1)
				return ;
			if ((*new)->fd_in != STDIN_FILENO && (*new)->fd_in != -1)
				close((*new)->fd_in);
			(*new)->fd_in = dup((*new)->fd_hd);
			close((*new)->fd_hd);
		}
		tmp = tmp->next;
	}
}
