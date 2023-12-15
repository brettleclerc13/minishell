/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:39:24 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/14 07:50:38 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_var = 0;

static void	main_execution(char *input, t_struct *mshell)
{
	ft_execute(mshell);
	add_history(input);
	free(input);
}

static void	end_of_file(char *input, t_struct *mshell)
{
	if (!input)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		g_var = 127;
		ft_free_mshell(mshell);
		exit(g_var);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	*mshell;
	char		*input;

	(void)argv;
	mshell = before_loop_init(argc, envp);
	if (!mshell)
		return (1);
	while (1)
	{
		ft_termios(true);
		signals_types();
		input = readline("minishell$ ");
		end_of_file(input, mshell);
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		if (!parsing(input, &mshell) || !mshell->check_valid)
			continue ;
		main_execution(input, mshell);
	}
	return (0);
}
