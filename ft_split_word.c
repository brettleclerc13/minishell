/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:09:16 by ehouot            #+#    #+#             */
/*   Updated: 2023/10/12 17:04:44 by ehouot           ###   ########.fr       */
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

int	ft_strlen_skip(char *str, char *char_token)
{
	int	i;
	int	len_token;

	i = 0;
	len_token = ft_strlen(char_token);
	if (len_token == 1)
	{
		while (str[i] && str[i] == char_token[0])
			i++;
	}
	else
	{
		while (str[i] && ft_strncmp(str, char_token, len_token))
		{
			i += len_token;
			char_token = char_token + len_token;
		}
	}
	return (i);
}

static void	skip_sep(char *args, t_lex **list, char *char_token, t_sp_wd **vars)
{
	int	skip;

	skip = ft_strlen_skip(args, char_token);
	// if (type != SPACE)
	ft_lstadd_back_lex(list, ft_lstnew_lex(ft_substr(args, (*vars)->i, skip)));
	(*vars)->i += skip;
	(*vars)->start = (*vars)->i;
}

void	create_token(char *args, t_lex **list, t_sp_wd **vars)
{
	char	*char_token;

	char_token = ft_substr(args, (*vars)->start, (*vars)->i - (*vars)->start);
	if (!char_token)
		return ;
	if (*char_token)
		ft_lstadd_back_lex(list, ft_lstnew_lex(char_token));
	if (!*char_token)
		free(char_token);
	skip_sep(args, list, char_token, vars);
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
	t_sp_wd	*vars = NULL;
	int		check_sep;

	vars = malloc(sizeof(t_sp_wd));
	if (!vars)
		return (-1);
	vars->i = 0;
	vars->start = 0;
	check_sep = 0;
	while (args[vars->start])
	{
		vars->type = is_sep(&args[vars->i]);
		if (args[vars->i] && vars->type != WORD)
		{
			create_token(args, list, &vars);
			check_sep = 1;
		}
		else
			vars->i++;
	}
	return (check_sep);
}

// int    ft_split_word(char *args, t_lex **list)
// {
//     int                i;
//     int                start;
//     char            *char_tmp;
//     enum e_token    type;
//     int                check_sep;

//     i = 0;
//     start = 0;
//     check_sep = 0;
//     print_tab(args);
//     while (args[start])
//     {
//         type = is_sep(&args[i]);
//         if (args[i] && type != WORD)
//         {
//             if (i - start == 0)
//             {
//                 char_tmp = ft_substr(args, start, 17);
//                 i++;
//                 start = i;
//                 new_node(char_tmp, list, type);
//                 check_sep = 1;
//             }
//             else
//             {
//                 char_tmp = ft_substr(args, start, i - start);
//                 start = i;
//                 new_node(char_tmp, list, type);
//                 check_sep = 1;
//             }
//         }
//         else
//             i++;
//     }
//     return (check_sep);
// }
