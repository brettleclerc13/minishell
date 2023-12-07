/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:09:16 by ehouot            #+#    #+#             */
/*   Updated: 2023/12/06 10:20:36 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_node(t_lex_var *lex_var, char *char_tmp, t_lex **list, enum e_token type)
{
	t_lex	*new;

	new = ft_lstnew_lex(lex_var, char_tmp, type);
	ft_lstadd_back_lex(list, new);
}

void	create_token(t_lex_var *lex_var, char *args, t_lex **list, t_sp_wd **vars)
{
	char	*char_token;

	char_token = ft_substr(args, (*vars)->start, (*vars)->i - (*vars)->start);
	if (!char_token)
		return ;
	if (*char_token)
		new_node(lex_var, char_token, list, (*vars)->type);
	free(char_token);
}

static enum e_token	is_sep_word(char *c, int *i)
{
	static t_sep	type[] = {{"<<", 2}, {">>", 2}, {"<", 1}, \
					{">", 1}, {"|", 1}};
	int				index;
	int				len_word;

	len_word = 0;
	if (!c)
		return (-1);
	while (c[len_word])
	{
		index = -1;
		while (++index < 5)
		{
			if (!ft_strncmp((c + len_word), type[index].str, type[index].num))
			{
				if (len_word > 0)
					return (7);
				*i += type[index].num;
				return (index);
			}
		}
		len_word++;
		(*i)++;
	}
	return (7);
}

int	ft_split_word(t_lex_var *lex_var, char *args, t_lex **list)
{
	t_sp_wd	*vars = NULL;
	int		check_sep;

	vars = malloc(sizeof(t_sp_wd));
	if (!vars)
		return (-1);
	vars->i = 0;
	vars->start = 0;
	vars->type = WORD;
	check_sep = 0;
	while (args[vars->start])
	{
		if (check_sep == 1)
			vars->start = vars->i;
		vars->type = is_sep_word(&args[vars->i], &vars->i);
		if (args[vars->start])
		{
			create_token(lex_var, args, list, &vars);
			check_sep = 1;
		}
	}
	free(vars);
	return (check_sep);
}
