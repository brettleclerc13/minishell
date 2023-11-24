/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_results.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:26:46 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/23 17:55:47 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_termios(bool set)
{
    struct termios	termios;
	tcgetattr(STDIN_FILENO, &termios);
	if (set == true)
		termios.c_lflag &= ~ECHOCTL;
	else
		termios.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
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
