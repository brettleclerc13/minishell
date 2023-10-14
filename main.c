/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:39:24 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/13 13:22:44 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_struct	mshell;
	char	*input;
	
	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			input = readline(COLOR_PROMPT COLOR_RESET"$ ");
			if (input == NULL)
				break ;
			mshell.envp = ft_arraydup(envp);
			if (ft_update_shlvl(&mshell))
				return (1);
			parsing(input, &mshell);
			add_history(input);
			free(input);
		}
	}
	return (0);
}

// if (ft_strncmp(input, "exit", 5) == 0)
				// ft_exit();
