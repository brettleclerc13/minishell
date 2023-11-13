/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:32:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/13 11:0:20 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	basic_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_var = 130;
}

static void	basic_sigquit(int signal)
{
	if (signal != SIGQUIT)
		return ;
	rl_on_new_line();
	rl_redisplay();
	g_var = 131;
}

static void	heredoc_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_var = 1;
	exit(1);
}

void    signals_types(char *input, bool isheredoc)
{
	if (!input)
	{
		// printf("pid du processus : %d\n", getpid());
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(127);
	}
	if (isheredoc == true)
		signal(SIGINT, heredoc_sigint); // Ctrl + C for heredoc
	else
		signal(SIGINT, basic_sigint); // Ctrl + C
    signal(SIGQUIT, basic_sigquit); // ctrl + "\" same for heredoc
}

void	ft_gvar_result(int process_result)
{
	if (WIFEXITED(process_result))
		g_var = WEXITSTATUS(process_result);
	else if (WIFSIGNALED(process_result))
		g_var = 128 + WTERMSIG(process_result);
	else if (WIFSTOPPED(process_result))
		g_var = 128 + WSTOPSIG(process_result);
}
