/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:01:46 by brettlecler       #+#    #+#             */
/*   Updated: 2023/10/03 10:54:55 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_arrayfree(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

char	**ft_arrayadd(char *newline, char **array)
{
	char **tmp;
	int	i;

	if (!array)
		return (NULL);
	i = -1;
	tmp = ft_calloc(ft_arraylen(array) + 2, sizeof(char *));
	if (!tmp)
		return (NULL);
	while (array[++i])
		tmp[i] = ft_strdup(array[i]);
	tmp[i] = ft_strdup(newline);
	return (tmp);
}

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i] && array)
		i++;
	return (i);
}

char	**ft_arraydup(char **array)
{
	char **tmp;
	int	i;

	i = -1;
	tmp = ft_calloc(ft_arraylen(array) + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	while (array[++i] && array)
		tmp[i] = ft_strdup(array[i]);
	return (tmp);
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
