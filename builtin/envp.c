/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:01:46 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/15 20:03:39 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_struct *mshell)
{
	int	i;

	i = -1;
	if (!mshell->envp)
	{
		ft_putstr_fd("env: env not found", 2);
		return (1);
	}
	while (mshell->envp[++i])
		printf("%s\n", mshell->envp[i]);
	return (0);
}

int	ft_update_shlvl(t_struct *mshell)
{
	char	*shlvl;

	shlvl = get_env_value("SHLVL=", mshell->envp);
	if (!shlvl)
	{
		ft_putstr_fd("env: Cannot retrieve shlvl in env", 2);
		return (1);
	}
	update_env_value("SHLVL=", ft_itoa(ft_atoi(shlvl) + 1), mshell->envp);
	return (0);	
}

void	update_env_value(char *var, char *new_value, char **envp)
{
	char	*tmp;
	int		i;
	int		varlen;
	
	i = -1;
	varlen = ft_strlen(var);
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], var, varlen))
		{
			tmp = ft_substr(envp[i], 0, varlen);
			free(envp[i]);
			envp[i] = ft_strjoin(tmp, new_value);
			free(tmp);
			return ;
		}
	}
}

char	*get_env_value(char *var, char **envp)
{
	int	i;
	int	strlen;
	
	i = -1;
	strlen = ft_strlen(var);
	while (envp[++i])
		if (!ft_strncmp(envp[i], var, strlen))
			return (envp[i] + strlen);
	return (NULL);
}

char	**add_env_value(char *var, char *value, char **envp)
{
	char	*tmp;
	char	**new_envp;
	
	tmp = ft_strjoin(var, value);
	new_envp = ft_arrayadd(tmp, envp);
	free(tmp);
	ft_arrayfree(envp);
	return (new_envp);
}
