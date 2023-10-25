/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:55:51 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/25 17:01:45 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
    int    i;

    i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            break ;
        i++;
    }
    return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

char    *get_env_var(char *line)
{
    char    *skip_var;

    skip_var = NULL;
    if (!ft_strchr(line, '='))
        return(ft_strdup(line));
    else
    {
        skip_var = ft_strchr(line, '=');
        return(ft_substr(line, 0, ft_strlen(line) - ft_strlen(skip_var)));
    }
}

bool	ft_varcmp_vtwo(char *var, char **envp)
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

char	*check_dollar_continue(char **char_dol, char *result, char **envp, int i)
{
	while (char_dol[++i])
	{
		if (ft_varcmp_vtwo(char_dol[i], envp) == true)
		{
			char_dol[i] = ft_strjoin_parser(char_dol[i], "=", true);
			if (!get_env_value(char_dol[i], envp))
				break ;
			if (result == NULL)
				result = ft_strdup(get_env_value(char_dol[i], envp));
			else
				result = ft_strjoin_parser(result, get_env_value(char_dol[i], envp), true);
		}
	}
	return (result);
}

void	check_dollar(t_lex **list, char **envp)
{
	char	*result;
	char	**char_dol;
	int		i;

	result = NULL;
	if ((*list)->token != DOLLAR && (*list)->token != STRING && (*list)->token != WORD)
		return ;
	if ((*list)->content[0] == '$')
		i = -1;
	else
		i = 0;
	char_dol = ft_split((*list)->content, '$');
	if (i == 0)
		result = ft_strdup(char_dol[i]);
	result = check_dollar_continue(char_dol, result, envp, i);
	ft_arrayfree(char_dol);
	free((*list)->content);
	(*list)->content = result;
}
