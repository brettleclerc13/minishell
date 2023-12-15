/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:28:04 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/15 08:18:57 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int file, char *source)
{
	if (!close(file))
		;
	else
		printf("close error, %s\n", source);
}

void	ft_waitpid(t_serie *series)
{
	t_serie	*tmp;
	int		return_result;
	int		last_cmd_status;

	tmp = ft_lstlast_serie(series);
	return_result = 0;
	last_cmd_status = return_result;
	if (tmp->pid == -5 || tmp->pid == -1)
		return ;
	while (tmp)
	{
		waitpid(tmp->pid, &return_result, 0);
		if (!tmp->next)
			last_cmd_status = return_result;
		tmp = tmp->prev;
	}
	ft_gvar_result(last_cmd_status);
}

void	child_input(t_serie *serie, int pfd[], int start, t_struct *mshell)
{
	if (serie->fd_in != STDIN_FILENO && serie->fd_in != -1)
	{
		//printf("in_child 1, start == %d\n", start);
		dup2(serie->fd_in, STDIN_FILENO);
		ft_close(serie->fd_in, "in_child");
		ft_close(pfd[0], "in_child");
	}
	else if (serie->fd_in == STDIN_FILENO && start != 0)
	{
		//printf("in_child 2, start == %d\n", start);
		dup2(mshell->pipe_fd, STDIN_FILENO);
		ft_close(mshell->pipe_fd, "in_child 2");
		ft_close(pfd[0], "in_child 2");
	}
	else
	{
		//printf("in_child 3, start == %d\n", start);
		if (mshell->pipe_fd != STDIN_FILENO && mshell->pipe_fd != -1)
			ft_close(mshell->pipe_fd, "in_child");
		ft_close(pfd[0], "in_child");
	}
}

void	child_output(t_serie *serie, int pfd[])
{
	if (serie->fd_out != STDOUT_FILENO && serie->fd_out != -1)
	{
		if (serie->fd_out_token != END)
		{
			//printf("out_child 1, fd_out_tok == %d\n", serie->fd_out_token);
			dup2(serie->fd_out, pfd[1]);
			ft_close(serie->fd_out, "out_child");
			dup2(pfd[1], STDOUT_FILENO);
			ft_close(pfd[1], "out_child");
		}
		else
		{
			//printf("out_child 2, fd_out_tok == %d\n", serie->fd_out_token);
			dup2(serie->fd_out, STDOUT_FILENO);
			ft_close(serie->fd_out, "out_child");
			ft_close(pfd[1], "out_child");
		}
	}
	else if (serie->fd_out == STDOUT_FILENO && serie->fd_out_token != END)
	{
		//printf("out_child 3, fd_out_tok == %d\n", serie->fd_out_token);
		dup2(pfd[1], STDOUT_FILENO);
		ft_close(pfd[1], "out_child");
	}
	else
	{
		//printf("out_child 4, fd_out_tok == %d\n", serie->fd_out_token);
		ft_close(pfd[1], "out_child 4");
	}
}

void	set_parent_io(int pfd[], t_struct *mshell)
{
	ft_close(pfd[1], "parent pfd1");
	if (mshell->pipe_fd != STDIN_FILENO && mshell->pipe_fd != -1)
		close(mshell->pipe_fd);
	mshell->pipe_fd = dup(pfd[0]);
	ft_close(pfd[0], "parent pfd0");
}
