/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:39:24 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/10 15:38:56 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	

	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			input = readline(COLOR_PROMPT COLOR_RESET"$ ");
			if (input == NULL)
				break ;
			parsing(input, envp);
			add_history(input);
			free(input);
		}
	}
	return (0);
}

// if (ft_strncmp(input, "exit", 5) == 0)
				// ft_exit();
