/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:21:25 by ehouot            #+#    #+#             */
/*   Updated: 2023/06/23 15:26:36 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close(t_varb *var)
{
	close (var->fdhd[0]);
	close (var->fdhd[1]);
	close (var->pfd[0]);
	close (var->tmpfd);
	close (var->outfile);
	close (var->infile);
	close (var->pfd[1]);
}
