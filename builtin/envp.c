/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:01:46 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/23 10:37:02 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_env_str(char *arg, char **envp)
{
	char	**new_envp;

	new_envp = ft_arrayadd(arg, envp);
	ft_arrayfree(envp);
	return (new_envp);
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

void	update_env(t_var *var, char *new_value, t_struct *mshell)
{
	int		i;
	
	i = -1;
	while (mshell->envp[++i])
	{
		if (!ft_strncmp(mshell->envp[i], var->var, var->varlen))
		{
			if (!ft_strcmp(var->var, var->envp_var))
			{
				free(mshell->envp[i]);
				mshell->envp[i] = ft_varjoin(var->var, new_value);
				return ;
			}
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
