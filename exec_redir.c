/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:29:32 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/09 11:27:18 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_put_redir_error(char *file)
{
    char	*tmp;

	tmp = ft_strjoin("minishell: ", file);
	perror(tmp);
	free(tmp);
	return (-1);
}

static int	check_permissions(char *file, int i)
{
	if (i == 1)
	{
        if (!open(file, O_DIRECTORY))
		{
			printf("file %s, check\n", file);
			return (ft_put_redir_error(file));
		}
	}
	else
	{
		if (access(file, X_OK) == -1)
    	{
			if (errno == EACCES)
				g_var = 126;
			else
				g_var = 1;
			return (ft_put_redir_error(file));
    	}
	}
	return (0);
}

static int fd_in_redir(t_lex *tmp, t_serie **new)
{
    if (tmp->token == LEFT_CHEV)
	{
		tmp = tmp->next;
		if (check_permissions(tmp->content, 0))
			return (-1);
		(*new)->fd_in = open(tmp->content, O_RDWR, 0666);
	}
	if (tmp->token == DOUBLE_L_CHEV)
	{
		tmp = tmp->next;
		(*new)->hd_limiter = tmp->content;
		(*new)->hd = true;
	}
    if ((*new)->fd_in < 0)
	    return (ft_put_redir_error(tmp->content));
	// dup2((*new)->fd_in, STDIN_FILENO);
	// close((*new)->fd_in);
    return (0);
}

static int fd_out_redir(t_lex *tmp, t_serie **new)
{
    if (tmp->token == RIGHT_CHEV)
    {
		tmp = tmp->next;
		if (check_permissions(tmp->content, 1))
			return (-1);
		(*new)->fd_out = open(tmp->content, O_RDWR | O_TRUNC | O_CREAT, 0644);
    }
    if (tmp->token == DOUBLE_R_CHEV)
	{
		tmp = tmp->next;
		if (check_permissions(tmp->content, 1))
			return (-1);
		(*new)->fd_out = open(tmp->content, O_RDWR | O_APPEND | O_CREAT, 0644);
    }
	if ((*new)->fd_out < 0)
		return (ft_put_redir_error(tmp->content));
	// dup2((*new)->fd_out, STDOUT_FILENO);
	// close((*new)->fd_out);
    return (0);
}

int	ft_set_redirections(t_lex *tmp, t_serie **new)
{
    int res_open;

    res_open = 0;
	while (tmp && tmp->token != 4)
	{
		if (tmp->token == RIGHT_CHEV || tmp->token == DOUBLE_R_CHEV)
            res_open = fd_out_redir(tmp, new);
        else if (tmp->token == LEFT_CHEV || tmp->token == DOUBLE_L_CHEV)
            res_open = fd_in_redir(tmp, new);
        if (res_open == -1)
            return (res_open);
		tmp = tmp->next;
	}
    return (res_open);
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
