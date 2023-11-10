/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:28:04 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/10 15:01:56 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_waitpid(t_serie *series)
{
	t_serie	*tmp;
	int		return_result;

	tmp = series;
	return_result = 0;
	if (tmp->pid == -5)
		return ;
	while (tmp)
	{
		waitpid(tmp->pid, &return_result, 0);
		tmp = tmp->next;
	}
	ft_exit_result(return_result);
}

void	set_child_input(t_serie *serie, int pfd[], int previous_fd, int start)
{
	if (serie->fd_in != STDIN_FILENO && serie->fd_in != -1)
	{
		dup2(serie->fd_in, STDIN_FILENO);
		close(serie->fd_in);
		close(pfd[0]);
		if (previous_fd)
			close(previous_fd);
	}
	else if ((serie->fd_in == STDIN_FILENO || serie->fd_in == -1) && start != 0)
	{
		dup2(previous_fd, STDIN_FILENO);
		close(previous_fd);
		close(pfd[0]);
	}
	else
		close(pfd[0]);
}
void	set_child_output(t_serie *serie, int pfd[])
{
	if (serie->fd_out != STDOUT_FILENO && serie->fd_out != -1)
	{
		if (serie->fd_out_token != END)
		{
			dup2(serie->fd_out, pfd[1]);
			close(serie->fd_out);
			dup2(pfd[1], STDOUT_FILENO);
			close(pfd[1]);
		}
		else
		{
			dup2(serie->fd_out, STDOUT_FILENO);
			close(serie->fd_out);
			close(pfd[1]);
		}
	}
	else if ((serie->fd_out == STDOUT_FILENO || serie->fd_out == -1) && serie->fd_out_token != END)
	{
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	}
	else
		close(pfd[1]);
}
void	set_parent_io(int pfd[], t_struct *mshell)
{
	close(pfd[1]);
	dup2(pfd[0], mshell->tmp_fd);
	close(pfd[0]);
}

