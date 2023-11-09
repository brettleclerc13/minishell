/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rough_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:01:12 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/09 12:02:20 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
char	**ft_lex_array(t_lex *args)
{
	t_lex	*tmp;
	char	**array;
	int		struct_len;

	struct_len = 0;
	tmp = args;
	while (tmp)
	{
		struct_len++;
		tmp = tmp->next;
	}
	array = ft_calloc(struct_len + 1, sizeof(char *));
	if (!array)
		return (NULL);
	tmp = args;
	struct_len = 0;
	while (tmp)
	{
		array[struct_len++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (array);
}

int	ft_count_pipe(t_struct *mshell)
{
	t_lex	*args;
	int		pipe_count;

	pipe_count = 0;
	args = mshell->args;
	while (args)
	{
		if (args->token == 4)
			pipe_count++;
		args = args->next;
	}
	return(pipe_count);
}

static char	**ft_convert_to_array(t_lex *args)
{
	t_lex	*tmp;
	char	**array;
	int		struct_len;

	struct_len = 0;
	tmp = args;
	while (tmp)
	{
		struct_len++;
		tmp = tmp->next;
	}
	array = ft_calloc(struct_len + 1, sizeof(char *));
	if (!array)
		return (NULL);
	tmp = args;
	struct_len = 0;
	while (tmp)
	{
		array[struct_len++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (array);
}
*/