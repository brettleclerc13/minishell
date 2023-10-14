/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 09:30:51 by ehouot            #+#    #+#             */
/*   Updated: 2023/06/23 16:53:03 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_pipe_to_pipe(char *argv, char **envp, t_varb *var)
{
	if (pipe(var->pfd) == -1)
		ft_error("pipe error\n");
	var->child = fork();
	if (var->child < 0)
		ft_error("fork problem\n");
	if (var->child == 0)
	{
		if (var->here_doc == 1)
		{
			close (var->fdhd[0]);
			close (var->fdhd[1]);
		}
		else
			close (var->outfile);
		close (var->pfd[0]);
		close (var->infile);
		dup2 (var->tmpfd, STDIN_FILENO);
		dup2 (var->pfd[1], STDOUT_FILENO);
		close (var->tmpfd);
		close (var->pfd[1]);
		exec_cmd_bonus (argv, envp, var);
	}
}

static void	ft_read_to_pipe(char *argv, char **envp, t_varb *var)
{
	var->child = fork();
	if (var->child < 0)
		ft_error("fork problem\n");
	if (var->child == 0 && var->here_doc == 0)
	{
		close (var->pfd[0]);
		close (var->outfile);
		dup2(var->infile, STDIN_FILENO);
		dup2(var->pfd[1], STDOUT_FILENO);
		close (var->infile);
		close (var->pfd[1]);
		exec_cmd_bonus(argv, envp, var);
	}
	else if (var->child == 0 && var->here_doc == 1)
	{
		close (var->fdhd[1]);
		close (var->pfd[0]);
		dup2(var->fdhd[0], STDIN_FILENO);
		dup2(var->pfd[1], STDOUT_FILENO);
		close (var->fdhd[0]);
		close (var->pfd[1]);
		exec_cmd_bonus(argv, envp, var);
	}
	close (var->fdhd[0]);
	close (var->pfd[1]);
}

static void	ft_pipe_to_write(char *argv, char **envp, t_varb *var)
{
	var->child = fork();
	if (var->child < 0)
		ft_error("fork problem\n");
	if (var->child == 0 && var->here_doc == 1)
	{
		close (var->fdhd[0]);
		close (var->infile);
		close (var->pfd[1]);
		dup2(var->tmpfd, STDIN_FILENO);
		dup2(var->outfile, STDOUT_FILENO);
		close (var->fdhd[0]);
		close (var->tmpfd);
		exec_cmd_bonus(argv, envp, var);
	}
	else if (var->child == 0 && var->here_doc == 0)
	{
		close (var->pfd[1]);
		close (var->infile);
		dup2(var->tmpfd, STDIN_FILENO);
		dup2(var->outfile, STDOUT_FILENO);
		close (var->outfile);
		close (var->tmpfd);
		exec_cmd_bonus(argv, envp, var);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_varb	var;
	int		i;

	i = 2;
	var.here_doc = parsing_bonus(argc, argv, &var);
	if (var.here_doc == 2)
		ft_mandatory(argv, envp, &var);
	if (pipe(var.pfd) == -1)
		ft_error("pipe error\n");
	if (var.here_doc == 1)
		i++;
	ft_read_to_pipe(argv[i], envp, &var);
	var.tmpfd = var.pfd[0];
	close(var.pfd[1]);
	while (++i < argc - 2)
	{
		ft_pipe_to_pipe(argv[i], envp, &var);
		close (var.tmpfd);
		var.tmpfd = dup(var.pfd[0]);
		close (var.pfd[1]);
	}
	ft_pipe_to_write(argv[argc - 2], envp, &var);
	ft_close(&var);
	waitpid(0, NULL, 0);
	return (EXIT_SUCCESS);
}
