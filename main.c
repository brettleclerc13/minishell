/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:39:24 by ehouot            #+#    #+#             */
/*   Updated: 2023/06/27 13:46:51 by ehouot           ###   ########.fr       */
/*   Updated: 2023/06/27 15:34:03 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argv;
	(void)envp;
	if (argc == 1)
	{
		while (1)
		{
			input = readline(COLOR_PROMPT COLOR_RESET"$ ");
			if (input == NULL)
				break ;
			parsing(input);
			add_history(input);
			free(input);
		}
	}
	return (0);
}

// if (ft_strncmp(input, "exit", 5) == 0)
				// ft_exit();
