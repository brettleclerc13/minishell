/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:28:04 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/09 20:08:06 by ehouot           ###   ########.fr       */
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

void	set_output(t_serie *serie, int pfd[])
{
	close(pfd[0]);
	if (serie->fd_out_token == END)
		return ;
	if (serie->fd_out == STDOUT_FILENO)
		dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
}

void	set_input(t_serie *serie, int pfd[])
{
	if (serie->fd_out_token == END)
		return ;
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
}
