/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:16:19 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/08 19:49:220 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	ft_fork_execution(t_serie *serie, t_struct *mshell)
{
	int 	pfd[2];
	pid_t	pid;

	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		set_output(serie, pfd);
		if (serie->cmd_token == FUNCTION)
			g_var = builtin_main(serie->cmd, mshell);
		else
			g_var = ft_execve(serie->cmd, mshell->envp);
	}
	set_input(serie, pfd);
	return (pfd);
}

pid_t	ft_execute_serie(t_serie *serie, int start, t_struct *mshell)
{
	if (serie->fd_in != STDIN_FILENO)
	{
		dup2(serie->fd_in, STDIN_FILENO);
		close(serie->fd_in);
	}
	if (serie->fd_out != STDOUT_FILENO)
	{
		dup2(serie->fd_out, STDOUT_FILENO);
		close(serie->fd_out);
	}
	if (serie->fd_out_token == END && start == 0 && serie->cmd_token == FUNCTION)
	{
		g_var = builtin_main(serie->cmd, mshell);
		return (-5);
	}
	else
		return (ft_fork_execution(serie, mshell));
}


void	ft_execute(t_struct *mshell)
{
	int		i;
	t_serie *tmp;
	t_serie	*series;
	int		original_io[2];

	series = NULL;
	i = 0;
	serie_creation(mshell, &series);
	tmp = series;
	original_io[0] = dup(STDIN_FILENO);
	original_io[1] = dup(STDOUT_FILENO);
	while (series)
	{
		series->pid = ft_execute_serie(series, i, mshell);
		i++;
		series = series->next;
	}
	dup2(original_io[0], STDIN_FILENO);
	dup2(original_io[1], STDOUT_FILENO);
	close(original_io[0]);
	close(original_io[1]);
	ft_waitpid(tmp);
}

// ft_putstr_fd("check\n", 1);