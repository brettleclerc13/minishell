/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:39:24 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/10 17:28:07 by brettlecler      ###   ########.fr       */
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
		if (parsing(input, &mshell) == false)
			return (g_var); // changer la valeur de g_var dans les retours du parsing
		if (mshell->check_valid == true)
			continue ;
		ft_execute(mshell);
		add_history(input);
		free(input);
	}
	// ft_arrayfree(mshell->envp);
	// free(mshell);
	return (0);
}
