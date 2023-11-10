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

pid_t	ft_fork_execution(t_serie *serie, t_struct *mshell, int start)
{
	int 	pfd[2];
	pid_t	pid;

	if (pipe(pfd) == -1)
		ft_error("pipe error\n");
	pid = fork();
	if (pipe < 0)
		ft_error("fork problem\n");
	if (pid == 0)
	{
		set_child_input(serie, pfd, mshell->tmp_fd, start);
		set_child_output(serie, pfd);
		if (serie->cmd_token == FUNCTION)
			g_var = builtin_main(serie->cmd, mshell);
		else
			g_var = ft_execve(serie->cmd, mshell->envp);
		exit (1);					//to be modified - set sig & free before exit
	}
	set_parent_io(pfd, mshell);
	return (pid);
}

pid_t	ft_execute_serie(t_serie *serie, int start, t_struct *mshell)
{
	if (serie->fd_out_token == END && start == 0 && serie->cmd_token == FUNCTION)
	{
		if (serie->fd_in != STDIN_FILENO && serie->fd_in != -1)
		{
			dup2(serie->fd_in, STDIN_FILENO);
			close(serie->fd_in);
		}
		if (serie->fd_out != STDOUT_FILENO && serie->fd_out != -1)
		{
			dup2(serie->fd_out, STDOUT_FILENO);
			close(serie->fd_out);
		}
		g_var = builtin_main(serie->cmd, mshell);
		return (-5);
	}
	else
		return (ft_fork_execution(serie, mshell, start));
}


void	ft_execute(t_struct *mshell)
{
	int		i;
	t_serie *tmp_series;
	t_serie	*series;
	int		original_io[2];

	series = NULL;
	i = 0;
	serie_creation(mshell->args, &series);
	ft_free_lex(mshell->args);
	print_lst_serie(series);
	tmp_series = series;
	original_io[0] = dup(STDIN_FILENO);
	original_io[1] = dup(STDOUT_FILENO);
	while (tmp_series)
	{
		tmp_series->pid = ft_execute_serie(tmp_series, i, mshell);
		i++;
		tmp_series = tmp_series->next;
	}
	dup2(original_io[0], STDIN_FILENO);
	dup2(original_io[1], STDOUT_FILENO);
	close(original_io[0]);
	close(original_io[1]);
	tmp_series = series;
	ft_waitpid(tmp_series);
	ft_free_serie(series);
	if (mshell->tmp_fd != STDIN_FILENO && mshell->tmp_fd != -1)
		close(mshell->tmp_fd);
}

// ft_putstr_fd("check\n", 1);