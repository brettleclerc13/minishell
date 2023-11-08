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

// static char	**ft_convert_to_array(t_lex *args)
// {
// 	t_lex	*tmp;
// 	char	**array;
// 	int		struct_len;

// 	struct_len = 0;
// 	tmp = args;
// 	while (tmp)
// 	{
// 		struct_len++;
// 		tmp = tmp->next;
// 	}
// 	array = ft_calloc(struct_len + 1, sizeof(char *));
// 	if (!array)
// 		return (NULL);
// 	tmp = args;
// 	struct_len = 0;
// 	while (tmp)
// 	{
// 		array[struct_len++] = ft_strdup(tmp->content);
// 		tmp = tmp->next;
// 	}
// 	return (array);
// }

int	ft_count_pipe(t_struct *mshell)
{
	t_lex	*args;
	int		pipe_count;

	pipe_count = 0;
	args = mshell->args;
	while (args)
	{
		if (args->token == 4)
			pipe_count++;
		args = args->next;
	}
	return(pipe_count);
}

// char	**ft_lex_array(t_lex *args)
// {
// 	t_lex	*tmp;
// 	char	**array;
// 	int		struct_len;

// 	struct_len = 0;
// 	tmp = args;
// 	while (tmp)
// 	{
// 		struct_len++;
// 		tmp = tmp->next;
// 	}
// 	array = ft_calloc(struct_len + 1, sizeof(char *));
// 	if (!array)
// 		return (NULL);
// 	tmp = args;
// 	struct_len = 0;
// 	while (tmp)
// 	{
// 		array[struct_len++] = ft_strdup(tmp->content);
// 		tmp = tmp->next;
// 	}
// 	return (array);
// }

int	ft_pipe_execution(t_serie *serie, t_struct *mshell)
{
	int 	pfd[2];
	pid_t	pid;

	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		dup2(serie->fd_in, STDIN_FILENO);
		dup2(serie->fd_out, pfd[1]);
		// close(serie->fd_in);
		// close(serie->fd_out);
		if (serie->cmd_token == FUNCTION)
			g_var = builtin_main(serie->cmd, mshell);
		else
			g_var = ft_execve(serie->cmd, mshell->envp);
	}
	waitpid(0, NULL, WNOHANG);
	return (pfd[0]);
}

void	ft_execute_serie(t_serie *serie, t_struct *mshell)
{
	int		pipe_fd;
	pid_t	pid;

	pipe_fd = 0;
	if (serie->fd_out_token == PIPE)
		pipe_fd = ft_pipe_execution(serie, mshell);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (!pipe_fd)
				dup2(serie->fd_in, STDIN_FILENO);
			else
				dup2(serie->fd_in, pipe_fd);
			dup2(serie->fd_out, STDOUT_FILENO);
			// close(serie->fd_in);
			// close(serie->fd_out);
			if (serie->cmd_token == FUNCTION)
				g_var = builtin_main(serie->cmd, mshell);
			else
				g_var = ft_execve(serie->cmd, mshell->envp);
		}
		waitpid(0, NULL, WNOHANG);
	}
}

void	ft_execute(t_struct *mshell)
{
	t_serie	*series;

	series = NULL;
	serie_creation(mshell, &series);
	while (series)
	{
		ft_execute_serie(series, mshell);
		series = series->next;
	}
}
