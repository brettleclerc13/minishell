/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:09:12 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/04 21:50:27 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit(1);
}

static void	heredoc_sigquit(int signal)
{
	if (signal != SIGQUIT)
		return ;
}

void	heredoc_signals(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, heredoc_sigquit);
}
