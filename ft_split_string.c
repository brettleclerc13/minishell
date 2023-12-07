/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 08:21:30 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/07 17:19:51 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex	*ft_lstnew_lex_str(void *content, enum e_token token)
{
	t_lex	*new;

	new = malloc (sizeof(t_lex));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->token = token;
	new->next = NULL;
	return (new);
}

void	new_node_str(char *char_tmp, t_lex **list, enum e_token type)
{
	t_lex	*new;

	new = ft_lstnew_lex_str(char_tmp, type);
	ft_lstadd_back_lex(list, new);
}

void	create_token_str(char *args, t_lex **list, t_sp_wd **vars)
{
	char	*char_token;

	char_token = ft_substr(args, (*vars)->start, (*vars)->i - (*vars)->start);
	if (!char_token)
		return ;
	if (*char_token)
		new_node_str(char_token, list, (*vars)->type);
	free(char_token);
}

static enum e_token	is_sep_str(char *c, int *i, enum e_token token)
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
		vars->type = is_sep_str(&args[vars->i], &vars->i, token);
		if (args[vars->start])
		{
			create_token_str(args, list, &vars);
			check_sep = 1;
		}
	}
	free(vars);
	return (check_sep);
}
