/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 22:41:55 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/15 08:19:20 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	pre_check_fd_out(t_serie **new)
{
	if ((*new)->fd_out != STDOUT_FILENO && (*new)->fd_out != -1)
	{
		close((*new)->fd_out);
		(*new)->fd_out = STDOUT_FILENO;
	}
	if ((*new)->fd_out == -1 || (*new)->fd_in == -1 || (*new)->fd_hd == -1)
		return (false);
	return (true);
}

static bool	pre_check_fd_in(t_serie **new)
{
	if ((*new)->fd_in == -1 || (*new)->fd_hd == -1)
		return (false);
	if ((*new)->fd_in != STDIN_FILENO)
	{
		close((*new)->fd_in);
		(*new)->fd_in = STDIN_FILENO;
	}
	return (true);
}

static void	double_l_chev(t_lex *tmp, t_serie **new, int nb_heredoc)
{
	tmp = tmp->next;
	waitpid(ft_here_doc(tmp, new, nb_heredoc), &g_var, WUNTRACED);
	ft_termios(true);
	signals_types();
	if ((*new)->fd_hd == -1)
		ft_put_redir_error(tmp->content, false);
}

void	fd_in_redir(t_lex *tmp, t_serie **new, int nb_heredoc)
{
	if (!pre_check_fd_in(new))
		return ;
	if (tmp->token == LEFT_CHEV)
	{
		tmp = tmp->next;
		if (tmp->token == DOLLAR)
		{
			amb_error_minus_one(tmp->content, new, true);
			return ;
		}
		if (open(tmp->content, O_DIRECTORY) != -1)
		{
			ft_put_redir_error(tmp->content, true);
			(*new)->fd_in = -1;
			return ;
		}
		(*new)->fd_in = open(tmp->content, O_RDWR, 0644);
	}
	if (tmp->token == DOUBLE_L_CHEV)
		double_l_chev(tmp, new, nb_heredoc);
	if ((*new)->fd_in == -1)
		check_permissions(tmp->content, tmp->token);
}

void	fd_out_redir(t_lex *tmp, t_serie **new)
{
	if (!pre_check_fd_out(new))
		return ;
	if (tmp->token == RIGHT_CHEV)
	{
		tmp = tmp->next;
		if (tmp->token == DOLLAR)
		{
			amb_error_minus_one(tmp->content, new, false);
			return ;
		}
		(*new)->fd_out = open(tmp->content, O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	if (tmp->token == DOUBLE_R_CHEV)
	{
		tmp = tmp->next;
		if (tmp->token == DOLLAR)
		{
			amb_error_minus_one(tmp->content, new, false);
			return ;
		}
		(*new)->fd_out = open(tmp->content, O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	if ((*new)->fd_out == -1)
		check_permissions(tmp->content, tmp->token);
}
