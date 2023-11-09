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

void	set_output(t_serie *serie, int pfd[])
{
	if (serie->fd_out_token == END)
		return ;
	close(pfd[0]);
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
	return (pfd[0]);
}

pid_t	ft_execute_serie(t_serie *serie, t_struct *mshell)
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
	if (serie->fd_out_token == END && serie->cmd_token == FUNCTION)
	{
		g_var = builtin_main(serie->cmd, mshell);
		return (-5);
	}
	else
		return (ft_fork_execution(serie, mshell));
}

static void	ft_waitpid(t_serie *series)
{
	t_serie	*tmp;
	//int		return_result;

	tmp = series;
	//return_result = 0;
	if (tmp->pid == -5)
		return ;
	while (tmp)
	{
		waitpid(tmp->pid, &g_var, 0);
		tmp = tmp->next;
	}
	//ft_exit_result(return_result);
}

void	ft_execute(t_struct *mshell)
{
	t_serie *tmp;
	t_serie	*series;
	int		original_io[2];

	series = NULL;
	serie_creation(mshell, &series);
	tmp = series;
	original_io[0] = dup(STDIN_FILENO);
	original_io[1] = dup(STDOUT_FILENO);
	while (series)
	{
		series->pid = ft_execute_serie(series, mshell);
		series = series->next;
	}
	dup2(original_io[0], STDIN_FILENO);
	dup2(original_io[1], STDOUT_FILENO);
	close(original_io[0]);
	close(original_io[1]);
	ft_waitpid(tmp);
}

// ft_putstr_fd("check\n", 1);