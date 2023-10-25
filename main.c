/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:39:24 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/23 08:59:50 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_struct	*mshell;
	char	*input;
	
	(void)argv;
	mshell = before_loop_init(argc, envp);
	if (!mshell)
		return (1);
	while (1)
	{
		input = readline(COLOR_PROMPT COLOR_RESET"$ ");
		if (input == NULL)
			break ;
		if (!parsing(input, mshell))
			return (-1);
		ft_execute(mshell);
		add_history(input);
		free(input);
	}
	return (0);
}

// if (ft_strncmp(input, "exit", 5) == 0)
				// ft_exit();
