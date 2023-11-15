/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:55:51 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/15 20:01:38 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_dollarcount(char *content)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (content[i + 1] == '$')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

static char **ft_dollar_array_continue(t_dollar *dol, char *content)
{
	while (content[dol->i])
	{
		if (content[dol->i] == '$')
		{
			if (dol->start != dol->i)
				dol->array[dol->j++] = ft_substr(content, dol->start, dol->i - dol->start);
			if (content[dol->i + 1] && content[dol->i + 1] == '$')
			{
				dol->array[dol->j] = ft_strdup("`PID'");
				dol->i += 2;
				dol->start = dol->i;
				while(content[dol->i] && content[dol->i] != '$')
					dol->i++;
				if (dol->start != dol->i)
					dol->array[dol->j] = ft_strjoin_dollar(dol->array[dol->j], ft_substr(content, dol->start, dol->i - dol->start), true);
				dol->j++;
				if (content[dol->i] == '$' && !content[dol->i + 1])
					dol->array[dol->j++] = ft_strdup("$");
			}
			else if (content[dol->i + 1] && content[dol->i + 1] != '$')
			{
				dol->i++;
				dol->start = dol->i;
				while (content[dol->i] && content[dol->i] != '$')
					dol->i++;
				dol->array[dol->j++] = ft_substr(content, dol->start, dol->i - dol->start);
			}
			else
				dol->array[dol->j++] = ft_strdup("$");
			dol->start = dol->i;
		}
		if (content[dol->i] != '$' || !content[dol->i + 1])
			dol->i++;
	}
	return(dol->array);
}

static char	**ft_dollar_array(char *content)
{
	t_dollar	dol;

	dol.i = 0;
	dol.j = 0;
	dol.start = 0;
	dol.array = ft_calloc(ft_dollarcount(content) + 2, sizeof(char *));
	if (!dol.array)
	{
		ft_putstr_fd("minishell: malloc: cannot allocate memory\n", 2);
		return (NULL);
	}
	return (ft_dollar_array_continue(&dol, content));
}

static char	*expand_dollar(char **char_dol, char *result, char **envp, int i)
{
	char	*g_var_value;

	g_var_value = NULL;
	while (char_dol[++i])
	{
		if (!ft_strncmp(char_dol[i], "$", 1))
			result = ft_strjoin_dollar(result, "$", true);
		else if (!ft_strncmp(char_dol[i], "?", 1))
		{
			g_var_value = ft_strjoin_dollar(ft_itoa(g_var), char_dol[i] + 1 ,true);
			result = ft_strjoin_dollar(result, g_var_value, true);
			free(g_var_value);
		}
		else if (!ft_strncmp(char_dol[i], "`PID'", 5))
			result = ft_strjoin_dollar(result, char_dol[i], true);
		else if (ft_varcmp(char_dol[i], envp) == true)
		{
			char_dol[i] = ft_strjoin_dollar(char_dol[i], "=", true);
			if (!get_env_value(char_dol[i], envp))
				break ;
			result = ft_strjoin_dollar(result, get_env_value(char_dol[i], envp), true);
		}
		else
			result = ft_strjoin_dollar(result, char_dol[i], true);
	}
	return (result);
}

bool	check_dollar(t_lex **list, char **envp)
{
	char	*result;
	char	**char_dol;
	int		i;

	result = NULL;
	i = -1;
	if ((*list)->token != DOLLAR && (*list)->token != STRING && (*list)->token != WORD)
		return (true);
	if (ft_dollarcount((*list)->content) == 0)
		return (true);
	char_dol = ft_dollar_array((*list)->content);
	if (!char_dol)
		return (false);
	result = expand_dollar(char_dol, result, envp, i);
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


	// dol->i = -1;
	// while (dol->array[++dol->i])
	// 	printf("%s\n", dol->array[dol->i]);