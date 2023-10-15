/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:12:37 by ehouot            #+#    #+#             */
/*   Updated: 2023/06/10 15:18:39 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_check_files(int argc, char **argv, t_var *var)
{
	var->fd[0] = open(argv[1], O_RDWR);
	if (var->fd[0] == -1)
		ft_error("infile problem\n");
	if (access(argv[argc - 1], F_OK) == 0)
		unlink(argv[argc - 1]);
	var->fd[1] = open(argv[argc - 1], O_RDWR | O_CREAT, 0666);
	if (var->fd[1] == -1)
		ft_error("outfile problem\n");
}

void	parsing(int argc, char **argv, t_var *var)
{
	if (argc != 5)
		ft_error("wrong number of arguments\n");
	ft_check_files(argc, argv, var);
}
