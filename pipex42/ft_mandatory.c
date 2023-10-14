/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandatory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:27:54 by ehouot            #+#    #+#             */
/*   Updated: 2023/06/23 16:45:14 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_read_to_pipe_bonus(char **argv, char **envp, t_varb *var)
{
	var->child = fork();
	if (var->child < 0)
		ft_error("fork problem\n");
	else if (var->child == 0)
	{
		close (var->outfile);
		close (var->pfd[0]);
		dup2(var->infile, STDIN_FILENO);
		dup2(var->pfd[1], STDOUT_FILENO);
		close (var->infile);
		close (var->pfd[1]);
		exec_cmd_bonus(argv[2], envp, var);
	}
}

static void	ft_pipe_to_write_bonus(char **argv, char **envp, t_varb *var)
{
	var->child = fork();
	if (var->child < 0)
		ft_error("fork problem\n");
	else if (var->child == 0)
	{
		close (var->infile);
		close (var->pfd[1]);
		dup2(var->outfile, STDOUT_FILENO);
		dup2(var->pfd[0], STDIN_FILENO);
		close (var->outfile);
		close (var->pfd[0]);
		exec_cmd_bonus(argv[3], envp, var);
	}
}

int	ft_mandatory(char **argv, char **envp, t_varb *var)
{
	if (pipe(var->pfd) == -1)
		ft_error("pipe error\n");
	ft_read_to_pipe_bonus(argv, envp, var);
	ft_pipe_to_write_bonus(argv, envp, var);
	close (var->infile);
	close (var->outfile);
	close (var->pfd[0]);
	close (var->pfd[1]);
	waitpid(-1, NULL, 0);
	return (EXIT_SUCCESS);
}
