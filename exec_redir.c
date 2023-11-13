/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:29:32 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/12 07:53:25 by ehouot           ###   ########.fr       */
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

static int	check_permissions_fdin(char *file)
{
	if (access(file, R_OK) == -1)
    {
		if (errno == EACCES)
			g_var = 126;
		else
			g_var = 1;
		return (ft_put_redir_error(file));
    }
	return (0);
}

// static int	check_permissions_fdout(char *file)
// {
//     if (open(file, O_DIRECTORY) == -1)
// 	{
// 		printf("file %s, check\n", file);
// 		return (ft_put_redir_error(file));
// 	}
// 	return (0);
// }

static void	ft_here_doc(int argc, char **argv, t_varb *var)
{
	char	*str;

	if (pipe(var->fdhd) == -1)
		ft_error("here_doc pipe error\n");
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if ((ft_strlen(argv[2]) == ft_strlen(str + 1))
			&& (ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0))
		{
			free(str);
			break ;
		}
		write(var->fdhd[1], str, ft_strlen(str) + 1);
	}
	close(var->fdhd[1]);
	if (access(argv[argc - 1], F_OK) == 0)
		unlink(argv[argc - 1]);
	var->outfile = open(argv[argc - 1], O_RDWR | O_APPEND | O_CREAT, 0666);
	if (var->outfile == -1)
		ft_error("outfile problem\n");
}

static int fd_in_redir(t_lex *tmp, t_serie **new)
{
    if (tmp->token == LEFT_CHEV)
	{
		tmp = tmp->next;
		if (check_permissions_fdin(tmp->content))
			return (-1);
		(*new)->fd_in = open(tmp->content, O_RDWR, 0644);
	}
	if (tmp->token == DOUBLE_L_CHEV)
	{
		tmp = tmp->next;
		// (*new)->hd_limiter = tmp->content;
		// (*new)->hd = true;
		ft_here_doc();
	}
    if ((*new)->fd_in < 0)
	    return (ft_put_redir_error(tmp->content));
    return (0);
}

static int fd_out_redir(t_lex *tmp, t_serie **new)
{
    if (tmp->token == RIGHT_CHEV)
    {
		tmp = tmp->next;
		// if (check_permissions_fdout(tmp->content))
		// 	return (-1);
		(*new)->fd_out = open(tmp->content, O_RDWR | O_TRUNC | O_CREAT, 0644);
    }
    if (tmp->token == DOUBLE_R_CHEV)
	{
		tmp = tmp->next;
		// if (check_permissions_fdout(tmp->content))
		// 	return (-1);
		(*new)->fd_out = open(tmp->content, O_RDWR | O_APPEND | O_CREAT, 0644);
    }
	if ((*new)->fd_out < 0)
		return (ft_put_redir_error(tmp->content));
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
