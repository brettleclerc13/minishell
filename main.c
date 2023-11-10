/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:39:24 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/09 18:38:39 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int g_var = 0;

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
		input = readline("minishell$ ");
		signals_types(input, false);
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		parsing(input, &mshell);
		if (mshell->check_valid == true)
			continue ;
		ft_execute(mshell);
		// ft_free_mshell(mshell);
		add_history(input);
		free(input);
	}
	return (0);
}

// if (ft_strncmp(input, "exit", 5) == 0)
				// ft_exit();
