/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:09:16 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/10 15:36:08 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_node(char *char_tmp, t_lex **list, enum e_token type)
{
	t_lex	*new;
	new = ft_lstnew_lex(char_tmp);
	ft_lstadd_back_lex(list, new);
	(*list)->token = type;
}

enum e_token	is_sep(char *c)
{
	static t_sep	type[] = {{"<<", 2}, {">>", 2}, {"<", 1}, \
					{">", 1}, {"|", 1}, {"\'", 1}, {"\"", 1}};
	int				i;

	if (!c)
		return (-1);
	i = -1;
	while (++i < 7)
		if (!ft_strncmp(c, type[i].str, type[i].num))
			return (i);
	return (WORD);
}

int	ft_split_word(char *args, t_lex **list)
{
	int				i;
	int				start;
	char			*char_tmp;
	enum e_token	type;
	int				check_sep;

	i = 0;
	start = 0;
	check_sep = 0;
	print_tab(args);
	while (args[start])
	{
		type = is_sep(&args[i]);
		if (args[i] && type != WORD)
		{
			if (i - start == 0)
			{
				char_tmp = ft_substr(args, start, 1);
				i++;
			}
			else
			{
				char_tmp = ft_substr(args, start, i - start);
			}
			start = i;
			new_node(char_tmp, list, type);
			check_sep = 1;
		}
		else
			i++;
	}
	return (check_sep);
}
