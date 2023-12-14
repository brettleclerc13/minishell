/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:28:04 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/12 13:09:05 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		waitpid(tmp->pid, &return_result, 0);	//WUNTRACED
		printf("check waitpid\n");
		if (!tmp->next)
			last_cmd_status = return_result;
		tmp = tmp->prev;
	}
	ft_gvar_result(last_cmd_status);
}

void	child_input(t_serie *serie, int pfd[], int previous_fd, int start)
{
	if (serie->fd_in != STDIN_FILENO && serie->fd_in != -1)
	{
		printf("in_child 1, start == %d\n", start);
		dup2(serie->fd_in, STDIN_FILENO);
		close(serie->fd_in);
		close(pfd[0]);
		if (previous_fd != STDIN_FILENO && previous_fd != -1)
			close(previous_fd);
	}
	else if (serie->fd_in == STDIN_FILENO && start != 0)
	{
		dup2(previous_fd, STDIN_FILENO);
		close(previous_fd);
		close(pfd[0]);
		printf("in_child 2, start == %d\n", start);
	}
	else
	{
		printf("in_child 3, start == %d\n", start);
		close(pfd[0]);
	}
}

void	child_output(t_serie *serie, int pfd[])
{
	if (serie->fd_out != STDOUT_FILENO && serie->fd_out != -1)
	{
		if (serie->fd_out_token != END)
		{
			printf("out_child 1, fd_out_tok == %d\n", serie->fd_out_token);
			dup2(serie->fd_out, pfd[1]);
			close(serie->fd_out);
			dup2(pfd[1], STDOUT_FILENO);
			close(pfd[1]);
		}
		else
		{
			printf("out_child 2, fd_out_tok == %d\n", serie->fd_out_token);
			dup2(serie->fd_out, STDOUT_FILENO);
			close(serie->fd_out);
			close(pfd[1]);
		}
	}
	else if (serie->fd_out == STDOUT_FILENO && serie->fd_out_token != END)
	{
		printf("out_child 3, fd_out_tok == %d\n", serie->fd_out_token);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	}
	else
	{
		printf("out_child 4, fd_out_tok == %d\n", serie->fd_out_token);
		close(pfd[1]);
	}
}

void	set_parent_io(int pfd[], t_struct *mshell)
{
	close(pfd[1]);
	if (mshell->tmp_fd != STDIN_FILENO && mshell->tmp_fd != -1)
		close (mshell->tmp_fd);
	mshell->tmp_fd = dup(pfd[0]);
	close(pfd[0]);
	printf("check parent_io\n");
}
