/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:01:46 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/22 16:20:06 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_env_str(char *arg, char **envp)
{
	char	**new_envp;

	new_envp = ft_arrayadd(arg, envp);
	return (new_envp);
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
			if (!new_value)
				envp[i] = ft_strdup(var);
			else
				envp[i] = ft_strjoin(tmp, new_value);
			free(tmp);
			if (new_value)
				free(new_value);
			return ;
		}
	}
}

void	update_env(t_var *var, char *new_value, t_struct *mshell, bool is_equal)
{
	int	i;
	
	i = -1;
	while (mshell->envp[++i])
	{
		if (!ft_strncmp(mshell->envp[i], var->var, var->varlen))
		{
			if (!ft_strcmp(var->var, var->envp_var))
			{
				free(mshell->envp[i]);
				if (is_equal)
					mshell->envp[i] = ft_varjoin(var->var, new_value);
				else
				{
					if (!new_value)
						mshell->envp[i] = ft_strdup(var->var);
					else
					{
						var->var = ft_strjoin_path(var->var, "=", true);
						mshell->envp[i] = ft_varjoin(var->var, new_value);	
					}
				}
			}
		}
	}
}

char	*get_env_value(char *var, char **envp)
{
	int	i;
	int	varlen;
	
	i = -1;
	varlen = ft_strlen(var);
	while (envp[++i])
		if (!ft_strncmp(envp[i], var, varlen))
			return (envp[i] + varlen);
	return (NULL);
}

char	**add_env_value(char *var, char *value, char **envp)
{
	char	*tmp;
	char	**new_envp;
	
	if (!value)
		tmp = ft_strdup(var);
	else
		tmp = ft_strjoin(var, value);
	new_envp = ft_arrayadd(tmp, envp);
	free(tmp);
	return (new_envp);
}
