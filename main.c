/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:39:24 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/13 10:55:37 by ehouot           ###   ########.fr       */
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
			return (g_var);
		if (mshell->check_valid == false)
			continue ;
		ft_execute(mshell);
		add_history(input);
		free(input);
	}
	// ft_arrayfree(mshell->envp);
	// free(mshell);
	return (0);
}
