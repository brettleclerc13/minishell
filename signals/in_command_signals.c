/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_command_signals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:37:30 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/23 12:46:40 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	in_command_sigint(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static void	in_command_sigquit(int signal)
{
	if (signal != SIGQUIT)
		return ;
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}

void	sig_in_command(void)
{
	signal(SIGINT, in_command_sigint);
	signal(SIGQUIT, in_command_sigquit);
}
