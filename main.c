/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:39:24 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/15 20:21:07 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_struct	*before_loop_init(int argc, char **envp)
{
	t_struct	*mshell;

	if (argc != 1)
		return (NULL);
	mshell = malloc(sizeof(t_struct));
	if (!mshell)
		return (NULL);
	mshell->envp = ft_arraydup(envp);
	if (ft_update_shlvl(mshell))
		return (NULL);
	return (mshell);
}

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
		mshell->args = parsing(input, envp);
		ft_execute(mshell);
		add_history(input);
		free(input);
	}
	return (0);
}

// if (ft_strncmp(input, "exit", 5) == 0)
				// ft_exit();
