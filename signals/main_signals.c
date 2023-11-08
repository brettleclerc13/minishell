/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:32:36 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/07 09:58:13 by ehouot           ###   ########.fr       */
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
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(127);
	}
	if (isheredoc == true)
		signal(SIGINT, heredoc_sigint); // Ctrl + C for heredoc
	else
		signal(SIGINT, basic_sigint); // Ctrl + C
    signal(SIGQUIT, basic_sigquit); // ctrl + "\" same for heredoc
}
