/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:55:51 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/13 12:35:32 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	one_dollar(void)
{
	ft_putstr_fd("minishell: $: command not found\n", STDOUT_FILENO);
	g_var = 127;
}

char	*get_gvar_value(char *char_dol)
{
	char	*g_var_value;

	g_var_value = ft_strjoin_parser(ft_itoa(g_var), char_dol + 1 ,true);
	return (g_var_value);
}

char	*check_dollar_continue(char **char_dol, char *result, char **envp, int i)
{
	while (char_dol[++i])
	{
		if (!ft_strncmp(char_dol[i], "?", 1))
		{
			if (result == NULL)
				result = get_gvar_value(*char_dol);
			else
				result = ft_strjoin_parser(result, get_gvar_value(*char_dol), true);
		}
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

bool	check_dollar(t_lex **list, char **envp)
{
	char	*result;
	char	**char_dol;
	int		i;

	result = NULL;
	if ((*list)->token != DOLLAR && (*list)->token != STRING && (*list)->token != WORD)
		return (true);
	if ((*list)->content[0] == '$')
		i = -1;
	else
		i = 0;
	char_dol = ft_split((*list)->content, '$');
	if (i == 0)
		result = ft_strdup(char_dol[i]);
	result = check_dollar_continue(char_dol, result, envp, i);
	if (!result)
	{
		ft_arrayfree(char_dol);
		return (false);
	}
	ft_arrayfree(char_dol);
	free((*list)->content);
	(*list)->content = result;
	return (true);
}
