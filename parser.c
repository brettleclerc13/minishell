/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:17:25 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/09 15:27:57 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_env_value(char *var, char **envp)
// {
// 	int	i;
// 	int	str_len;

// 	i = -1;
// 	str_len = ft_strlen(var);
// 	while (envp[++i])
// 		if (!ft_strncmp(envp[i], var, str_len))
// 			return (envp[i] + str_len + 1);
// 	return (NULL);
// }

// static bool	check_dollar(t_lex **list, char **envp)
// {
// 	int		i;
// 	char	*str;

// 	i = -1;
// 	str = ft_strchr((*list)->content, '$');
// 	if (!str)
// 		return (false);
// 	(*list)->content = get_env_value(ft_substr((*list)->content, 1, ft_strlen((*list)->content)), envp);
// 	if ((*list)->content == NULL)
// 		return (false);
// 	return (true);
// }

// void	check_double_pipe(t_lex **list, char **envp)
// {
// 	t_lex	*tmp;
// 	int		i;

// 	tmp = *list;
// 	if ((*list)->content == '|')
// 	{
// 		ft_error("Double pipe not supported\n"); // faire retourner le prompt
// 	}
// }

// void	parser(t_lex **list, char **envp)
// {
// 	t_lex	*tmp;

// 	tmp = (*list);
// 	while (list)
// 	{
// 		if ((*list)->token == STRING | (*list)->token  == WORD)
// 		{
// 			check_string_word(list, envp);
// 			continue;
// 		}
// 		if ((*list)->token  == WORD | (*list)->token == FUNCTION)
// 		{
			
// 		}
// 		if ((*list)->token == WORD | (*list)->token == STRING | (*list)->token == DOLLAR)
// 			check_dollar(list, envp);
// 		list = (*list)->next;
// 	}
// }
