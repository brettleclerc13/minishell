/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_manipulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:11:30 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/15 19:58:41 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char *line)
{
	char	*skip_var;
	
	skip_var = NULL;
	if (!ft_strchr(line, '='))
		return(ft_strdup(line));
	else
	{
		skip_var = ft_strchr(line, '=');
		return(ft_substr(line, 0, ft_strlen(line) - ft_strlen(skip_var)));
	}
}

int	ft_varcmp_struct(t_var *var, char **envp)
{
	int		i;

	i = 0;
	while (envp[++i])
	{
		var->envp_var = get_env_var(envp[i]);
		if (!ft_strcmp(var->var, var->envp_var))
			return (1);
		free(var->envp_var);
	}
	return (0);
}

void	ft_create_var(char *arg, t_var *var)
{
	char	*skip_var;

	var->envp_var = NULL;
	if (!ft_strchr(arg, '='))
	{
		var->var = ft_strdup(arg);
		var->symbol = '0';
		var->varlen = ft_strlen(var->var);
		return ;
	}
	else if (ft_strnstr(arg, "+=", ft_strlen(arg)))
	{
		skip_var = ft_strchr(arg, '+');
		var->symbol = '+';
	}
	else
	{
		skip_var = ft_strchr(arg, '=');
		var->symbol = '=';
	}
	var->varlen = ft_strlen(arg) - ft_strlen(skip_var);
	var->var = ft_substr(arg, 0, var->varlen);
}

bool	ft_varcmp(char *var, char **envp)
{
	char    *envp_var;
	int      i;

    i = -1;
    while (envp[++i])
    {
        envp_var = get_env_var(envp[i]);
        if (!ft_strcmp(var, envp_var))
        {
            free(envp_var);
            return (true);
        }
        free(envp_var);
    }
    return (false);
}

char	*ft_varjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	j = 0;
	i = -1;
	if (!s1)
		return (NULL);
	dest = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	while (++i < ft_strlen(s1))
		dest[i] = s1[i];
	while (s2 && j < ft_strlen(s2))
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}
