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

void	signals_types(void)
{
	signal(SIGINT, basic_sigint);
	signal(SIGQUIT, basic_sigquit);
}
