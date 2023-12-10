/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 08:21:30 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/08 21:52:01 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_quote_forwarding(char *c, int *len_word, int *i)
{
	char	quote;

	quote = '\0';
	if (c[*len_word] == '\"' || c[*len_word] == '\'')
	{
		quote = c[(*len_word)++];
		(*i)++;
		while (c[*len_word] && c[*len_word] != quote)
		{
			(*len_word)++;
			(*i)++;
		}
	}
}

static enum e_token	is_sep_str(char *c, int *i, enum e_token token)
{
	static t_sep	type[] = {{"<<", 2}, {">>", 2}, {"<", 1}, \
					{">", 1}, {"|", 1}};
	int				index;
	int				len_word;

	len_word = 0;
	while (c[len_word])
	{
		if (c[len_word] == '\"' || c[len_word] == '\'')
			ft_quote_forwarding(c, &len_word, i);
		index = -1;
		while (++index < 5)
		{
			if (!ft_strncmp((c + len_word), type[index].str, type[index].num))
			{
				if (len_word > 0)
					return (token);
				*i += type[index].num;
				return (index);
			}
		}
		len_word++;
		(*i)++;
	}
	return (token);
}

int	ft_split_string(char *args, t_lex **list, enum e_token token)
{
	t_sp_wd	*vars;
	int		check_sep;

	vars = malloc(sizeof(t_sp_wd));
	if (!vars)
		return (-1);
	vars->i = 0;
	vars->start = 0;
	vars->type = token;
	check_sep = 0;
	while (args[vars->start])
	{
		if (check_sep == 1)
			vars->start = vars->i;
		if (args[vars->i])
			vars->type = is_sep_str(&args[vars->i], &vars->i, token);
		if (args[vars->start])
		{
			create_token(args, list, &vars);
			check_sep = 1;
		}
	}
	free(vars);
	return (check_sep);
}
