/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:50:54 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/09 15:20:31 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_serie(t_serie *series)
{
	if (!series)
		return ;
	while (series)
	{
		ft_arrayfree(series->cmd);
		if (series->fd_in != STDIN_FILENO && series->fd_in != -1)
			close(series->fd_in);
		if (series->fd_out != STDOUT_FILENO && series->fd_out != -1)
			close(series->fd_out);
		free(series);
		series = series->next;
	}
}

void	ft_free_lex(t_lex *lex)
{
	if (!lex)
		return ;
	while (lex)
	{
		free(lex->content);
		free(lex);
		lex = lex->next;
	}
}

void	ft_free_exit(t_serie *series, t_struct *mshell)
{
	if (series)
		ft_free_serie(series);
	if (mshell)
		ft_free_mshell(mshell);
	g_var = 1;
	exit(g_var);
}

void	ft_free_mshell(t_struct *mshell)
{
	if (!mshell)
		return ;
	if (mshell->envp)
		ft_arrayfree(mshell->envp);
	if (mshell->args)
		ft_free_lex(mshell->args);
	if (mshell->tmp_fd != STDIN_FILENO && mshell->tmp_fd != -1)
		close(mshell->tmp_fd);
	if (mshell->tmp_cwd)
		free(mshell->tmp_cwd);
	free(mshell);
}

void	ft_free_lex_var(t_lex_var *lex_var)
{
	if (!lex_var)
		return ;
	if (lex_var->args)
		ft_arrayfree(lex_var->args);
	if (lex_var->envp)
		ft_arrayfree(lex_var->envp);
	free(lex_var);
}
