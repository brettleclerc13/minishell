/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscore_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:05:48 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/11 10:18:33 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*retrieve_last_cmd(t_serie *serie, int start)
{
	char	*last_cmd;
	t_serie	*tmp_serie;
	int		i;

	i = -1;
	tmp_serie = serie;
	last_cmd = NULL;
	while (tmp_serie->cmd[++i] && !start)
	{
		if (!tmp_serie->cmd[i + 1])
		{
			if (!ft_strncmp(tmp_serie->cmd[i], "env", 4))
				last_cmd = ft_strdup("/usr/bin/env");
			else
				last_cmd = ft_strdup(tmp_serie->cmd[i]);
		}
	}
	return (last_cmd);
}

void	update_underscore(t_serie *serie, t_struct *mshell, int start)
{
	char	*last_cmd;
	t_var	var;

	last_cmd = retrieve_last_cmd(serie, start);
	ft_create_var("_", &var);
	if (!ft_varcmp(var.var, mshell->envp))
	{
		free(var.var);
		var.var = ft_varjoin("_=", last_cmd);
		mshell->envp = add_env_str(var.var, mshell->envp);
	}
	else
		update_env(&var, last_cmd, mshell, false);
	free(var.var);
	free(last_cmd);
}
