/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:39:24 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/29 14:46:32 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_var = 0;

void	end_of_file(char *input)
{
	if (!input)
	{
		free(input);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		g_var = 127;
		exit(127);
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
		end_of_file(input);
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		if (parsing(input, &mshell) == false)
			continue ;
		if (mshell->check_valid == false)
			continue ;
		ft_execute(mshell);
		add_history(input);
		free(input);
	}
	return (0);
}

	// ft_arrayfree(mshell->envp);
	// free(mshell);