/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:29:32 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/29 14:23:29 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_put_redir_error(char *file, bool is_dir)
{
	char	*tmp;

	tmp = NULL;
	if (is_dir)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": is a directory\n", 2);
		g_var = 1;
		return ;
	}
	tmp = ft_strjoin("minishell: ", file);
	perror(tmp);
	free(tmp);
}

static void	check_permissions(char *file)
{
	if (access(file, X_OK) == -1)
	{
		if (errno == EACCES)
			g_var = 126;
		else
			g_var = 1;
		ft_put_redir_error(file, false);
	}
}

static void	fd_in_redir(t_lex *tmp, t_serie **new, int nb_heredoc)
{
	if (tmp->token == LEFT_CHEV)
	{
		tmp = tmp->next;
		if (open(tmp->content, O_DIRECTORY) != -1)
		{
			ft_put_redir_error(tmp->content, true);
			(*new)->fd_in = -1;
			return ;
		}
		(*new)->fd_in = open(tmp->content, O_RDWR, 0644);
	}
	if (tmp->token == DOUBLE_L_CHEV)
	{
		tmp = tmp->next;
		ft_here_doc(tmp, new, nb_heredoc);
		if ((*new)->fd_in == -1)
			ft_put_redir_error(tmp->content, true);
	}
	if ((*new)->fd_in == -1)
		check_permissions(tmp->content);
}

static void	fd_out_redir(t_lex *tmp, t_serie **new)
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
	if ((*new)->fd_out == -1)
		check_permissions(tmp->content);
}

void	ft_set_redirections(t_lex *tmp, t_serie **new)
{
	int	nb_heredoc;

	nb_heredoc = ft_count_heredoc(tmp);
	while (tmp && tmp->token != 4)
	{
		if (tmp->token == RIGHT_CHEV || tmp->token == DOUBLE_R_CHEV)
			fd_out_redir(tmp, new);
		else if (tmp->token == LEFT_CHEV)
			fd_in_redir(tmp, new, 0);
		else if (tmp->token == DOUBLE_L_CHEV)
		{
			nb_heredoc -= 1;
			fd_in_redir(tmp, new, nb_heredoc);
		}
		tmp = tmp->next;
	}
}

int	ft_count_redir(t_lex *args)
{
	int		nb_red;
	t_lex	*tmp;

	nb_red = 0;
	tmp = args;
	while (tmp)
	{
		if (tmp->token == RIGHT_CHEV
			|| tmp->token == DOUBLE_R_CHEV
			|| tmp->token == LEFT_CHEV
			|| tmp->token == DOUBLE_L_CHEV)
			nb_red++;
		tmp = tmp->next;
	}
	return (nb_red);
}
