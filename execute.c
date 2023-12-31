/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:16:19 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/15 10:10:15 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_io(int original_io[])
{
	dup2(original_io[0], STDIN_FILENO);
	dup2(original_io[1], STDOUT_FILENO);
	close(original_io[0]);
	close(original_io[1]);
}

pid_t	ft_execute_error(char *message)
{
	ft_putstr_fd(message, 2);
	g_var = 1;
	return (-1);
}

// static void	random_function(t_struct *mshell)
// {
// 	read_file(mshell->pipe_fd, "INSIDE RANDOM FUNCTION");
// }

pid_t	ft_fork_execution(t_serie *serie, t_struct *mshell, int start)
{
	int		pfd[2];
	pid_t	pid;

	if (serie->first_arg_token == SKIP && serie->fd_out_token == END)
		return (-1);
	if (pipe(pfd) == -1)
		ft_execute_error("minishell: broken pipe\n");
	pid = fork();
	if (pid < 0)
		ft_execute_error("minishell: fork: resource temporarily unavailable\n");
	if (pid == 0)
	{
		child_input(serie, pfd, start, mshell);
		child_output(serie, pfd);
		if ((serie->fd_in == -1 || serie->fd_out == -1))
			exit(g_var);
		if (builtin_checker(serie->cmd[0]))
			g_var = builtin_main(serie->cmd, mshell, 0);
		else
			g_var = ft_execve(serie, serie->cmd, mshell->envp);
		exit (g_var);
	}
	set_parent_io(pfd, mshell);
	return (pid);
}

pid_t	ft_execute_serie(t_serie *serie, int start, t_struct *mshell)
{
	if (!serie->cmd[0] && serie->fd_out_token == END)
		return (0);
	update_underscore(serie, mshell, start);
	if (serie->fd_out_token == END && start == 0 \
	&& builtin_checker(serie->cmd[0]))
	{
		if (serie->fd_in == -1 || serie->fd_out == -1 \
			|| serie->first_arg_token == SKIP)
			return (-5);
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
		g_var = builtin_main(serie->cmd, mshell, 1);
		return (-5);
	}
	sig_in_command();
	ft_termios(false);
	return (ft_fork_execution(serie, mshell, start));
}

void	ft_execute(t_struct *mshell)
{
	int		start;
	t_serie	*tmp_series;
	t_serie	*series;
	int		original_io[2];

	series = NULL;
	start = 0;
	if (!serie_creation(mshell->args, &series))
		ft_free_exit(series, mshell);
	ft_free_lex(mshell->args);
	tmp_series = series;
	original_io[0] = dup(STDIN_FILENO);
	original_io[1] = dup(STDOUT_FILENO);
	while (tmp_series)
	{
		tmp_series->pid = ft_execute_serie(tmp_series, start++, mshell);
		tmp_series = tmp_series->next;
	}
	reset_io(original_io);
	tmp_series = series;
	ft_waitpid(tmp_series);
	ft_free_serie(series);
}

// ft_free_mshell(mshell);
// system("leaks minishell");
// exit(0);